/*
 * Copyright 2011-2019 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "bgfx_p.h"

#if BGFX_CONFIG_RENDERER_WEBGPU
#	include "renderer_webgpu.h"

#	include "renderer.h"

#	include "debug_renderdoc.h"

#include <cfloat>

#if !BX_PLATFORM_EMSCRIPTEN
#include <dawn_native/D3D12Backend.h>
#include <dawn_native/DawnNative.h>
#include <dawn/dawn_wsi.h>
#include <dawn/dawn_proc.h>
#else
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#endif

#define UNIFORM_BUFFER_SIZE (8*1024*1024)

#define DAWN_ENABLE_BACKEND_D3D12

namespace bgfx { namespace webgpu
{
	template <class T>
	T defaultDescriptor() { return T(); }

	template <> wgpu::BlendDescriptor              defaultDescriptor() { return { wgpu::BlendOperation::Add, wgpu::BlendFactor::One, wgpu::BlendFactor::Zero }; }
	template <> wgpu::ColorStateDescriptor         defaultDescriptor() { return { nullptr, wgpu::TextureFormat::RGBA8Unorm, defaultDescriptor<wgpu::BlendDescriptor>(), defaultDescriptor<wgpu::BlendDescriptor>(), wgpu::ColorWriteMask::All }; }
	template <> wgpu::StencilStateFaceDescriptor   defaultDescriptor() { return { wgpu::CompareFunction::Always, wgpu::StencilOperation::Keep, wgpu::StencilOperation::Keep, wgpu::StencilOperation::Keep }; }
	template <> wgpu::VertexStateDescriptor        defaultDescriptor() { return { nullptr, wgpu::IndexFormat::Uint32, 0, nullptr }; }
	template <> wgpu::VertexBufferLayoutDescriptor defaultDescriptor() { return { 0, wgpu::InputStepMode::Vertex, 0, nullptr }; }
	template <> wgpu::VertexAttributeDescriptor    defaultDescriptor() { return { wgpu::VertexFormat::Float, 0, 0 }; }
	template <> wgpu::RasterizationStateDescriptor defaultDescriptor() { return { nullptr, wgpu::FrontFace::CCW, wgpu::CullMode::None, 0, 0.f, 0.f }; }
	template <> wgpu::ProgrammableStageDescriptor  defaultDescriptor() { return { nullptr, {}, "main" }; }
	template <> wgpu::DepthStencilStateDescriptor  defaultDescriptor() { return { nullptr, wgpu::TextureFormat::Depth24PlusStencil8, false, wgpu::CompareFunction::Always, defaultDescriptor<wgpu::StencilStateFaceDescriptor>(), defaultDescriptor<wgpu::StencilStateFaceDescriptor>(), 0xff, 0xff }; }
	template <> wgpu::PipelineLayoutDescriptor     defaultDescriptor() { return { nullptr, "", 0, nullptr }; }

	template <> wgpu::RenderPassColorAttachmentDescriptor defaultDescriptor() { return { {}, {}, wgpu::LoadOp::Clear, wgpu::StoreOp::Store, { 0.0f, 0.0f, 0.0f, 0.0f } }; }
	template <> wgpu::RenderPassDepthStencilAttachmentDescriptor defaultDescriptor() { return { {}, wgpu::LoadOp::Clear, wgpu::StoreOp::Store, 1.0f, wgpu::LoadOp::Clear, wgpu::StoreOp::Store, 0 }; }

	RenderPassDescriptor::RenderPassDescriptor()
	{
		depthStencilAttachment = defaultDescriptor<wgpu::RenderPassDepthStencilAttachmentDescriptor>();

		for(uint32_t i = 0; i < kMaxColorAttachments; ++i)
		{
			colorAttachments[i] = defaultDescriptor<wgpu::RenderPassColorAttachmentDescriptor>();
		}

		desc = defaultDescriptor<wgpu::RenderPassDescriptor>();
		//desc.colorAttachmentCount = colorAttachmentCount;
		desc.colorAttachments = colorAttachments;
		desc.colorAttachmentCount = 1; // TODO set it properly everywhere
	}

	VertexStateDescriptor::VertexStateDescriptor()
	{
		for(uint32_t i = 0; i < kMaxVertexInputs; ++i)
		{
			vertexBuffers[i] = defaultDescriptor<wgpu::VertexBufferLayoutDescriptor>();
		}

		for (uint32_t i = 0; i < kMaxVertexAttributes; ++i)
		{
			attributes[i] = defaultDescriptor<wgpu::VertexAttributeDescriptor>();
		}

		vertexBuffers[0].attributes = &attributes[0];
		//vertexBuffers[0].attributeCount = numAttributes;

		desc = defaultDescriptor<wgpu::VertexStateDescriptor>();

		desc.vertexBuffers = vertexBuffers;
		//desc.vertexBufferCount = numVertexBuffers;
	}

	RenderPipelineDescriptor::RenderPipelineDescriptor()
	{
		//vertexStage = defaultDescriptor<wgpu::ProgrammableStageDescriptor>();
		fragmentStage = defaultDescriptor<wgpu::ProgrammableStageDescriptor>();
		rasterizationState = defaultDescriptor<wgpu::RasterizationStateDescriptor>();
		depthStencilState = defaultDescriptor<wgpu::DepthStencilStateDescriptor>();

		for(uint32_t i = 0; i < kMaxColorAttachments; ++i)
		{
			colorStates[i] = defaultDescriptor<wgpu::ColorStateDescriptor>();
		}

		desc = defaultDescriptor<wgpu::RenderPipelineDescriptor>();

		desc.primitiveTopology = wgpu::PrimitiveTopology::TriangleList;
		desc.sampleCount = 1;
		desc.colorStateCount = 1;

		//wgpu::VertexStateDescriptor inputState = inputState.descriptor();

		desc.vertexStage = defaultDescriptor<wgpu::ProgrammableStageDescriptor>();
		desc.fragmentStage = &fragmentStage;
		//desc.vertexState = &inputState;
		desc.rasterizationState = &rasterizationState;
		desc.depthStencilState = nullptr;
		desc.colorStates = colorStates;
	}

	static char s_viewName[BGFX_CONFIG_MAX_VIEWS][BGFX_CONFIG_MAX_VIEW_NAME];

	inline void setViewType(ViewId _view, const bx::StringView _str)
	{
		if (BX_ENABLED(BGFX_CONFIG_DEBUG_ANNOTATION || BGFX_CONFIG_PROFILER) )
		{
			bx::memCopy(&s_viewName[_view][3], _str.getPtr(), _str.getLength() );
		}
	}

	struct PrimInfo
	{
		wgpu::PrimitiveTopology m_type;
		uint32_t m_min;
		uint32_t m_div;
		uint32_t m_sub;
	};
	
	static const PrimInfo s_primInfo[] =
	{
		{ wgpu::PrimitiveTopology::TriangleList,  3, 3, 0 },
		{ wgpu::PrimitiveTopology::TriangleStrip, 3, 1, 2 },
		{ wgpu::PrimitiveTopology::LineList,      2, 2, 0 },
		{ wgpu::PrimitiveTopology::LineStrip,     2, 1, 1 },
		{ wgpu::PrimitiveTopology::PointList,     1, 1, 0 },
	};
	BX_STATIC_ASSERT(Topology::Count == BX_COUNTOF(s_primInfo) );
	
#if 0
	static const char* s_attribName[] =
	{
		"a_position",
		"a_normal",
		"a_tangent",
		"a_bitangent",
		"a_color0",
		"a_color1",
		"a_color2",
		"a_color3",
		"a_indices",
		"a_weight",
		"a_texcoord0",
		"a_texcoord1",
		"a_texcoord2",
		"a_texcoord3",
		"a_texcoord4",
		"a_texcoord5",
		"a_texcoord6",
		"a_texcoord7",
	};
	BX_STATIC_ASSERT(Attrib::Count == BX_COUNTOF(s_attribName) );

	static const char* s_instanceDataName[] =
	{
		"i_data0",
		"i_data1",
		"i_data2",
		"i_data3",
		"i_data4",
	};
	BX_STATIC_ASSERT(BGFX_CONFIG_MAX_INSTANCE_DATA_COUNT == BX_COUNTOF(s_instanceDataName) );
#endif

	static const wgpu::VertexFormat s_attribType[][4][2] =
	{
		{ // Uint8
			{ wgpu::VertexFormat::UChar2,      wgpu::VertexFormat::UChar2Norm },
			{ wgpu::VertexFormat::UChar2,      wgpu::VertexFormat::UChar2Norm },
			{ wgpu::VertexFormat::UChar4,      wgpu::VertexFormat::UChar4Norm },
			{ wgpu::VertexFormat::UChar4,      wgpu::VertexFormat::UChar4Norm },
		},
		{ // Uint10
			{ wgpu::VertexFormat::UShort2, wgpu::VertexFormat::UShort2Norm },
			{ wgpu::VertexFormat::UShort2, wgpu::VertexFormat::UShort2Norm },
			{ wgpu::VertexFormat::UShort4, wgpu::VertexFormat::UShort4Norm },
			{ wgpu::VertexFormat::UShort4, wgpu::VertexFormat::UShort4Norm },
		},
		{ // Int16
			{ wgpu::VertexFormat::Short2, wgpu::VertexFormat::Short2Norm },
			{ wgpu::VertexFormat::Short2, wgpu::VertexFormat::Short2Norm },
			{ wgpu::VertexFormat::Short4, wgpu::VertexFormat::Short4Norm },
			{ wgpu::VertexFormat::Short4, wgpu::VertexFormat::Short4Norm },
		},
		{ // Half
			{ wgpu::VertexFormat::Half2, wgpu::VertexFormat::Half2 },
			{ wgpu::VertexFormat::Half2, wgpu::VertexFormat::Half2 },
			{ wgpu::VertexFormat::Half4, wgpu::VertexFormat::Half4 },
			{ wgpu::VertexFormat::Half4, wgpu::VertexFormat::Half4 },
		},
		{ // Float
			{ wgpu::VertexFormat::Float,  wgpu::VertexFormat::Float  },
			{ wgpu::VertexFormat::Float2, wgpu::VertexFormat::Float2 },
			{ wgpu::VertexFormat::Float3, wgpu::VertexFormat::Float3 },
			{ wgpu::VertexFormat::Float4, wgpu::VertexFormat::Float4 },
		},
	};
	BX_STATIC_ASSERT(AttribType::Count == BX_COUNTOF(s_attribType) );

	static const wgpu::CullMode s_cullMode[] =
	{
		wgpu::CullMode::None,
		wgpu::CullMode::Front,
		wgpu::CullMode::Back,
		wgpu::CullMode::None,
	};

	static const wgpu::BlendFactor s_blendFactor[][2] =
	{
		{ wgpu::BlendFactor(0),                  wgpu::BlendFactor(0)                  }, // ignored
		{ wgpu::BlendFactor::Zero,               wgpu::BlendFactor::Zero               }, // ZERO
		{ wgpu::BlendFactor::One,                wgpu::BlendFactor::One                }, // ONE
		{ wgpu::BlendFactor::SrcColor,           wgpu::BlendFactor::SrcAlpha           }, // SRC_COLOR
		{ wgpu::BlendFactor::OneMinusSrcColor,   wgpu::BlendFactor::OneMinusSrcAlpha   }, // INV_SRC_COLOR
		{ wgpu::BlendFactor::SrcAlpha,           wgpu::BlendFactor::SrcAlpha           }, // SRC_ALPHA
		{ wgpu::BlendFactor::OneMinusSrcAlpha,   wgpu::BlendFactor::OneMinusSrcAlpha   }, // INV_SRC_ALPHA
		{ wgpu::BlendFactor::DstAlpha,           wgpu::BlendFactor::DstAlpha           }, // DST_ALPHA
		{ wgpu::BlendFactor::OneMinusDstAlpha,   wgpu::BlendFactor::OneMinusDstAlpha   }, // INV_DST_ALPHA
		{ wgpu::BlendFactor::DstColor,           wgpu::BlendFactor::DstAlpha           }, // DST_COLOR
		{ wgpu::BlendFactor::OneMinusDstColor,   wgpu::BlendFactor::OneMinusDstAlpha   }, // INV_DST_COLOR
		{ wgpu::BlendFactor::SrcAlphaSaturated,  wgpu::BlendFactor::One                }, // SRC_ALPHA_SAT
		{ wgpu::BlendFactor::BlendColor,         wgpu::BlendFactor::BlendColor         }, // FACTOR
		{ wgpu::BlendFactor::OneMinusBlendColor, wgpu::BlendFactor::OneMinusBlendColor }, // INV_FACTOR
	};

	static const wgpu::BlendOperation s_blendEquation[] =
	{
		wgpu::BlendOperation::Add,
		wgpu::BlendOperation::Subtract,
		wgpu::BlendOperation::ReverseSubtract,
		wgpu::BlendOperation::Min,
		wgpu::BlendOperation::Max,
	};

	static const wgpu::CompareFunction s_cmpFunc[] =
	{
		wgpu::CompareFunction::Always, // ignored
		wgpu::CompareFunction::Less,
		wgpu::CompareFunction::LessEqual,
		wgpu::CompareFunction::Equal,
		wgpu::CompareFunction::GreaterEqual,
		wgpu::CompareFunction::Greater,
		wgpu::CompareFunction::NotEqual,
		wgpu::CompareFunction::Never,
		wgpu::CompareFunction::Always,
	};

	static const wgpu::StencilOperation s_stencilOp[] =
	{
		wgpu::StencilOperation::Zero,
		wgpu::StencilOperation::Keep,
		wgpu::StencilOperation::Replace,
		wgpu::StencilOperation::IncrementWrap,
		wgpu::StencilOperation::IncrementClamp,
		wgpu::StencilOperation::DecrementWrap,
		wgpu::StencilOperation::DecrementClamp,
		wgpu::StencilOperation::Invert,
	};

	static const wgpu::AddressMode s_textureAddress[] =
	{
		wgpu::AddressMode::Repeat,
		wgpu::AddressMode::MirrorRepeat,
		wgpu::AddressMode::ClampToEdge,
		wgpu::AddressMode(0), // Border ? ClampToZero ?
	};

	static const wgpu::FilterMode s_textureFilterMinMag[] =
	{
		wgpu::FilterMode::Linear,
		wgpu::FilterMode::Nearest,
		wgpu::FilterMode::Linear,
	};

	static const wgpu::FilterMode s_textureFilterMip[] =
	{
		wgpu::FilterMode::Linear,
		wgpu::FilterMode::Nearest,
	};

	//struct TextureFormatInfo
	//{
	//	wgpu::TextureFormat:: m_fmt;
	//	wgpu::TextureFormat:: m_fmtSrgb;
	//};

	static wgpu::TextureFormat s_textureFormat[] =
	{
		wgpu::TextureFormat(0), // BC1
		wgpu::TextureFormat(0), // BC2
		wgpu::TextureFormat(0), // BC3
		wgpu::TextureFormat(0), // BC4
		wgpu::TextureFormat(0), // BC5
		wgpu::TextureFormat(0), // BC6H
		wgpu::TextureFormat(0), // BC7
		wgpu::TextureFormat(0), // ETC1
		wgpu::TextureFormat(0), // ETC2
		wgpu::TextureFormat(0), // ETC2A
		wgpu::TextureFormat(0), // ETC2A1
		wgpu::TextureFormat(0), // PTC12
		wgpu::TextureFormat(0), // PTC14
		wgpu::TextureFormat(0), // PTC12A
		wgpu::TextureFormat(0), // PTC14A
		wgpu::TextureFormat(0), // PTC22
		wgpu::TextureFormat(0), // PTC24
		wgpu::TextureFormat(0), // ATC
		wgpu::TextureFormat(0), // ATCE
		wgpu::TextureFormat(0), // ATCI
		wgpu::TextureFormat(0), // ASTC4x4
		wgpu::TextureFormat(0), // ASTC5x5
		wgpu::TextureFormat(0), // ASTC6x6
		wgpu::TextureFormat(0), // ASTC8x5
		wgpu::TextureFormat(0), // ASTC8x6
		wgpu::TextureFormat(0), // ASTC10x5
		wgpu::TextureFormat(0), // Unknown
		wgpu::TextureFormat(0), // R1
		wgpu::TextureFormat(0), // A8
		wgpu::TextureFormat::R8Unorm, // R8
		wgpu::TextureFormat(0), // R8I
		wgpu::TextureFormat::R8Uint, // R8U
		wgpu::TextureFormat(0), // R8S
		wgpu::TextureFormat(0), // R16
		wgpu::TextureFormat(0), // R16I
		wgpu::TextureFormat(0), // R16U
		wgpu::TextureFormat(0), // R16F
		wgpu::TextureFormat(0), // R16S
		wgpu::TextureFormat(0), // R32I
		wgpu::TextureFormat(0), // R32U
		wgpu::TextureFormat(0), // R32F
		wgpu::TextureFormat::RG8Unorm, // RG8
		wgpu::TextureFormat(0), // RG8I
		wgpu::TextureFormat::RG8Uint, // RG8U
		wgpu::TextureFormat(0), // RG8S
		wgpu::TextureFormat(0), // RG16
		wgpu::TextureFormat(0), // RG16I
		wgpu::TextureFormat(0), // RG16U
		wgpu::TextureFormat(0), // RG16F
		wgpu::TextureFormat(0), // RG16S
		wgpu::TextureFormat(0), // RG32I
		wgpu::TextureFormat(0), // RG32U
		wgpu::TextureFormat(0), // RG32F
		wgpu::TextureFormat(0), // RGB8
		wgpu::TextureFormat(0), // RGB8I
		wgpu::TextureFormat(0), // RGB8U
		wgpu::TextureFormat(0), // RGB8S
		wgpu::TextureFormat(0), // RGB9E5F
		wgpu::TextureFormat::BGRA8Unorm, // BGRA8
		wgpu::TextureFormat::RGBA8Unorm, // RGBA8
		wgpu::TextureFormat(0), // RGBA8I
		wgpu::TextureFormat::RGBA8Uint, // RGBA8U
		wgpu::TextureFormat(0), // RGBA8S
		wgpu::TextureFormat(0), // RGBA16
		wgpu::TextureFormat(0), // RGBA16I
		wgpu::TextureFormat(0), // RGBA16U
		wgpu::TextureFormat(0), // RGBA16F
		wgpu::TextureFormat(0), // RGBA16S
		wgpu::TextureFormat(0), // RGBA32I
		wgpu::TextureFormat(0), // RGBA32U
		wgpu::TextureFormat(0), // RGBA32F
		wgpu::TextureFormat(0), // R5G6B5
		wgpu::TextureFormat(0), // RGBA4
		wgpu::TextureFormat(0), // RGB5A1
		wgpu::TextureFormat(0), // RGB10A2
		wgpu::TextureFormat(0), // RG11B10F
		wgpu::TextureFormat(0), // UnknownDepth
		wgpu::TextureFormat(0), // D16
		wgpu::TextureFormat::Depth24Plus, // D24
		wgpu::TextureFormat::Depth24PlusStencil8, // D24S8
		wgpu::TextureFormat(0), // D32
		wgpu::TextureFormat(0), // D16F
		wgpu::TextureFormat(0), // D24F
		wgpu::TextureFormat::Depth32Float, // D32F
		wgpu::TextureFormat(0), // D0S8
	};
	BX_STATIC_ASSERT(TextureFormat::Count == BX_COUNTOF(s_textureFormat));

	int32_t s_msaa[] =
	{
		 1,
		 2,
		 4,
		 8,
		16,
	};

	struct RendererContextWgpu;
	static RendererContextWgpu* s_renderWgpu;

	static bool s_ignoreError = false;

#if !BX_PLATFORM_EMSCRIPTEN
	DawnSwapChainImplementation(*CreateSwapChain)(wgpu::Device device, void* nwh);

	DawnSwapChainImplementation CreateSwapChainD3D12(wgpu::Device device, void* nwh)
	{
		HWND win32Window = (HWND)nwh;
		return dawn_native::d3d12::CreateNativeSwapChainImpl(device.Get(), win32Window);
	}
#endif

	struct RendererContextWgpu : public RendererContextI
	{
		RendererContextWgpu()
			: m_bufferIndex(0)
			, m_numWindows(0)
			, m_rtMsaa(false)
			, m_capture(NULL)
			, m_captureSize(0)
		{
			bx::memSet(&m_windows, 0xff, sizeof(m_windows) );
		}

		~RendererContextWgpu()
		{
		}

		bool init(const Init& _init)
		{
			BX_UNUSED(_init);
			BX_TRACE("Init.");

			if (_init.debug
			||  _init.profile)
			{
				m_renderDocDll = loadRenderDoc();
			}

			setGraphicsDebuggerPresent(NULL != m_renderDocDll);

			m_fbh.idx = kInvalidHandle;
			bx::memSet(m_uniforms, 0, sizeof(m_uniforms) );
			bx::memSet(&m_resolution, 0, sizeof(m_resolution) );

#if !BX_PLATFORM_EMSCRIPTEN
			// Default to D3D12, Metal, Vulkan, OpenGL in that order as D3D12 and Metal are the preferred on
			// their respective platforms, and Vulkan is preferred to OpenGL
#if defined(DAWN_ENABLE_BACKEND_D3D12)
			static dawn_native::BackendType backendType = dawn_native::BackendType::D3D12;
#elif defined(DAWN_ENABLE_BACKEND_METAL)
			static dawn_native::BackendType backendType = dawn_native::BackendType::Metal;
#elif defined(DAWN_ENABLE_BACKEND_OPENGL)
			static dawn_native::BackendType backendType = dawn_native::BackendType::OpenGL;
#elif defined(DAWN_ENABLE_BACKEND_VULKAN)
			static dawn_native::BackendType backendType = dawn_native::BackendType::Vulkan;
#else
#error
#endif

			m_instance.DiscoverDefaultAdapters();

			dawn_native::Adapter backendAdapter;
			backendAdapter = m_instance.GetAdapter();

#if 0
			std::vector<dawn_native::Adapter> adapters = m_instance.GetAdapters();
			for (dawn_native::Adapter& adapter : adapters)
			{
				if (adapter.GetBackendType() == backendType)
					backendAdapter = adapter;
			}
#endif

			//BX_ASSERT(adapterIt != adapters.end());

			WGPUDevice backendDevice = backendAdapter.CreateDevice();
			DawnProcTable backendProcs = dawn_native::GetProcs();

			switch(backendType) {
#if defined(DAWN_ENABLE_BACKEND_D3D12)
			case dawn_native::BackendType::D3D12:
				CreateSwapChain = CreateSwapChainD3D12;
				break;
#endif

#if defined(DAWN_ENABLE_BACKEND_METAL)
			case dawn_native::BackendType::Metal:
				CreateSwapChain = CreateSwapChainMetal;
				break;
#endif

#if defined(DAWN_ENABLE_BACKEND_NULL)
			case dawn_native::BackendType::Null:
				CreateSwapChain = CreateSwapChainNull;
				break;
#endif

#if defined(DAWN_ENABLE_BACKEND_OPENGL)
			case dawn_native::BackendType::OpenGL:
				CreateSwapChain = CreateSwapChainOpenGL;
				break;
#endif

#if defined(DAWN_ENABLE_BACKEND_VULKAN)
			case dawn_native::BackendType::Vulkan:
				CreateSwapChain = CreateSwapChainVulkan;
				break;
#endif

			default:
				return nullptr;
			}

			// Choose whether to use the backend procs and devices directly, or set up the wire.
			WGPUDevice cDevice = backendDevice;
			DawnProcTable procs = backendProcs;
			dawnProcSetProcs(&procs);

			m_device = wgpu::Device::Acquire(cDevice);
#else
			m_device = wgpu::Device(emscripten_webgpu_get_device());
#endif

			auto PrintDeviceError = [](WGPUErrorType errorType, const char* message, void*) {
				BX_UNUSED(errorType);

				if (s_ignoreError)
				{
					BX_TRACE("Device error: %s", message);
				}
				else
				{
					BX_CHECK(false, "Device error: %s", message);
				}
				s_ignoreError = false;
			};

			m_device.SetUncapturedErrorCallback(PrintDeviceError, nullptr);

			if (!m_device)
			{
				BX_WARN(!m_device, "Unable to create WebGPU device.");
				return false;
			}

			bool success = m_mainFrameBuffer.create(
				  0
				, g_platformData.nwh
				, _init.resolution.width
				, _init.resolution.height
				, TextureFormat::Unknown
				, TextureFormat::UnknownDepth
				);
			m_numWindows = 1;

			if (!success)
			{
				return false;
			}

			m_queue = m_device.CreateQueue();

			m_cmd.init(m_queue);
			//BGFX_FATAL(NULL != m_cmd.m_commandQueue, Fatal::UnableToInitialize, "Unable to create Metal device.");

			for (uint8_t ii = 0; ii < WEBGPU_MAX_FRAMES_IN_FLIGHT; ++ii)
			{
				BX_TRACE("Create scratch buffer %d", ii);
				m_scratchBuffers[ii].create(BGFX_CONFIG_MAX_DRAW_CALLS * 128); // , 1024);
			}

			g_caps.supported |= (0
				| BGFX_CAPS_ALPHA_TO_COVERAGE
				| BGFX_CAPS_BLEND_INDEPENDENT
				| BGFX_CAPS_FRAGMENT_DEPTH
				| BGFX_CAPS_INDEX32
				| BGFX_CAPS_INSTANCING
				| BGFX_CAPS_OCCLUSION_QUERY
				| BGFX_CAPS_SWAP_CHAIN
				| BGFX_CAPS_TEXTURE_2D_ARRAY
				| BGFX_CAPS_TEXTURE_3D
				| BGFX_CAPS_TEXTURE_BLIT
				| BGFX_CAPS_TEXTURE_COMPARE_ALL
				| BGFX_CAPS_TEXTURE_COMPARE_LEQUAL
				| BGFX_CAPS_TEXTURE_READ_BACK
				| BGFX_CAPS_VERTEX_ATTRIB_HALF
				| BGFX_CAPS_VERTEX_ATTRIB_UINT10
				| BGFX_CAPS_COMPUTE
				);

			g_caps.limits.maxTextureSize   = 16384;
			g_caps.limits.maxFBAttachments = 4;
			g_caps.supported |= BGFX_CAPS_TEXTURE_CUBE_ARRAY;

			if (false) // m_device.supportsFeatureSet( (MTLFeatureSet)10001 /* MTLFeatureSet_macOS_GPUFamily1_v2 */ ))
			{
				g_caps.supported |= BGFX_CAPS_DRAW_INDIRECT;
			}

			g_caps.limits.maxTextureLayers = 2048;
			g_caps.limits.maxVertexStreams = BGFX_CONFIG_MAX_VERTEX_STREAMS;
			// Maximum number of entries in the buffer argument table, per graphics or compute function are 31.
			// It is decremented by 1 because 1 entry is used for uniforms.
			g_caps.limits.maxComputeBindings = bx::uint32_min(30, BGFX_MAX_COMPUTE_BINDINGS);

			for (uint32_t ii = 0; ii < TextureFormat::Count; ++ii)
			{
				uint16_t support = 0;

				support |= wgpu::TextureFormat(0) != s_textureFormat[ii]
					? BGFX_CAPS_FORMAT_TEXTURE_2D
					| BGFX_CAPS_FORMAT_TEXTURE_3D
					| BGFX_CAPS_FORMAT_TEXTURE_CUBE
					| BGFX_CAPS_FORMAT_TEXTURE_VERTEX
					: BGFX_CAPS_FORMAT_TEXTURE_NONE
					;

				//support |= wgpu::TextureFormat::Invalid != s_textureFormat[ii].m_fmtSrgb
				//	? BGFX_CAPS_FORMAT_TEXTURE_2D_SRGB
				//	| BGFX_CAPS_FORMAT_TEXTURE_3D_SRGB
				//	| BGFX_CAPS_FORMAT_TEXTURE_CUBE_SRGB
				//	| BGFX_CAPS_FORMAT_TEXTURE_VERTEX
				//	: BGFX_CAPS_FORMAT_TEXTURE_NONE
				//	;

				if (!bimg::isCompressed(bimg::TextureFormat::Enum(ii) ) )
				{
					support |= 0
						| BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER
						| BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA
						;
				}

				g_caps.formats[ii] = support;
			}

			g_caps.formats[TextureFormat::A8     ] &= ~(BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER | BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA);
			g_caps.formats[TextureFormat::RG32I  ] &= ~(BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA);
			g_caps.formats[TextureFormat::RG32U  ] &= ~(BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA);
			g_caps.formats[TextureFormat::RGBA32I] &= ~(BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA);
			g_caps.formats[TextureFormat::RGBA32U] &= ~(BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA);

			//s_textureFormat[TextureFormat::D24S8].m_fmt = (wgpu::TextureFormat::)(m_device.depth24Stencil8PixelFormatSupported()
			//	? 255 /* Depth24Unorm_Stencil8 */
			//	: wgpu::TextureFormat::Depth32Float_Stencil8)
			//	;

			g_caps.formats[TextureFormat::ETC2  ] =
			g_caps.formats[TextureFormat::ETC2A ] =
			g_caps.formats[TextureFormat::ETC2A1] =
			g_caps.formats[TextureFormat::PTC12 ] =
			g_caps.formats[TextureFormat::PTC14 ] =
			g_caps.formats[TextureFormat::PTC12A] =
			g_caps.formats[TextureFormat::PTC14A] =
			g_caps.formats[TextureFormat::R5G6B5] =
			g_caps.formats[TextureFormat::RGBA4 ] =
			g_caps.formats[TextureFormat::RGB5A1] = BGFX_CAPS_FORMAT_TEXTURE_NONE;

			g_caps.formats[TextureFormat::RGB9E5F] &= ~(BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER | BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA);

			for (uint32_t ii = 0; ii < TextureFormat::Count; ++ii)
			{
				if (BGFX_CAPS_FORMAT_TEXTURE_NONE == g_caps.formats[ii])
				{
					s_textureFormat[ii] = wgpu::TextureFormat(0);
					//s_textureFormat[ii].m_fmtSrgb = wgpu::TextureFormat::Invalid;
				}
			}

			for (uint32_t ii = 1, last = 0; ii < BX_COUNTOF(s_msaa); ++ii)
			{
				//const int32_t sampleCount = 1; //1<<ii;
				//if (m_device.supportsTextureSampleCount(sampleCount) )
				//{
				//	s_msaa[ii] = sampleCount;
				//	last = ii;
				//}
				//else
				{
					s_msaa[ii] = s_msaa[last];
				}
			}

			// Init reserved part of view name.
			for (uint32_t ii = 0; ii < BGFX_CONFIG_MAX_VIEWS; ++ii)
			{
				bx::snprintf(s_viewName[ii], BGFX_CONFIG_MAX_VIEW_NAME_RESERVED+1, "%3d   ", ii);
			}

			m_occlusionQuery.preReset();
			m_gpuTimer.init();

			g_internalData.context = &m_device;

			return true;
		}

		void shutdown()
		{
			m_occlusionQuery.postReset();
			m_gpuTimer.shutdown();

			m_pipelineStateCache.invalidate();

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_shaders); ++ii)
			{
				m_shaders[ii].destroy();
			}

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_textures); ++ii)
			{
				m_textures[ii].destroy();
			}

			captureFinish();

			m_mainFrameBuffer.destroy();

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_scratchBuffers); ++ii)
			{
				m_scratchBuffers[ii].destroy();
			}

			m_cmd.shutdown();
		}

		RendererType::Enum getRendererType() const override
		{
			return RendererType::WebGPU;
		}

		const char* getRendererName() const override
		{
			return BGFX_RENDERER_WEBGPU_NAME;
		}

		void createIndexBuffer(IndexBufferHandle _handle, const Memory* _mem, uint16_t _flags) override
		{
			m_indexBuffers[_handle.idx].create(_mem->size, _mem->data, _flags);
		}

		void destroyIndexBuffer(IndexBufferHandle _handle) override
		{
			m_indexBuffers[_handle.idx].destroy();
		}

		void createVertexLayout(VertexLayoutHandle _handle, const VertexLayout& _decl) override
		{
			VertexLayout& decl = m_vertexDecls[_handle.idx];
			bx::memCopy(&decl, &_decl, sizeof(VertexLayout) );
			dump(decl);
		}

		void destroyVertexLayout(VertexLayoutHandle /*_handle*/) override
		{
		}

		void createVertexBuffer(VertexBufferHandle _handle, const Memory* _mem, VertexLayoutHandle _declHandle, uint16_t _flags) override
		{
			m_vertexBuffers[_handle.idx].create(_mem->size, _mem->data, _declHandle, _flags);
		}

		void destroyVertexBuffer(VertexBufferHandle _handle) override
		{
			m_vertexBuffers[_handle.idx].destroy();
		}

		void createDynamicIndexBuffer(IndexBufferHandle _handle, uint32_t _size, uint16_t _flags) override
		{
			m_indexBuffers[_handle.idx].create(_size, NULL, _flags);
		}

		void updateDynamicIndexBuffer(IndexBufferHandle _handle, uint32_t _offset, uint32_t _size, const Memory* _mem) override
		{
			m_indexBuffers[_handle.idx].update(_offset, bx::uint32_min(_size, _mem->size), _mem->data);
		}

		void destroyDynamicIndexBuffer(IndexBufferHandle _handle) override
		{
			m_indexBuffers[_handle.idx].destroy();
		}

		void createDynamicVertexBuffer(VertexBufferHandle _handle, uint32_t _size, uint16_t _flags) override
		{
			VertexLayoutHandle decl = BGFX_INVALID_HANDLE;
			m_vertexBuffers[_handle.idx].create(_size, NULL, decl, _flags);
		}

		void updateDynamicVertexBuffer(VertexBufferHandle _handle, uint32_t _offset, uint32_t _size, const Memory* _mem) override
		{
			m_vertexBuffers[_handle.idx].update(_offset, bx::uint32_min(_size, _mem->size), _mem->data);
		}

		void destroyDynamicVertexBuffer(VertexBufferHandle _handle) override
		{
			m_vertexBuffers[_handle.idx].destroy();
		}

		void createShader(ShaderHandle _handle, const Memory* _mem) override
		{
			m_shaders[_handle.idx].create(_handle, _mem);
		}

		void destroyShader(ShaderHandle _handle) override
		{
			m_shaders[_handle.idx].destroy();
		}

		void createProgram(ProgramHandle _handle, ShaderHandle _vsh, ShaderHandle _gsh, ShaderHandle _fsh) override
		{
			BX_UNUSED(_gsh);
			m_program[_handle.idx].create(&m_shaders[_vsh.idx], isValid(_fsh) ? &m_shaders[_fsh.idx] : NULL);
		}

		void destroyProgram(ProgramHandle _handle) override
		{
			m_program[_handle.idx].destroy();
		}

		void* createTexture(TextureHandle _handle, const Memory* _mem, uint64_t _flags, uint8_t _skip) override
		{
			m_textures[_handle.idx].create(_mem, _flags, _skip);
			return NULL;
		}

		void updateTextureBegin(TextureHandle /*_handle*/, uint8_t /*_side*/, uint8_t /*_mip*/) override
		{
		}

		void updateTexture(TextureHandle _handle, uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem) override
		{
			m_textures[_handle.idx].update(_side, _mip, _rect, _z, _depth, _pitch, _mem);
		}

		void updateTextureEnd() override
		{
		}

		void readTexture(TextureHandle _handle, void* _data, uint8_t _mip) override
		{
			BX_UNUSED(_data);

			m_cmd.kick(false, true);
			m_cmd.begin();

			const TextureWgpu& texture = m_textures[_handle.idx];

			BX_CHECK(_mip<texture.m_numMips,"Invalid mip: %d num mips:",_mip,texture.m_numMips);

			uint32_t srcWidth  = bx::uint32_max(1, texture.m_width  >> _mip);
			uint32_t srcHeight = bx::uint32_max(1, texture.m_height >> _mip);
			const uint8_t bpp  = bimg::getBitsPerPixel(bimg::TextureFormat::Enum(texture.m_textureFormat) );

			BX_UNUSED(srcWidth);
			BX_UNUSED(srcHeight);
			BX_UNUSED(bpp);

			//MTLRegion region =
			//{
			//	{        0,         0, 0 },
			//	{ srcWidth, srcHeight, 1 },
			//};
			//
			//texture.m_ptr.getBytes(_data, srcWidth*bpp/8, 0, region, _mip, 0);
		}

		void resizeTexture(TextureHandle _handle, uint16_t _width, uint16_t _height, uint8_t _numMips, uint16_t _numLayers) override
		{
			TextureWgpu& texture = m_textures[_handle.idx];

			uint32_t size = sizeof(uint32_t) + sizeof(TextureCreate);
			const Memory* mem = alloc(size);

			bx::StaticMemoryBlockWriter writer(mem->data, mem->size);
			uint32_t magic = BGFX_CHUNK_MAGIC_TEX;
			bx::write(&writer, magic);

			TextureCreate tc;
			tc.m_width     = _width;
			tc.m_height    = _height;
			tc.m_depth     = 0;
			tc.m_numLayers = _numLayers;
			tc.m_numMips   = _numMips;
			tc.m_format    = TextureFormat::Enum(texture.m_requestedFormat);
			tc.m_cubeMap   = false;
			tc.m_mem       = NULL;
			bx::write(&writer, tc);

			texture.destroy();
			texture.create(mem, texture.m_flags, 0);

			release(mem);
		}

		void overrideInternal(TextureHandle _handle, uintptr_t _ptr) override
		{
			BX_UNUSED(_handle, _ptr);
		}

		uintptr_t getInternal(TextureHandle _handle) override
		{
			BX_UNUSED(_handle);
			return 0;
		}

		void destroyTexture(TextureHandle _handle) override
		{
			m_textures[_handle.idx].destroy();
		}

		void createFrameBuffer(FrameBufferHandle _handle, uint8_t _num, const Attachment* _attachment) override
		{
			m_frameBuffers[_handle.idx].create(_num, _attachment);
		}

		void createFrameBuffer(FrameBufferHandle _handle, void* _nwh, uint32_t _width, uint32_t _height, TextureFormat::Enum _format, TextureFormat::Enum _depthFormat) override
		{
			for (uint32_t ii = 0, num = m_numWindows; ii < num; ++ii)
			{
				FrameBufferHandle handle = m_windows[ii];
				if (isValid(handle)
				&&  m_frameBuffers[handle.idx].m_nwh == _nwh)
				{
					destroyFrameBuffer(handle);
				}
			}

			uint16_t denseIdx   = m_numWindows++;
			m_windows[denseIdx] = _handle;

			FrameBufferWgpu& fb = m_frameBuffers[_handle.idx];
			fb.create(denseIdx, _nwh, _width, _height, _format, _depthFormat);
			fb.m_swapChain->resize(m_frameBuffers[_handle.idx], _width, _height, 0);
		}

		void destroyFrameBuffer(FrameBufferHandle _handle) override
		{
			uint16_t denseIdx = m_frameBuffers[_handle.idx].destroy();

			if (UINT16_MAX != denseIdx)
			{
				--m_numWindows;

				if (m_numWindows > 1)
				{
					FrameBufferHandle handle = m_windows[m_numWindows];
					m_windows[m_numWindows]  = {kInvalidHandle};

					if (m_numWindows != denseIdx)
					{
						m_windows[denseIdx] = handle;
						m_frameBuffers[handle.idx].m_denseIdx = denseIdx;
					}
				}
			}
		}

		void createUniform(UniformHandle _handle, UniformType::Enum _type, uint16_t _num, const char* _name, UniformSet::Enum _freq) override
		{
			if (NULL != m_uniforms[_handle.idx])
			{
				BX_FREE(g_allocator, m_uniforms[_handle.idx]);
			}

			uint32_t size = BX_ALIGN_16(g_uniformTypeSize[_type]*_num);
			void* data = BX_ALLOC(g_allocator, size);
			bx::memSet(data, 0, size);
			m_uniforms[_handle.idx] = data;
			m_uniformReg.add(_handle, _name, _freq);
		}

		void destroyUniform(UniformHandle _handle) override
		{
			BX_FREE(g_allocator, m_uniforms[_handle.idx]);
			m_uniforms[_handle.idx] = NULL;
			m_uniformReg.remove(_handle);
		}

		void requestScreenShotPre(const char* _filePath)
		{
			BX_UNUSED(_filePath);
			//m_saveScreenshot = true;
		}

		void requestScreenShot(FrameBufferHandle _handle, const char* _filePath) override
		{
			BX_UNUSED(_handle); BX_UNUSED(_filePath);
		}

		void updateViewName(ViewId _id, const char* _name) override
		{
			bx::strCopy(
				  &s_viewName[_id][BGFX_CONFIG_MAX_VIEW_NAME_RESERVED]
				, BX_COUNTOF(s_viewName[0])-BGFX_CONFIG_MAX_VIEW_NAME_RESERVED
				, _name
				);
		}

		void updateUniform(uint16_t _loc, const void* _data, uint32_t _size) override
		{
			bx::memCopy(m_uniforms[_loc], _data, _size);
		}

		void invalidateOcclusionQuery(OcclusionQueryHandle _handle) override
		{
			m_occlusionQuery.invalidate(_handle);
		}

		void setMarker(const char* _marker, uint16_t _len) override
		{
			BX_UNUSED(_len);

			if (BX_ENABLED(BGFX_CONFIG_DEBUG_ANNOTATION) )
			{
				m_renderEncoder.InsertDebugMarker(_marker);
			}
		}

		virtual void setName(Handle _handle, const char* _name, uint16_t _len) override
		{
			BX_UNUSED(_handle); BX_UNUSED(_name); BX_UNUSED(_len);
#if 0
			BX_UNUSED(_len);

			switch (_handle.type)
			{
			case Handle::IndexBuffer:
				m_indexBuffers[_handle.idx].m_ptr.setLabel(_name);
				break;

			case Handle::Shader:
				m_shaders[_handle.idx].m_function.setLabel(_name);
				break;

			case Handle::Texture:
				m_textures[_handle.idx].m_ptr.setLabel(_name);
				break;

			case Handle::VertexBuffer:
				m_vertexBuffers[_handle.idx].m_ptr.setLabel(_name);
				break;

			default:
				BX_CHECK(false, "Invalid handle type?! %d", _handle.type);
				break;
			}
#endif
		}

		void submitBlit(BlitState& _bs, uint16_t _view);

		void submit(Frame* _render, ClearQuad& _clearQuad, TextVideoMemBlitter& _textVideoMemBlitter) override;

		void blitSetup(TextVideoMemBlitter& _blitter) override
		{
			BX_UNUSED(_blitter);
		}

		void blitRender(TextVideoMemBlitter& _blitter, uint32_t _numIndices) override
		{
			const uint32_t numVertices = _numIndices*4/6;
			if (0 < numVertices)
			{
				m_indexBuffers [_blitter.m_ib->handle.idx].update(
					  0
					, bx::strideAlign(_numIndices*2, 4)
					, _blitter.m_ib->data
					, true
					);
				m_vertexBuffers[_blitter.m_vb->handle.idx].update(
					  0
					, numVertices*_blitter.m_layout.m_stride
					, _blitter.m_vb->data
					, true
					);

				endEncoding();

				uint32_t width  = m_resolution.width;
				uint32_t height = m_resolution.height;

				FrameBufferHandle fbh = BGFX_INVALID_HANDLE;

				uint64_t state = 0
				| BGFX_STATE_WRITE_RGB
				| BGFX_STATE_WRITE_A
				| BGFX_STATE_DEPTH_TEST_ALWAYS
				;

				PipelineStateWgpu* pso = getPipelineState(
														 state
														 , 0
														 , 0
														 , fbh
														 , _blitter.m_vb->layoutHandle
														 , false
														 , _blitter.m_program
														 , 0
														 );

				RenderPassDescriptor renderPassDescriptor;
				wgpu::RenderPassColorAttachmentDescriptor& color = renderPassDescriptor.colorAttachments[0];

				setFrameBuffer(renderPassDescriptor, fbh);

				color.loadOp = wgpu::LoadOp::Load;
				color.storeOp = wgpu::StoreOp::Store;
				//	NULL != renderPassDescriptor.colorAttachments[0].resolveTexture
				//	? wgpu::StoreOp::MultisampleResolve
				//	: wgpu::StoreOp::Store
				//;

				wgpu::RenderPassEncoder rce = m_cmd.m_encoder.BeginRenderPass(&renderPassDescriptor.desc);
				m_renderEncoder = rce;
				m_renderCommandEncoderFrameBufferHandle = fbh;

				//rce.SetViewport(0.0f, 0.0f, (float)width, (float)height, 0.0f, 1.0f);
				rce.SetScissorRect(0, 0, width, height);
				//rce.setCullMode(MTLCullModeNone);

				rce.SetPipeline(pso->m_rps);

				ProgramWgpu& program = m_program[_blitter.m_program.idx];

				//const uint32_t align = uint32_t(m_deviceProperties.limits.minUniformBufferOffsetAlignment);
				const uint32_t align = kMinUniformBufferOffsetAlignment;

				const uint32_t vsize = bx::strideAlign(program.m_vsh->m_size, align);
				const uint32_t fsize = bx::strideAlign((NULL != program.m_fsh ? program.m_fsh->m_size : 0), align);
				//const uint32_t total = vsize + fsize;

				wgpu::BindGroupBinding uniforms[2] = {};
				wgpu::BindGroupBinding textures[2] = {};
				wgpu::BindGroupBinding samplers[2] = {};

				ScratchBufferWgpu& scratchBuffer = m_scratchBuffers[0];
				const uint32_t voffset = scratchBuffer.m_offset;
				const uint32_t foffset = scratchBuffer.m_offset + vsize;
				scratchBuffer.m_offset += vsize + fsize;

				uniforms[0].binding = 0;
				uniforms[0].buffer = scratchBuffer.m_buffer;
				uniforms[0].offset = voffset;
				uniforms[0].size = vsize;

				uniforms[1].binding = 1;
				uniforms[1].buffer = scratchBuffer.m_buffer;
				uniforms[1].offset = foffset;
				uniforms[1].size = fsize;

				float proj[16];
				bx::mtxOrtho(proj, 0.0f, (float)width, (float)height, 0.0f, 0.0f, 1000.0f, 0.0f, false);

				PredefinedUniform& predefined = program.m_predefined[0];
				uint8_t flags = predefined.m_type;
				setShaderUniform(flags, predefined.m_loc, proj, 4);

				TextureWgpu& texture = m_textures[_blitter.m_texture.idx];

				textures[1].binding = 0;
				textures[1].textureView = texture.m_ptr.CreateView();

				samplers[1].binding = 0;
				samplers[1].sampler = 0 == (BGFX_SAMPLER_INTERNAL_DEFAULT & state)
					? getSamplerState(state)
					: texture.m_sampler;

				// TODO
				//bindProgram(m_device, m_renderEncoder, program, uniforms, textures, samplers, 1);

				VertexBufferWgpu& vb = m_vertexBuffers[_blitter.m_vb->handle.idx];
				m_renderEncoder.SetVertexBuffer(0, vb.m_ptr);

				m_renderEncoder.SetIndexBuffer(m_indexBuffers[_blitter.m_ib->handle.idx].m_ptr, 0);
				m_renderEncoder.DrawIndexed(_numIndices, 1, 0, 0, 0);
			}
		}

		bool isDeviceRemoved() override
		{
			return false;
		}

		void flip() override
		{
			//if (!m_cmd.m_encoder)
			//{
			//	return;
			//}

			//m_cmd.kick(true);

			for (uint32_t ii = 0, num = m_numWindows; ii < num; ++ii)
			{
				FrameBufferWgpu& frameBuffer = ii == 0 ? m_mainFrameBuffer : m_frameBuffers[m_windows[ii].idx];
				if (NULL != frameBuffer.m_swapChain)
				//&& frameBuffer.m_swapChain->m_drawable)
				{
					SwapChainWgpu& swapChain = *frameBuffer.m_swapChain;
					swapChain.flip();
				}
			}

			//m_cmd.kick(true);
			m_cmd.m_encoder = nullptr;
		}

		void updateResolution(const Resolution& _resolution)
		{
			m_resolution = _resolution;
			return; // @todo

			m_mainFrameBuffer.m_swapChain->m_maxAnisotropy = !!(_resolution.reset & BGFX_RESET_MAXANISOTROPY)
				? 16
				: 1
				;

			const uint32_t maskFlags = ~(0
				| BGFX_RESET_MAXANISOTROPY
				| BGFX_RESET_DEPTH_CLAMP
				| BGFX_RESET_SUSPEND
				);

			if (m_resolution.width            !=  _resolution.width
			||  m_resolution.height           !=  _resolution.height
			|| (m_resolution.reset&maskFlags) != (_resolution.reset&maskFlags) )
			{
				wgpu::TextureFormat prevMetalLayerPixelFormat; // = m_mainFrameBuffer.m_swapChain->m_metalLayer.pixelFormat;
				BX_UNUSED(prevMetalLayerPixelFormat);

				m_resolution = _resolution;
				m_resolution.reset &= ~BGFX_RESET_INTERNAL_FORCE;

				m_mainFrameBuffer.m_swapChain->resize(m_mainFrameBuffer, _resolution.width, _resolution.height, _resolution.reset);

				for (uint32_t ii = 0; ii < BX_COUNTOF(m_frameBuffers); ++ii)
				{
					m_frameBuffers[ii].postReset();
				}

				updateCapture();

				m_textVideoMem.resize(false, _resolution.width, _resolution.height);
				m_textVideoMem.clear();

				//if (prevMetalLayerPixelFormat != m_mainFrameBuffer.m_swapChain->m_metalLayer.pixelFormat)
				{
					//MTL_RELEASE(m_screenshotBlitRenderPipelineState)
					//reset(m_renderPipelineDescriptor);

					//m_renderPipelineDescriptor.colorAttachments[0].pixelFormat = m_mainFrameBuffer.m_swapChain->m_metalLayer.pixelFormat;
					//m_renderPipelineDescriptor.vertexFunction   = m_screenshotBlitProgram.m_vsh->m_function;
					//m_renderPipelineDescriptor.fragmentFunction = m_screenshotBlitProgram.m_fsh->m_function;
					//m_screenshotBlitRenderPipelineState = m_device.newRenderPipelineStateWithDescriptor(m_renderPipelineDescriptor);
				}
			}
		}

		void invalidateCompute()
		{
			if (m_computeEncoder)
			{
				m_computeEncoder.EndPass();
				m_computeEncoder = NULL;
			}
		}

		void updateCapture()
		{
		}

		void capture()
		{
		}

		void captureFinish()
		{
		}


		void setShaderUniform(uint8_t _flags, uint32_t _regIndex, const void* _val, uint32_t _numRegs)
		{
			if(_flags&BGFX_UNIFORM_FRAGMENTBIT)
			{
				bx::memCopy(&m_fsScratch[_regIndex], _val, _numRegs * 16);
			}
			else
			{
				bx::memCopy(&m_vsScratch[_regIndex], _val, _numRegs * 16);
			}
		}

		void setShaderUniform4f(uint8_t _flags, uint32_t _loc, const void* _val, uint32_t _numRegs)
		{
			setShaderUniform(_flags, _loc, _val, _numRegs);
		}

		void setShaderUniform4x4f(uint8_t _flags, uint32_t _loc, const void* _val, uint32_t _numRegs)
		{
			setShaderUniform(_flags, _loc, _val, _numRegs);
		}

		void commitShaderConstants(ScratchBufferWgpu& _scratchBuffer, const ProgramWgpu& _program, uint32_t _vertexOffset, uint32_t _fragmentOffset)
		{
			const uint32_t size = _program.m_vsh->m_size;
			if (0 != size)
				_scratchBuffer.m_buffer.SetSubData(_vertexOffset, size, m_vsScratch);

			if(NULL != _program.m_fsh)
			{
				const uint32_t size = _program.m_fsh->m_size;
				if(0 != size)
					_scratchBuffer.m_buffer.SetSubData(_fragmentOffset, size, m_fsScratch);
			}
		}

		void commit(UniformBuffer& _uniformBuffer)
		{
			_uniformBuffer.reset();

			for (;;)
			{
				uint32_t opcode = _uniformBuffer.read();

				if (UniformType::End == opcode)
				{
					break;
				}

				UniformType::Enum type;
				uint16_t loc;
				uint16_t num;
				uint16_t copy;
				UniformBuffer::decodeOpcode(opcode, type, loc, num, copy);

				const char* data;
				if (copy)
				{
					data = _uniformBuffer.read(g_uniformTypeSize[type]*num);
				}
				else
				{
					UniformHandle handle;
					bx::memCopy(&handle, _uniformBuffer.read(sizeof(UniformHandle) ), sizeof(UniformHandle) );
					data = (const char*)m_uniforms[handle.idx];
				}

#define CASE_IMPLEMENT_UNIFORM(_uniform, _dxsuffix, _type) \
	case UniformType::_uniform:                            \
	case UniformType::_uniform|BGFX_UNIFORM_FRAGMENTBIT:   \
	{                                                      \
		setShaderUniform(uint8_t(type), loc, data, num);   \
	}                                                      \
	break;

				switch ( (uint32_t)type)
				{
				case UniformType::Mat3:
				case UniformType::Mat3|BGFX_UNIFORM_FRAGMENTBIT:
					{
						float* value = (float*)data;
						for (uint32_t ii = 0, count = num/3; ii < count; ++ii,  loc += 3*16, value += 9)
						{
							Matrix4 mtx;
							mtx.un.val[ 0] = value[0];
							mtx.un.val[ 1] = value[1];
							mtx.un.val[ 2] = value[2];
							mtx.un.val[ 3] = 0.0f;
							mtx.un.val[ 4] = value[3];
							mtx.un.val[ 5] = value[4];
							mtx.un.val[ 6] = value[5];
							mtx.un.val[ 7] = 0.0f;
							mtx.un.val[ 8] = value[6];
							mtx.un.val[ 9] = value[7];
							mtx.un.val[10] = value[8];
							mtx.un.val[11] = 0.0f;
							setShaderUniform(uint8_t(type), loc, &mtx.un.val[0], 3);
						}
					}
					break;

					CASE_IMPLEMENT_UNIFORM(Sampler, I, int);
					CASE_IMPLEMENT_UNIFORM(Vec4,    F, float);
					CASE_IMPLEMENT_UNIFORM(Mat4,    F, float);

				case UniformType::End:
					break;

				default:
					BX_TRACE("%4d: INVALID 0x%08x, t %d, l %d, n %d, c %d", _uniformBuffer.getPos(), opcode, type, loc, num, copy);
					break;
				}

#undef CASE_IMPLEMENT_UNIFORM

			}
		}

		void clearQuad(ClearQuad& _clearQuad, const Rect& /*_rect*/, const Clear& _clear, const float _palette[][4])
		{
			uint32_t width;
			uint32_t height;

			if (isValid(m_fbh) )
			{
				const FrameBufferWgpu& fb = m_frameBuffers[m_fbh.idx];
				width  = fb.m_width;
				height = fb.m_height;
			}
			else
			{
				width  = m_resolution.width;
				height = m_resolution.height;
			}

			uint64_t state = 0;
			state |= _clear.m_flags & BGFX_CLEAR_COLOR ? BGFX_STATE_WRITE_RGB|BGFX_STATE_WRITE_A         : 0;
			state |= _clear.m_flags & BGFX_CLEAR_DEPTH ? BGFX_STATE_DEPTH_TEST_ALWAYS|BGFX_STATE_WRITE_Z : 0;

			uint64_t stencil = 0;
			stencil |= _clear.m_flags & BGFX_CLEAR_STENCIL ? 0
				| BGFX_STENCIL_TEST_ALWAYS
				| BGFX_STENCIL_FUNC_REF(_clear.m_stencil)
				| BGFX_STENCIL_FUNC_RMASK(0xff)
				| BGFX_STENCIL_OP_FAIL_S_REPLACE
				| BGFX_STENCIL_OP_FAIL_Z_REPLACE
				| BGFX_STENCIL_OP_PASS_Z_REPLACE
				: 0
				;

			uint32_t numMrt = 1;
			FrameBufferHandle fbh = m_fbh;
			if (isValid(fbh) && m_frameBuffers[fbh.idx].m_swapChain == NULL)
			{
				const FrameBufferWgpu& fb = m_frameBuffers[fbh.idx];
				numMrt = bx::uint32_max(1, fb.m_num);
			}

			const VertexLayout* decl = &_clearQuad.m_layout;
			const PipelineStateWgpu* pso = getPipelineState(
				  state
				, stencil
				, 0
				, fbh
				, 1
				, &decl
				, false
				, _clearQuad.m_program[numMrt-1]
				, 0
				);
			m_renderEncoder.SetPipeline(pso->m_rps);

			float mrtClearColor[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS][4];
			float mrtClearDepth[4] = { _clear.m_depth };

			if (BGFX_CLEAR_COLOR_USE_PALETTE & _clear.m_flags)
			{
				for (uint32_t ii = 0; ii < numMrt; ++ii)
				{
					uint8_t index = (uint8_t)bx::uint32_min(BGFX_CONFIG_MAX_COLOR_PALETTE-1, _clear.m_index[ii]);
					bx::memCopy(mrtClearColor[ii], _palette[index], 16);
				}
			}
			else
			{
				float rgba[4] =
				{
					_clear.m_index[0]*1.0f/255.0f,
					_clear.m_index[1]*1.0f/255.0f,
					_clear.m_index[2]*1.0f/255.0f,
					_clear.m_index[3]*1.0f/255.0f,
				};

				for (uint32_t ii = 0; ii < numMrt; ++ii)
				{
					bx::memCopy( mrtClearColor[ii]
								, rgba
								, 16
								);
				}
			}

			ProgramWgpu& program = m_program[_clearQuad.m_program[numMrt - 1].idx];

			//const uint32_t align = uint32_t(m_deviceProperties.limits.minUniformBufferOffsetAlignment);
			const uint32_t align = kMinUniformBufferOffsetAlignment;

			const uint32_t vsize = bx::strideAlign(program.m_vsh->m_size, align);
			const uint32_t fsize = bx::strideAlign((NULL != program.m_fsh ? program.m_fsh->m_size : 0), align);
			//const uint32_t total = vsize + fsize;

			wgpu::BindGroupBinding uniforms[2] = {};

			ScratchBufferWgpu& scratchBuffer = m_scratchBuffers[0];
			const uint32_t voffset = scratchBuffer.m_offset;
			const uint32_t foffset = scratchBuffer.m_offset + vsize;
			scratchBuffer.m_offset += vsize + fsize;

			scratchBuffer.m_buffer.SetSubData(voffset, bx::uint32_min(vsize, sizeof(mrtClearDepth)), (uint8_t*)mrtClearDepth);

			uniforms[0].buffer = scratchBuffer.m_buffer;
			uniforms[0].offset = 0;
			uniforms[0].size = vsize;

			scratchBuffer.m_buffer.SetSubData(foffset, bx::uint32_min(fsize, sizeof(mrtClearColor)), (uint8_t*)mrtClearColor);

			uniforms[1].buffer = scratchBuffer.m_buffer;
			uniforms[1].offset = 0;
			uniforms[1].size = fsize;

			wgpu::BindGroupDescriptor uniformsDesc;
			uniformsDesc.layout = program.m_uniforms;
			uniformsDesc.bindingCount = 2;
			uniformsDesc.bindings = uniforms;

			uint32_t numOffset = 0;
			uint32_t offsets[2] = { voffset, foffset };

			wgpu::BindGroup bindGroup = m_device.CreateBindGroup(&uniformsDesc);
			m_renderEncoder.SetBindGroup(0, bindGroup, numOffset, offsets);


			const VertexBufferWgpu& vb = m_vertexBuffers[_clearQuad.m_vb.idx];

			//m_renderEncoder.SetCullMode(MTLCullModeNone);

			m_renderEncoder.SetVertexBuffer(0, vb.m_ptr);
			m_renderEncoder.Draw(4, 1, 0, 0);
		}

		wgpu::TextureViewDescriptor attachmentView(const Attachment& _at, uint8_t _textureType, bool _resolve)
		{
			BX_UNUSED(_textureType);
			BX_UNUSED(_resolve);

			wgpu::TextureViewDescriptor desc;
			desc.baseMipLevel = _at.mip;
			desc.baseArrayLayer = _at.layer;

			//_attachmentDescriptor.mipLevel = _at.mip;
			//if ( _textureType == TextureWgpu::Texture3D )
			//	_attachmentDescriptor.depthPlane = _at.layer;
			//else
			//	_attachmentDescriptor.arrayLayer = _at.layer;
			//
			//if ( _resolve )
			//{
			//	_attachmentDescriptor.resolveLevel = _at.mip;
			//	if ( _textureType == TextureWgpu::Texture3D )
			//		_attachmentDescriptor.resolveDepthPlane = _at.layer;
			//	else
			//		_attachmentDescriptor.resolveSlice = _at.layer;
			//}

			return desc;
		}

		void setFrameBuffer(RenderPassDescriptor& _renderPassDescriptor, FrameBufferHandle _fbh, bool _msaa = true)
		{
			if (!isValid(_fbh)
			||  m_frameBuffers[_fbh.idx].m_swapChain)
			{
				SwapChainWgpu* swapChain = !isValid(_fbh)
					? m_mainFrameBuffer.m_swapChain
					: m_frameBuffers[_fbh.idx].m_swapChain
					;

				_renderPassDescriptor.colorAttachments[0] = defaultDescriptor<wgpu::RenderPassColorAttachmentDescriptor>();
				_renderPassDescriptor.desc.colorAttachmentCount = 1;

				if (swapChain->m_backBufferColorMsaa)
				{
					_renderPassDescriptor.colorAttachments[0].attachment    = swapChain->m_backBufferColorMsaa.CreateView();
					_renderPassDescriptor.colorAttachments[0].resolveTarget = swapChain->current();
				}
				else
				{
					_renderPassDescriptor.colorAttachments[0].attachment = swapChain->current();
				}

				_renderPassDescriptor.depthStencilAttachment = defaultDescriptor<wgpu::RenderPassDepthStencilAttachmentDescriptor>();
				_renderPassDescriptor.depthStencilAttachment.attachment = swapChain->m_backBufferDepth.CreateView();
				_renderPassDescriptor.desc.depthStencilAttachment = &_renderPassDescriptor.depthStencilAttachment;
			}
			else
			{
				FrameBufferWgpu& frameBuffer = m_frameBuffers[_fbh.idx];

				_renderPassDescriptor.desc.colorAttachmentCount = frameBuffer.m_num;

				for (uint32_t ii = 0; ii < frameBuffer.m_num; ++ii)
				{
					const TextureWgpu& texture = m_textures[frameBuffer.m_colorHandle[ii].idx];

					const wgpu::TextureViewDescriptor desc = attachmentView(frameBuffer.m_colorAttachment[ii], texture.m_type, bool(texture.m_ptrMsaa));

					_renderPassDescriptor.colorAttachments[ii].attachment = texture.m_ptrMsaa
						? texture.m_ptrMsaa.CreateView(&desc)
						: texture.m_ptr.CreateView(&desc)
						;
					_renderPassDescriptor.colorAttachments[ii].resolveTarget = texture.m_ptrMsaa
						? texture.m_ptr.CreateView(&desc)
						: wgpu::TextureView()
						;
				}

				if (isValid(frameBuffer.m_depthHandle) )
				{
					const TextureWgpu& texture = m_textures[frameBuffer.m_depthHandle.idx];
					const wgpu::TextureViewDescriptor desc = attachmentView(frameBuffer.m_depthAttachment, texture.m_type, bool(texture.m_ptrMsaa));

					_renderPassDescriptor.depthStencilAttachment.attachment = texture.m_ptrMsaa
						? texture.m_ptrMsaa.CreateView(&desc)
						: texture.m_ptr.CreateView(&desc)
						;
				}
			}

			m_fbh    = _fbh;
			m_rtMsaa = _msaa;
		}

		void setDepthStencilState(wgpu::DepthStencilStateDescriptor& desc, uint64_t _state, uint64_t _stencil = 0)
		{
			const uint32_t fstencil = unpackStencil(0, _stencil);
			const uint32_t func = (_state&BGFX_STATE_DEPTH_TEST_MASK) >> BGFX_STATE_DEPTH_TEST_SHIFT;

			//_state &= BGFX_STATE_WRITE_Z|BGFX_STATE_DEPTH_TEST_MASK;

			//uint32_t fstencil = unpackStencil(0, _stencil);

			//_stencil &= packStencil(~BGFX_STENCIL_FUNC_REF_MASK, ~BGFX_STENCIL_FUNC_REF_MASK);

			//uint32_t func = (_state&BGFX_STATE_DEPTH_TEST_MASK)>>BGFX_STATE_DEPTH_TEST_SHIFT;
			desc.depthWriteEnabled = !!(BGFX_STATE_WRITE_Z & _state);
			desc.depthCompare = s_cmpFunc[func];

			uint32_t bstencil = unpackStencil(1, _stencil);
			const uint32_t frontAndBack = bstencil != BGFX_STENCIL_NONE && bstencil != fstencil;
			bstencil = frontAndBack ? bstencil : fstencil;

			desc.stencilFront = defaultDescriptor<wgpu::StencilStateFaceDescriptor>();
			desc.stencilBack = defaultDescriptor<wgpu::StencilStateFaceDescriptor>();

			if (0 != _stencil)
			{
				// TODO (hugoam)
				//const uint32_t readMask  = (fstencil&BGFX_STENCIL_FUNC_RMASK_MASK)>>BGFX_STENCIL_FUNC_RMASK_SHIFT;
				//const uint32_t writeMask = 0xff;

				desc.stencilFront.failOp      = s_stencilOp[(fstencil&BGFX_STENCIL_OP_FAIL_S_MASK)>>BGFX_STENCIL_OP_FAIL_S_SHIFT];
				desc.stencilFront.depthFailOp = s_stencilOp[(fstencil&BGFX_STENCIL_OP_FAIL_Z_MASK)>>BGFX_STENCIL_OP_FAIL_Z_SHIFT];
				desc.stencilFront.passOp      = s_stencilOp[(fstencil&BGFX_STENCIL_OP_PASS_Z_MASK)>>BGFX_STENCIL_OP_PASS_Z_SHIFT];
				desc.stencilFront.compare     = s_cmpFunc[(fstencil&BGFX_STENCIL_TEST_MASK)>>BGFX_STENCIL_TEST_SHIFT];
				//desc.stencilFront.readMask  = readMask;
				//desc.stencilFront.writeMask = writeMask;

				desc.stencilBack.failOp      = s_stencilOp[(bstencil&BGFX_STENCIL_OP_FAIL_S_MASK)>>BGFX_STENCIL_OP_FAIL_S_SHIFT];
				desc.stencilBack.depthFailOp = s_stencilOp[(bstencil&BGFX_STENCIL_OP_FAIL_Z_MASK)>>BGFX_STENCIL_OP_FAIL_Z_SHIFT];
				desc.stencilBack.passOp      = s_stencilOp[(bstencil&BGFX_STENCIL_OP_PASS_Z_MASK)>>BGFX_STENCIL_OP_PASS_Z_SHIFT];
				desc.stencilBack.compare     = s_cmpFunc[(bstencil&BGFX_STENCIL_TEST_MASK)>>BGFX_STENCIL_TEST_SHIFT];
				//desc.stencilBack.readMask  = readMask;
				//desc.stencilBack.writeMask = writeMask;
			}
		}

		PipelineStateWgpu* getPipelineState(
			  uint64_t _state
			, uint64_t _stencil
			, uint32_t _rgba
			, FrameBufferHandle _fbh
			, uint8_t _numStreams
			, const VertexLayout** _vertexDecls
			, bool _index32
			, ProgramHandle _program
			, uint8_t _numInstanceData
			)
		{
			_state &= 0
				| BGFX_STATE_WRITE_RGB
				| BGFX_STATE_WRITE_A
				| BGFX_STATE_WRITE_Z
				| BGFX_STATE_DEPTH_TEST_MASK
				| BGFX_STATE_BLEND_MASK
				| BGFX_STATE_BLEND_EQUATION_MASK
				| BGFX_STATE_BLEND_INDEPENDENT
				| BGFX_STATE_BLEND_ALPHA_TO_COVERAGE
				| BGFX_STATE_CULL_MASK
				| BGFX_STATE_MSAA
				| BGFX_STATE_LINEAA
				| BGFX_STATE_CONSERVATIVE_RASTER
				| BGFX_STATE_PT_MASK
				;

			const bool independentBlendEnable = !!(BGFX_STATE_BLEND_INDEPENDENT & _state);
			const ProgramWgpu& program = m_program[_program.idx];

			bx::HashMurmur2A murmur;
			murmur.begin();
			murmur.add(_state);
			murmur.add(_stencil);
			murmur.add(independentBlendEnable ? _rgba : 0);
			murmur.add(_numInstanceData);

			FrameBufferWgpu& frameBuffer = !isValid(_fbh) ? m_mainFrameBuffer : m_frameBuffers[_fbh.idx];
			murmur.add(frameBuffer.m_pixelFormatHash);

			murmur.add(program.m_vsh->m_hash);
			if (NULL != program.m_fsh)
			{
				murmur.add(program.m_fsh->m_hash);
			}

			for (uint8_t ii = 0; ii < _numStreams; ++ii)
			{
				murmur.add(_vertexDecls[ii]->m_hash);
			}

			uint32_t hash = murmur.end();

			PipelineStateWgpu* pso = m_pipelineStateCache.find(hash);

			if (NULL == pso)
			{
				pso = BX_NEW(g_allocator, PipelineStateWgpu);

				//pd.alphaToCoverageEnabled = !!(BGFX_STATE_BLEND_ALPHA_TO_COVERAGE & _state);

				RenderPipelineDescriptor& pd = pso->m_rpd;

				uint32_t frameBufferAttachment = 1;
				uint32_t sampleCount = 1;

				if (!isValid(_fbh)
				||  s_renderWgpu->m_frameBuffers[_fbh.idx].m_swapChain)
				{
					SwapChainWgpu& swapChain = !isValid(_fbh)
						? *s_renderWgpu->m_mainFrameBuffer.m_swapChain
						: *s_renderWgpu->m_frameBuffers[_fbh.idx].m_swapChain
						;
					sampleCount = swapChain.m_backBufferColorMsaa
						? swapChain.m_sampleCount
						: 1
						;
					pd.colorStates[0].format = swapChain.m_colorFormat;
					pd.depthStencilState.format = swapChain.m_depthFormat;
				}
				else
				{
					//const FrameBufferWgpu& frameBuffer = m_frameBuffers[_fbh.idx];
					frameBufferAttachment = frameBuffer.m_num;

					for (uint32_t ii = 0; ii < frameBuffer.m_num; ++ii)
					{
						const TextureWgpu& texture = m_textures[frameBuffer.m_colorHandle[ii].idx];
						sampleCount = texture.m_ptrMsaa
							? texture.m_sampleCount
							: 1
							;
						pd.colorStates[0].format = s_textureFormat[texture.m_textureFormat];
					}

					if (isValid(frameBuffer.m_depthHandle) )
					{
						const TextureWgpu& texture = m_textures[frameBuffer.m_depthHandle.idx];
						pd.depthStencilState.format = s_textureFormat[texture.m_textureFormat];
					}
				}

				const uint32_t blend    = uint32_t( (_state&BGFX_STATE_BLEND_MASK         )>>BGFX_STATE_BLEND_SHIFT);
				const uint32_t equation = uint32_t( (_state&BGFX_STATE_BLEND_EQUATION_MASK)>>BGFX_STATE_BLEND_EQUATION_SHIFT);

				const uint32_t srcRGB = (blend    )&0xf;
				const uint32_t dstRGB = (blend>> 4)&0xf;
				const uint32_t srcA   = (blend>> 8)&0xf;
				const uint32_t dstA   = (blend>>12)&0xf;

				const uint32_t equRGB = (equation   )&0x7;
				const uint32_t equA   = (equation>>3)&0x7;

				wgpu::ColorWriteMask writeMask = wgpu::ColorWriteMask::None;
				writeMask |= (_state&BGFX_STATE_WRITE_R) ? wgpu::ColorWriteMask::Red   : wgpu::ColorWriteMask::None;
				writeMask |= (_state&BGFX_STATE_WRITE_G) ? wgpu::ColorWriteMask::Green : wgpu::ColorWriteMask::None;
				writeMask |= (_state&BGFX_STATE_WRITE_B) ? wgpu::ColorWriteMask::Blue  : wgpu::ColorWriteMask::None;
				writeMask |= (_state&BGFX_STATE_WRITE_A) ? wgpu::ColorWriteMask::Alpha : wgpu::ColorWriteMask::None;

				for (uint32_t ii = 0; ii < (independentBlendEnable ? 1 : frameBufferAttachment); ++ii)
				{
					wgpu::ColorStateDescriptor& drt = pd.colorStates[ii]; // = pd.colorAttachments[ii];

					if(!(BGFX_STATE_BLEND_MASK & _state))
					{
						drt.colorBlend = defaultDescriptor<wgpu::BlendDescriptor>();
						drt.alphaBlend = defaultDescriptor<wgpu::BlendDescriptor>();
					}
					else
					{
						drt.colorBlend.srcFactor = s_blendFactor[srcRGB][0];
						drt.colorBlend.dstFactor = s_blendFactor[dstRGB][0];
						drt.colorBlend.operation = s_blendEquation[equRGB];

						drt.alphaBlend.srcFactor = s_blendFactor[srcA][1];
						drt.alphaBlend.dstFactor = s_blendFactor[dstA][1];
						drt.alphaBlend.operation = s_blendEquation[equA];
					}

					drt.writeMask = writeMask;
				}

				if (independentBlendEnable)
				{
					for (uint32_t ii = 1, rgba = _rgba; ii < frameBufferAttachment; ++ii, rgba >>= 11)
					{
						wgpu::ColorStateDescriptor drt = pd.colorStates[ii]; // = pd.colorAttachments[ii];

						//drt.blendingEnabled = 0 != (rgba&0x7ff);

						const uint32_t src           = (rgba   )&0xf;
						const uint32_t dst           = (rgba>>4)&0xf;
						const uint32_t equationIndex = (rgba>>8)&0x7;
						
						drt.colorBlend.srcFactor  = s_blendFactor[src][0];
						drt.colorBlend.dstFactor  = s_blendFactor[dst][0];
						drt.colorBlend.operation  = s_blendEquation[equationIndex];

						drt.alphaBlend.srcFactor  = s_blendFactor[src][1];
						drt.alphaBlend.dstFactor  = s_blendFactor[dst][1];
						drt.alphaBlend.operation  = s_blendEquation[equationIndex];

						drt.writeMask = writeMask;
					}
				}

				pd.desc.vertexStage.module = program.m_vsh->m_module;
				pd.fragmentStage.module = program.m_fsh != NULL ? program.m_fsh->m_module : wgpu::ShaderModule();

				wgpu::PipelineLayoutDescriptor layout = defaultDescriptor<wgpu::PipelineLayoutDescriptor>();
				layout.bindGroupLayouts = &program.m_uniforms;
				layout.bindGroupLayoutCount = 3;

				setDepthStencilState(pd.depthStencilState, _state, _stencil);

				const uint64_t cull = _state & BGFX_STATE_CULL_MASK;
				const uint8_t cullIndex = uint8_t(cull >> BGFX_STATE_CULL_SHIFT);
				pd.rasterizationState.cullMode = s_cullMode[cullIndex];

				// pd.desc = m_renderPipelineDescriptor;
				pd.desc.sampleCount = sampleCount;
				pd.desc.depthStencilState = &pd.depthStencilState;

				pd.desc.layout = m_device.CreatePipelineLayout(&layout);
				// @todo this should be cached too

				//uint32_t ref = (_state&BGFX_STATE_ALPHA_REF_MASK) >> BGFX_STATE_ALPHA_REF_SHIFT;
				//viewState.m_alphaRef = ref / 255.0f;

				//const uint64_t primType = 0; // TODO
				const uint64_t pt = _state & BGFX_STATE_PT_MASK;
				uint8_t primIndex = uint8_t(pt >> BGFX_STATE_PT_SHIFT);

				PrimInfo prim = s_primInfo[primIndex];
				pd.desc.primitiveTopology = prim.m_type;

				auto fillVertexDecl = [](const ShaderWgpu* _vsh, VertexStateDescriptor& _vertexInputState, const VertexLayout& _decl)
				{
					wgpu::VertexBufferLayoutDescriptor* inputBinding = _vertexInputState.vertexBuffers;

					// TODO (webgpu)

					//inputBinding->binding = 0;
					//inputBinding->inputSlot = 0;
					inputBinding->arrayStride = _decl.m_stride;
					inputBinding->stepMode = wgpu::InputStepMode::Vertex;
					_vertexInputState.desc.vertexBufferCount = 1;

					uint32_t numAttribs = 0;
					wgpu::VertexAttributeDescriptor* inputAttrib = _vertexInputState.attributes;

					for(uint32_t attr = 0; attr < Attrib::Count; ++attr)
					{
						//Attrib::Enum attrib = Attrib::Enum(attr);

						if(UINT16_MAX != _decl.m_attributes[attr])
						{
							if(UINT8_MAX == _vsh->m_attrRemap[attr])
								continue;

							inputAttrib->shaderLocation = _vsh->m_attrRemap[attr];
							//inputAttrib->inputSlot = 0;
							//inputAttrib->location = _vsh->m_attrRemap[attr];
							//inputAttrib->binding = 0;

							if(0 == _decl.m_attributes[attr])
							{
								inputAttrib->format = wgpu::VertexFormat::Float3;
								inputAttrib->offset = 0;
							}
							else
							{
								uint8_t num;
								AttribType::Enum type;
								bool normalized;
								bool asInt;
								_decl.decode(Attrib::Enum(attr), num, type, normalized, asInt);
								inputAttrib->format = s_attribType[type][num-1][normalized];
								inputAttrib->offset = _decl.m_offset[attr];
							}

							++inputAttrib;
							++numAttribs;
						}
					}

					inputBinding->attributeCount = numAttribs;

					return numAttribs;
				};

				VertexStateDescriptor input;

				//bool attrSet[Attrib::Count] = {};

				uint8_t stream = 0;
				//for (; stream < _numStreams; ++stream)
				{
					const VertexLayout& vertexDecl = *_vertexDecls[stream];
					fillVertexDecl(program.m_vsh, input, vertexDecl);

					//input.inputs[stream+1].stride   = vertexDecl.getStride();
					//input.inputs[stream+1].stepMode = wgpu::InputStepMode::Vertex;
				}

				//if (0 < _numInstanceData)
				//{
				//	for (uint32_t ii = 0; UINT16_MAX != program.m_instanceData[ii]; ++ii)
				//	{
				//		const uint32_t loc = program.m_instanceData[ii];
				//		wgpu::VertexAttributeDescriptor& attrDesc = input.attributes[loc];
				//		attrDesc.format         = wgpu::VertexFormat::Float4;
				//		attrDesc.inputSlot      = stream+1;
				//		attrDesc.shaderLocation = loc;
				//		attrDesc.offset         = ii*16;
				//		input.numAttributes++;
				//	}
				//
				//	input.inputs[stream+1].stride   = _numInstanceData * 16;
				//	input.inputs[stream+1].stepMode = wgpu::InputStepMode::Instance;
				//	//inputs[stream+1].stepRate = 1;
				//}

				input.desc.indexFormat = _index32 ? wgpu::IndexFormat::Uint32 : wgpu::IndexFormat::Uint16;

				pd.desc.vertexState = &input.desc;

				pso->m_rps = m_device.CreateRenderPipeline(&pd.desc);

				m_pipelineStateCache.add(hash, pso);
			}

			return pso;
		}

		PipelineStateWgpu* getPipelineState(
			  uint64_t _state
			, uint64_t _stencil
			, uint32_t _rgba
			, FrameBufferHandle _fbh
			, VertexLayoutHandle _declHandle
			, bool _index32
			, ProgramHandle _program
			, uint8_t _numInstanceData
			)
		{
			const VertexLayout* decl = &m_vertexDecls[_declHandle.idx];
			return getPipelineState(
				  _state
				, _stencil
				, _rgba
				, _fbh
				, 1
				, &decl
				, _index32
				, _program
				, _numInstanceData
				);
		}

		PipelineStateWgpu* getComputePipelineState(ProgramHandle _program)
		{
			ProgramWgpu& program = m_program[_program.idx];

			if (NULL == program.m_computePS)
			{
				PipelineStateWgpu* pso = BX_NEW(g_allocator, PipelineStateWgpu);
				program.m_computePS = pso;

				wgpu::ComputePipelineDescriptor desc;
				pso->m_cps = m_device.CreateComputePipeline(&desc);

				for (uint32_t ii = 0; ii < 3; ++ii)
				{
					pso->m_numThreads[ii] = program.m_vsh->m_numThreads[ii];
				}
			}

			return program.m_computePS;
		}


		wgpu::Sampler getSamplerState(uint32_t _flags)
		{
			_flags &= BGFX_SAMPLER_BITS_MASK;
			SamplerStateWgpu* sampler = m_samplerStateCache.find(_flags);

			if (NULL == sampler)
			{
				sampler = BX_NEW(g_allocator, SamplerStateWgpu);

				wgpu::SamplerDescriptor desc;
				desc.addressModeU = s_textureAddress[(_flags&BGFX_SAMPLER_U_MASK)>>BGFX_SAMPLER_U_SHIFT];
				desc.addressModeV = s_textureAddress[(_flags&BGFX_SAMPLER_V_MASK)>>BGFX_SAMPLER_V_SHIFT];
				desc.addressModeW = s_textureAddress[(_flags&BGFX_SAMPLER_W_MASK)>>BGFX_SAMPLER_W_SHIFT];
				desc.minFilter    = s_textureFilterMinMag[(_flags&BGFX_SAMPLER_MIN_MASK)>>BGFX_SAMPLER_MIN_SHIFT];
				desc.magFilter    = s_textureFilterMinMag[(_flags&BGFX_SAMPLER_MAG_MASK)>>BGFX_SAMPLER_MAG_SHIFT];
				desc.mipmapFilter = s_textureFilterMip[(_flags&BGFX_SAMPLER_MIP_MASK)>>BGFX_SAMPLER_MIP_SHIFT];
				desc.lodMinClamp  = 0;
				desc.lodMaxClamp  = FLT_MAX;
				//m_samplerDescriptor.normalizedCoordinates = TRUE;
				//m_samplerDescriptor.maxAnisotropy =  (0 != (_flags & (BGFX_SAMPLER_MIN_ANISOTROPIC|BGFX_SAMPLER_MAG_ANISOTROPIC) ) ) ? m_mainFrameBuffer.m_swapChain->m_maxAnisotropy : 1;

				const uint32_t cmpFunc = (_flags&BGFX_SAMPLER_COMPARE_MASK)>>BGFX_SAMPLER_COMPARE_SHIFT;
				desc.compare = 0 == cmpFunc
					? wgpu::CompareFunction::Never
					: s_cmpFunc[cmpFunc]
					;

				sampler->m_sampler = s_renderWgpu->m_device.CreateSampler(&desc);
				m_samplerStateCache.add(_flags, sampler);
			}

			return sampler->m_sampler;
		}

		bool isVisible(Frame* _render, OcclusionQueryHandle _handle, bool _visible)
		{
			m_occlusionQuery.resolve(_render);
			return _visible == (0 != _render->m_occlusion[_handle.idx]);
		}

		wgpu::CommandEncoder& getBlitCommandEncoder()
		{
			if (!m_cmd.m_encoder)
				m_cmd.begin();

			if (m_renderEncoder || m_computeEncoder)
				endEncoding();

			return m_cmd.m_encoder;
		}

		wgpu::RenderPassEncoder renderPass(bgfx::Frame* _render, bgfx::FrameBufferHandle fbh, bool clear, Clear clr)
		{
			RenderPassDescriptor renderPassDescriptor;
			//renderPassDescriptor.visibilityResultBuffer = m_occlusionQuery.m_buffer;

			setFrameBuffer(renderPassDescriptor, fbh);

			if(clear)
			{
				for(uint32_t ii = 0; ii < g_caps.limits.maxFBAttachments; ++ii)
				{
					wgpu::RenderPassColorAttachmentDescriptor& color = renderPassDescriptor.colorAttachments[ii];

					if(0 != (BGFX_CLEAR_COLOR & clr.m_flags))
					{
						if(0 != (BGFX_CLEAR_COLOR_USE_PALETTE & clr.m_flags))
						{
							uint8_t index = (uint8_t)bx::uint32_min(BGFX_CONFIG_MAX_COLOR_PALETTE - 1, clr.m_index[ii]);
							const float* rgba = _render->m_colorPalette[index];
							const float rr = rgba[0];
							const float gg = rgba[1];
							const float bb = rgba[2];
							const float aa = rgba[3];
							color.clearColor = { rr, gg, bb, aa };
						}
						else
						{
							float rr = clr.m_index[0] * 1.0f / 255.0f;
							float gg = clr.m_index[1] * 1.0f / 255.0f;
							float bb = clr.m_index[2] * 1.0f / 255.0f;
							float aa = clr.m_index[3] * 1.0f / 255.0f;
							color.clearColor = { rr, gg, bb, aa };
						}

						color.loadOp = wgpu::LoadOp::Clear;
					}
					else
					{
						color.loadOp = wgpu::LoadOp::Load;
					}

					//desc.storeOp = desc.attachment.sampleCount > 1 ? wgpu::StoreOp::MultisampleResolve : wgpu::StoreOp::Store;
					color.storeOp = wgpu::StoreOp::Store;
				}

				wgpu::RenderPassDepthStencilAttachmentDescriptor& depthStencil = renderPassDescriptor.depthStencilAttachment;

				if(depthStencil.attachment)
				{
					depthStencil.clearDepth = clr.m_depth;
					depthStencil.depthLoadOp = 0 != (BGFX_CLEAR_DEPTH & clr.m_flags)
						? wgpu::LoadOp::Clear
						: wgpu::LoadOp::Load
						;
					depthStencil.depthStoreOp = m_mainFrameBuffer.m_swapChain->m_backBufferColorMsaa
						? wgpu::StoreOp(0) //wgpu::StoreOp::DontCare
						: wgpu::StoreOp::Store
						;

					depthStencil.clearStencil = clr.m_stencil;
					depthStencil.stencilLoadOp = 0 != (BGFX_CLEAR_STENCIL & clr.m_flags)
						? wgpu::LoadOp::Clear
						: wgpu::LoadOp::Load
						;
					depthStencil.stencilStoreOp = m_mainFrameBuffer.m_swapChain->m_backBufferColorMsaa
						? wgpu::StoreOp(0) //wgpu::StoreOp::DontCare
						: wgpu::StoreOp::Store
						;
				}
			}
			else
			{
				for(uint32_t ii = 0; ii < g_caps.limits.maxFBAttachments; ++ii)
				{
					wgpu::RenderPassColorAttachmentDescriptor& color = renderPassDescriptor.colorAttachments[ii];
					if(color.attachment)
					{
						color.loadOp = wgpu::LoadOp::Load;
					}
				}

				wgpu::RenderPassDepthStencilAttachmentDescriptor& depthStencil = renderPassDescriptor.depthStencilAttachment;

				if(depthStencil.attachment)
				{
					depthStencil.depthLoadOp = wgpu::LoadOp::Load;
					depthStencil.depthStoreOp = wgpu::StoreOp::Store;

					depthStencil.stencilLoadOp = wgpu::LoadOp::Load;
					depthStencil.stencilStoreOp = wgpu::StoreOp::Store;
				}
			}

			wgpu::RenderPassEncoder rce = m_cmd.m_encoder.BeginRenderPass(&renderPassDescriptor.desc);
			m_renderEncoder = rce;
			m_renderCommandEncoderFrameBufferHandle = fbh;
			return rce;
		}

		void endEncoding()
		{
			if (m_renderEncoder)
			{
				m_renderEncoder.EndPass();
				m_renderEncoder = 0;
			}

			if (m_computeEncoder)
			{
				m_computeEncoder.EndPass();
				m_computeEncoder = 0;
			}

			//if (0 != m_blitCommandEncoder)
			//{
			//	m_blitCommandEncoder.endEncoding();
			//	m_blitCommandEncoder = 0;
			//}
		}

		void* m_renderDocDll;

#if !BX_PLATFORM_EMSCRIPTEN
		dawn_native::Instance m_instance;
#endif
		wgpu::Device       m_device;
		wgpu::Queue        m_queue;
		OcclusionQueryWgpu m_occlusionQuery;
		TimerQueryWgpu     m_gpuTimer;
		CommandQueueWgpu   m_cmd;

		ScratchBufferWgpu  m_scratchBuffers[WEBGPU_MAX_FRAMES_IN_FLIGHT];

		uint8_t  m_bufferIndex;

		uint16_t          m_numWindows;
		FrameBufferHandle m_windows[BGFX_CONFIG_MAX_FRAME_BUFFERS];

		IndexBufferWgpu  m_indexBuffers[BGFX_CONFIG_MAX_INDEX_BUFFERS];
		VertexBufferWgpu m_vertexBuffers[BGFX_CONFIG_MAX_VERTEX_BUFFERS];
		ShaderWgpu       m_shaders[BGFX_CONFIG_MAX_SHADERS];
		ProgramWgpu      m_program[BGFX_CONFIG_MAX_PROGRAMS];
		TextureWgpu      m_textures[BGFX_CONFIG_MAX_TEXTURES];
		FrameBufferWgpu  m_mainFrameBuffer;
		FrameBufferWgpu  m_frameBuffers[BGFX_CONFIG_MAX_FRAME_BUFFERS];
		VertexLayout     m_vertexDecls[BGFX_CONFIG_MAX_VERTEX_LAYOUTS];
		UniformRegistry  m_uniformReg;
		void*            m_uniforms[BGFX_CONFIG_MAX_UNIFORMS];

		StateCacheT<BindStateWgpu*>		m_bindStateCache;
		StateCacheT<PipelineStateWgpu*> m_pipelineStateCache;
		StateCacheT<SamplerStateWgpu*>  m_samplerStateCache;

		TextVideoMem m_textVideoMem;

		uint8_t m_fsScratch[64 << 10];
		uint8_t m_vsScratch[64 << 10];

		FrameBufferHandle m_fbh;
		bool m_rtMsaa;

		Resolution m_resolution;
		void* m_capture;
		uint32_t m_captureSize;

		wgpu::RenderPassEncoder     m_renderEncoder;
		wgpu::ComputePassEncoder    m_computeEncoder;
		FrameBufferHandle    m_renderCommandEncoderFrameBufferHandle;
	};

	RendererContextI* rendererCreate(const Init& _init)
	{
		s_renderWgpu = BX_NEW(g_allocator, RendererContextWgpu);
		if (!s_renderWgpu->init(_init) )
		{
			BX_DELETE(g_allocator, s_renderWgpu);
			s_renderWgpu = NULL;
		}
		return s_renderWgpu;
	}

	void rendererDestroy()
	{
		s_renderWgpu->shutdown();
		BX_DELETE(g_allocator, s_renderWgpu);
		s_renderWgpu = NULL;
	}

	void writeString(bx::WriterI* _writer, const char* _str)
	{
		bx::write(_writer, _str, (int32_t)bx::strLen(_str) );
	}

	void ShaderWgpu::create(ShaderHandle _handle, const Memory* _mem)
	{
		m_handle = _handle;

		BX_TRACE("Creating shader %s", getName(_handle).getPtr());

		bx::MemoryReader reader(_mem->data, _mem->size);

		uint32_t magic;
		bx::read(&reader, magic);

		uint32_t hashIn;
		bx::read(&reader, hashIn);

		uint32_t hashOut;

		if (isShaderVerLess(magic, 6) )
		{
			hashOut = hashIn;
		}
		else
		{
			bx::read(&reader, hashOut);
		}

		uint16_t count;
		bx::read(&reader, count);

		m_numPredefined = 0;
		m_numUniforms = count;

		BX_TRACE("%s Shader consts %d"
			, getShaderTypeName(magic)
			, count
			);

		const bool fragment = isShaderType(magic, 'F');
		uint8_t fragmentBit = fragment ? BGFX_UNIFORM_FRAGMENTBIT : 0;

		//uint8_t lastSampler;
		//uint8_t numSamplers;

		if (0 < count)
		{
			for (uint32_t ii = 0; ii < count; ++ii)
			{
				uint8_t nameSize = 0;
				bx::read(&reader, nameSize);

				char name[256];
				bx::read(&reader, &name, nameSize);
				name[nameSize] = '\0';

				uint8_t type = 0;
				bx::read(&reader, type);

				uint8_t num;
				bx::read(&reader, num);

				uint16_t regIndex;
				bx::read(&reader, regIndex);

				uint16_t regCount;
				bx::read(&reader, regCount);

				const char* kind = "invalid";

				PredefinedUniform::Enum predefined = nameToPredefinedUniformEnum(name);
				if (PredefinedUniform::Count != predefined)
				{
					kind = "predefined";
					m_predefined[m_numPredefined].m_loc   = regIndex;
					m_predefined[m_numPredefined].m_count = regCount;
					m_predefined[m_numPredefined].m_type  = uint8_t(predefined|fragmentBit);
					m_numPredefined++;
				}
				else
				{
					const UniformRegInfo* info = s_renderWgpu->m_uniformReg.find(name);
					BX_CHECK(NULL != info, "User defined uniform '%s' is not found, it won't be set.", name);

					if(0 == (BGFX_UNIFORM_SAMPLERBIT & type))
					{
						if(NULL != info)
						{
							const UniformSet::Enum freq = info->m_freq;
							if(NULL == m_constantBuffer[freq])
							{
								m_constantBuffer[freq] = UniformBuffer::create(1024);
							}

							kind = "user";
							m_constantBuffer[freq]->writeUniformHandle((UniformType::Enum)(type | fragmentBit), regIndex, info->m_handle, regCount);
						}
					}
					else
					{
						kind = "sampler";

						//BX_TRACE("\tsampler binding: %2d", regIndex);

						m_samplers[m_numSamplers] = { regIndex, wgpu::ShaderStage::Fragment, wgpu::BindingType::Sampler };
						m_textures[m_numSamplers] = { regIndex, wgpu::ShaderStage::Fragment, wgpu::BindingType::SampledTexture };

						if(NULL != info)
						{
							//m_samplerInfo[m_numSamplers].m_index = uint32_t(arg.index);
							m_samplerInfo[m_numSamplers].m_uniform = info->m_handle;
							m_samplerInfo[m_numSamplers].m_fragment = fragmentBit ? 1 : 0;
							BX_TRACE("texture %s %d index:%d", name, info->m_handle.idx, 0); // uint32_t(arg.index));
						}

						m_numSamplers++;
					}
				}

				BX_TRACE("\t%s: %s (%s), num %2d, r.index %3d, r.count %2d"
					, kind
					, name
					, getUniformTypeName(UniformType::Enum(type&~BGFX_UNIFORM_MASK) )
					, num
					, regIndex
					, regCount
					);
				BX_UNUSED(kind);
			}

			for (uint32_t ii = 0; ii < UniformSet::Count; ++ii)
			{
				if (NULL != m_constantBuffer[ii])
				{
					m_constantBuffer[ii]->finish();
				}
			}
		}

		if (isShaderType(magic, 'C'))
		{
			for (uint32_t ii = 0; ii < 3; ++ii)
			{
				bx::read(&reader, m_numThreads[ii]);
			}
		}

		uint32_t shaderSize;
		bx::read(&reader, shaderSize);

		BX_TRACE("Shader body is at %i size %i remaining %i", reader.getPos(), shaderSize, reader.remaining());

		const uint32_t* code = (const uint32_t*)reader.getDataPtr();
		bx::skip(&reader, shaderSize+1);

		m_code = (uint32_t*)BX_ALLOC(g_allocator, shaderSize);
		m_codeSize = shaderSize;

		bx::memCopy(m_code, code, shaderSize);
		// TODO (hugoam) delete this

		BX_TRACE("First word %08" PRIx32, code[0]);
		BX_TRACE("Remaining %i", reader.remaining());

		uint8_t numAttrs = 0;
		bx::read(&reader, numAttrs);

		m_numAttrs = numAttrs;

		bx::memSet(m_attrMask, 0, sizeof(m_attrMask));
		bx::memSet(m_attrRemap, UINT8_MAX, sizeof(m_attrRemap));

		for(uint8_t ii = 0; ii < numAttrs; ++ii)
		{
			uint16_t id;
			bx::read(&reader, id);

			auto toString = [](Attrib::Enum attr)
			{
				if (attr == Attrib::Position) return "Position";
				else if (attr == Attrib::Normal) return "Normal";
				else if (attr == Attrib::Tangent) return "Tangent";
				else if (attr == Attrib::Bitangent) return "Bitangent";
				else if (attr == Attrib::Color0) return "Color0";
				else if (attr == Attrib::Color1) return "Color1";
				else if (attr == Attrib::Color2) return "Color2";
				else if (attr == Attrib::Color3) return "Color3";
				else if (attr == Attrib::Indices) return "Indices";
				else if (attr == Attrib::Weight) return "Weight";
				else if (attr == Attrib::TexCoord0) return "TexCoord0";
				else if (attr == Attrib::TexCoord1) return "TexCoord1";
				else if (attr == Attrib::TexCoord2) return "TexCoord2";
				else if (attr == Attrib::TexCoord3) return "TexCoord3";
				else if (attr == Attrib::TexCoord4) return "TexCoord4";
				else if (attr == Attrib::TexCoord5) return "TexCoord5";
				else if (attr == Attrib::TexCoord6) return "TexCoord6";
				else if (attr == Attrib::TexCoord7) return "TexCoord7";
				return "Invalid";
			};

			Attrib::Enum attr = idToAttrib(id);

			if(Attrib::Count != attr)
			{
				m_attrMask[attr] = UINT16_MAX;
				m_attrRemap[attr] = ii;
				BX_TRACE("\tattrib: %s (%i) at index %i", toString(attr), attr, ii);
			}
		}

		wgpu::ShaderModuleDescriptor desc;
		desc.code = code;
		desc.codeSize = shaderSize/4;

		m_module = s_renderWgpu->m_device.CreateShaderModule(&desc);
		
		BGFX_FATAL(m_module
			, bgfx::Fatal::InvalidShader
			, "Failed to create %s shader."
			, getShaderTypeName(magic)
			);

		bx::HashMurmur2A murmur;
		murmur.begin();
		murmur.add(hashIn);
		murmur.add(hashOut);
		murmur.add(code, shaderSize);
		murmur.add(numAttrs);
		murmur.add(m_attrMask, numAttrs);
		m_hash = murmur.end();

		auto roundUp = [](auto value, auto multiple)
		{
			return ((value + multiple - 1) / multiple) * multiple;
		};

		bx::read(&reader, m_size);
		m_size = roundUp(m_size, 4);
	}

	void ProgramWgpu::create(const ShaderWgpu* _vsh, const ShaderWgpu* _fsh)
	{
		BX_CHECK(_vsh->m_module, "Vertex shader doesn't exist.");
		m_vsh = _vsh;
		m_fsh = _fsh;

		//BX_CHECK(NULL != _vsh->m_code, "Vertex shader doesn't exist.");
		m_vsh = _vsh;
		bx::memCopy(&m_predefined[0], _vsh->m_predefined, _vsh->m_numPredefined * sizeof(PredefinedUniform));
		m_numPredefined = _vsh->m_numPredefined;

		if(NULL != _fsh)
		{
			//BX_CHECK(NULL != _fsh->m_code, "Fragment shader doesn't exist.");
			m_fsh = _fsh;
			bx::memCopy(&m_predefined[m_numPredefined], _fsh->m_predefined, _fsh->m_numPredefined * sizeof(PredefinedUniform));
			m_numPredefined += _fsh->m_numPredefined;
		}

		wgpu::BindGroupLayoutBinding uniforms[2];
		m_numUniforms = 0 + (_vsh->m_size > 0 ? 1 : 0) + (NULL != _fsh && _fsh->m_size > 0 ? 1 : 0);

		// bind uniform buffer at slot 0
		uniforms[0].binding = 0;
		uniforms[0].visibility = wgpu::ShaderStage::Vertex;
		uniforms[0].type = wgpu::BindingType::UniformBuffer;
		uniforms[0].hasDynamicOffset = true;

		if (m_numUniforms > 1)
		{
			uniforms[1].binding = 1;
			uniforms[1].visibility = wgpu::ShaderStage::Fragment;
			uniforms[1].type = wgpu::BindingType::UniformBuffer;
			uniforms[1].hasDynamicOffset = true;
		}

		wgpu::BindGroupLayoutBinding textures[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];
		wgpu::BindGroupLayoutBinding samplers[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];
		uint8_t numSamplers = 0;

		for (uint32_t ii = 0; ii < _vsh->m_numSamplers; ++ii)
		{
			textures[ii] = _vsh->m_textures[ii];
			samplers[ii] = _vsh->m_samplers[ii];
			m_samplerInfo[ii] = _vsh->m_samplerInfo[ii];
		}

		numSamplers += _vsh->m_numSamplers;

		for (uint32_t ii = 0; ii < _fsh->m_numSamplers; ++ii)
		{
			textures[numSamplers+ii] = _fsh->m_textures[ii];
			samplers[numSamplers+ii] = _fsh->m_samplers[ii];
			m_samplerInfo[numSamplers+ii] = _fsh->m_samplerInfo[ii];
		}

		numSamplers += _fsh->m_numSamplers;
		m_numSamplers = numSamplers;

		wgpu::BindGroupLayoutDescriptor uniformsDesc;
		uniformsDesc.bindingCount = m_numUniforms;
		uniformsDesc.bindings = uniforms;
		m_uniforms = s_renderWgpu->m_device.CreateBindGroupLayout(&uniformsDesc);

		wgpu::BindGroupLayoutDescriptor samplersDesc;
		samplersDesc.bindingCount = numSamplers;
		samplersDesc.bindings = samplers;
		m_samplers = s_renderWgpu->m_device.CreateBindGroupLayout(&samplersDesc);

		wgpu::BindGroupLayoutDescriptor texturesDesc;
		texturesDesc.bindingCount = numSamplers;
		texturesDesc.bindings = textures;
		m_textures = s_renderWgpu->m_device.CreateBindGroupLayout(&texturesDesc);

		bx::HashMurmur2A murmur;
		murmur.begin();
		murmur.add(m_numUniforms);
		murmur.add(textures, sizeof(wgpu::BindGroupLayoutBinding) * numSamplers);
		murmur.add(samplers, sizeof(wgpu::BindGroupLayoutBinding) * numSamplers);
		m_bindGroupLayoutHash = murmur.end();
	}

	void ProgramWgpu::destroy()
	{
		m_vsh = NULL;
		m_fsh = NULL;
		if ( NULL != m_computePS )
		{
			BX_DELETE(g_allocator, m_computePS);
			m_computePS = NULL;
		}
	}

	void BufferWgpu::create(uint32_t _size, void* _data, uint16_t _flags, uint16_t _stride, bool _vertex)
	{
		BX_UNUSED(_stride);

		m_size = _size;
		m_flags = _flags;
		m_vertex = _vertex;

		const uint32_t paddedSize = (_size % 4 == 0) ? _size : _size + 2;

		wgpu::BufferDescriptor desc;
		desc.size = paddedSize;
		desc.usage = _vertex ? wgpu::BufferUsage::Vertex : wgpu::BufferUsage::Index;
		desc.usage |= wgpu::BufferUsage::CopyDst;

		m_ptr = s_renderWgpu->m_device.CreateBuffer(&desc);

		if(NULL != _data)
		{
			if(_size % 4 != 0)
			{
				uint8_t* temp = (uint8_t*)BX_ALLOC(g_allocator, paddedSize);
				bx::memCopy(temp, _data, _size);
				m_ptr.SetSubData(0, paddedSize, temp);
				BX_FREE(g_allocator, temp);
			}
			else
			{
				m_ptr.SetSubData(0, _size, (const uint8_t*)_data);
			}
		}
	}

	void BufferWgpu::update(uint32_t _offset, uint32_t _size, void* _data, bool _discard)
	{
		wgpu::CommandEncoder& bce = s_renderWgpu->getBlitCommandEncoder();

		if (!m_vertex && !_discard)
		{
			if ( m_dynamic == NULL )
			{
				m_dynamic = (uint8_t*)BX_ALLOC(g_allocator, m_size);
			}

			bx::memCopy(m_dynamic + _offset, _data, _size);
			uint32_t start = _offset & 4;
			uint32_t end = bx::strideAlign(_offset + _size, 4);

			wgpu::BufferDescriptor desc;
			desc.size = end - start;
			desc.usage = wgpu::BufferUsage::CopyDst | wgpu::BufferUsage::CopySrc;

			wgpu::Buffer staging = s_renderWgpu->m_device.CreateBuffer(&desc); // m_dynamic, , 0);
			staging.SetSubData(0, _size, reinterpret_cast<const uint8_t*>(_data));

			bce.CopyBufferToBuffer(staging, 0, m_ptr, start, end - start);
			s_renderWgpu->m_cmd.release(staging);
		}
		else
		{
			wgpu::BufferDescriptor desc;
			desc.size = _size;
			desc.usage = wgpu::BufferUsage::CopyDst | wgpu::BufferUsage::CopySrc;

			wgpu::Buffer staging = s_renderWgpu->m_device.CreateBuffer(&desc);
			staging.SetSubData(0, _size, reinterpret_cast<const uint8_t*>(_data));

			bce.CopyBufferToBuffer(staging, 0, m_ptr, _offset, _size);
			s_renderWgpu->m_cmd.release(staging);
		}
	}

	void VertexBufferWgpu::create(uint32_t _size, void* _data, VertexLayoutHandle _layoutHandle, uint16_t _flags)
	{
		m_layoutHandle = _layoutHandle;
		uint16_t stride = isValid(_layoutHandle)
			? s_renderWgpu->m_vertexDecls[_layoutHandle.idx].m_stride
			: 0
			;

		BufferWgpu::create(_size, _data, _flags, stride, true);
	}

	void TextureWgpu::create(const Memory* _mem, uint64_t _flags, uint8_t _skip)
	{
		m_sampler = s_renderWgpu->getSamplerState(uint32_t(_flags) );

		bimg::ImageContainer imageContainer;

		if (bimg::imageParse(imageContainer, _mem->data, _mem->size) )
		{
			const bimg::ImageBlockInfo& blockInfo = getBlockInfo(bimg::TextureFormat::Enum(imageContainer.m_format) );
			const uint8_t startLod = bx::min<uint8_t>(_skip, imageContainer.m_numMips-1);

			bimg::TextureInfo ti;
			bimg::imageGetSize(
				  &ti
				, uint16_t(imageContainer.m_width >>startLod)
				, uint16_t(imageContainer.m_height>>startLod)
				, uint16_t(imageContainer.m_depth >>startLod)
				, imageContainer.m_cubeMap
				, 1 < imageContainer.m_numMips
				, imageContainer.m_numLayers
				, imageContainer.m_format
				);
			ti.numMips = bx::min<uint8_t>(imageContainer.m_numMips-startLod, ti.numMips);

			m_flags  = _flags;
			m_width  = ti.width;
			m_height = ti.height;
			m_depth  = ti.depth;
			m_requestedFormat  = uint8_t(imageContainer.m_format);
			m_textureFormat    = uint8_t(getViableTextureFormat(imageContainer) );
			const bool convert = m_textureFormat != m_requestedFormat;
			const uint8_t bpp  = bimg::getBitsPerPixel(bimg::TextureFormat::Enum(m_textureFormat) );

			wgpu::TextureDescriptor desc = defaultDescriptor<wgpu::TextureDescriptor>();

			if (1 < ti.numLayers)
			{
				if (imageContainer.m_cubeMap)
				{
					desc.dimension = wgpu::TextureDimension::e2D; // MTLTextureType(6); // MTLTextureTypeCubeArray
					m_type = TextureCube;
				}
				else
				{
					desc.dimension = wgpu::TextureDimension::e2D; // MTLTextureType2DArray;
					m_type = Texture2D;
				}
			}
			else if (imageContainer.m_cubeMap)
			{
				desc.dimension = wgpu::TextureDimension::e2D; //desc.dimension = MTLTextureTypeCube;
				m_type = TextureCube;
			}
			else if (1 < imageContainer.m_depth)
			{
				desc.dimension = wgpu::TextureDimension::e3D;
				m_type = Texture3D;
			}
			else
			{
				desc.dimension = wgpu::TextureDimension::e2D;
				m_type = Texture2D;
			}

			m_numMips = ti.numMips;
			const uint16_t numSides = ti.numLayers * (imageContainer.m_cubeMap ? 6 : 1);
			const bool compressed   = bimg::isCompressed(bimg::TextureFormat::Enum(m_textureFormat) );
			const bool writeOnly    = 0 != (_flags&BGFX_TEXTURE_RT_WRITE_ONLY);
			const bool computeWrite = 0 != (_flags&BGFX_TEXTURE_COMPUTE_WRITE);
			const bool renderTarget = 0 != (_flags&BGFX_TEXTURE_RT_MASK);
			const bool srgb         = 0 != (_flags&BGFX_TEXTURE_SRGB);

			BX_TRACE("Texture %3d: %s (requested: %s), layers %d, %dx%d%s RT[%c], WO[%c], CW[%c], sRGB[%c]"
				, this - s_renderWgpu->m_textures
				, getName( (TextureFormat::Enum)m_textureFormat)
				, getName( (TextureFormat::Enum)m_requestedFormat)
				, ti.numLayers
				, ti.width
				, ti.height
				, imageContainer.m_cubeMap ? "x6" : ""
				, renderTarget ? 'x' : ' '
				, writeOnly    ? 'x' : ' '
				, computeWrite ? 'x' : ' '
				, srgb         ? 'x' : ' '
				);

			const uint32_t msaaQuality = bx::uint32_satsub( (_flags&BGFX_TEXTURE_RT_MSAA_MASK)>>BGFX_TEXTURE_RT_MSAA_SHIFT, 1);
			const int32_t  sampleCount = s_msaa[msaaQuality];

			wgpu::TextureFormat format = wgpu::TextureFormat(0);
			//if (srgb)
			//{
			//	format = s_textureFormat[m_textureFormat].m_fmtSrgb;
			//	BX_WARN(format != wgpu::TextureFormat::Invalid
			//		, "sRGB not supported for texture format %d"
			//		, m_textureFormat
			//		);
			//}

			if (format == wgpu::TextureFormat(0))
			{
				// not swizzled and not sRGB, or sRGB unsupported
				format = s_textureFormat[m_textureFormat];
			}

			desc.format = format;
			desc.size.width  = ti.width;
			desc.size.height = ti.height;
			desc.size.depth  = bx::uint32_max(1,imageContainer.m_depth);
			desc.mipLevelCount = ti.numMips;
			desc.sampleCount      = 1;
			desc.arrayLayerCount  = ti.numLayers;

			desc.usage = wgpu::TextureUsage::Sampled; // MTLTextureUsageShaderRead;
			desc.usage |= wgpu::TextureUsage::CopyDst;

			if (computeWrite)
			{
				desc.usage |= wgpu::TextureUsage::Storage; // MTLTextureUsageShaderWrite;
			}

			if (renderTarget)
			{
				desc.usage |= wgpu::TextureUsage::OutputAttachment; //MTLTextureUsageRenderTarget;
			}

			m_ptr = s_renderWgpu->m_device.CreateTexture(&desc);

			if (sampleCount > 1)
			{
				desc.sampleCount = sampleCount;

				m_ptrMsaa = s_renderWgpu->m_device.CreateTexture(&desc);
			}

			uint8_t* temp = NULL;
			if (convert)
			{
				temp = (uint8_t*)BX_ALLOC(g_allocator, ti.width*ti.height*4);
			}

			for (uint8_t side = 0; side < numSides; ++side)
			{
				uint32_t width  = ti.width;
				uint32_t height = ti.height;
				uint32_t depth  = ti.depth;

				for (uint8_t lod = 0, num = ti.numMips; lod < num; ++lod)
				{
					width  = bx::max(1u, width);
					height = bx::max(1u, height);
					depth  = bx::max(1u, depth);

					bimg::ImageMip mip;
					if (bimg::imageGetRawData(imageContainer, side, lod+startLod, _mem->data, _mem->size, mip) )
					{
						const uint8_t* data = mip.m_data;

						if (convert)
						{
							bimg::imageDecodeToBgra8(
								  g_allocator
								, temp
								, mip.m_data
								, mip.m_width
								, mip.m_height
								, mip.m_width*4
								, mip.m_format
								);
							data = temp;
						}

						//MTLRegion region = { { 0, 0, 0 }, { width, height, depth } };

						uint32_t pitch = 0;
						uint32_t slice = 0;

						if (compressed && !convert)
						{
							if (format >= wgpu::TextureFormat(160) /*PVRTC_RGB_2BPP*/
							&&  format <= wgpu::TextureFormat(167) /*PVRTC_RGBA_4BPP_sRGB*/)
							{
								pitch = 0;
								slice = 0;
							}
							else
							{
								pitch = (mip.m_width / blockInfo.blockWidth)*mip.m_blockSize;
								slice = (mip.m_height / blockInfo.blockHeight)*pitch;

								//bytesPerImage = desc.dimension == MTLTextureType3D
								//	? (mip.m_height/blockInfo.blockHeight)*bytesPerRow
								//	: 0
								//	;
							}
						}
						else
						{
							pitch = width * bpp / 8;
							slice = pitch * height;
							//bytesPerImage = desc.dimension == MTLTextureType3D
							//	? bytesPerRow * height
							//	: 0
							//	;
						}

						//m_ptr.
						//m_ptr.replaceRegion(region, lod, side, data, bytesPerRow, bytesPerImage);

						wgpu::BufferDescriptor bufferCopyDesc;
						bufferCopyDesc.size = slice * depth;
						bufferCopyDesc.usage = wgpu::BufferUsage::CopyDst | wgpu::BufferUsage::CopySrc;

						wgpu::Buffer staging = s_renderWgpu->m_device.CreateBuffer(&bufferCopyDesc);
						staging.SetSubData(0, slice * depth, data);

						wgpu::BufferCopyView bufferCopyView;
						bufferCopyView.buffer = staging;
						bufferCopyView.offset = 0;
						bufferCopyView.rowPitch = 0;
						bufferCopyView.imageHeight = 0;

						wgpu::TextureCopyView textureCopyView;
						textureCopyView.texture = m_ptr;
						textureCopyView.mipLevel = 0;
						textureCopyView.arrayLayer = 0;
						textureCopyView.origin = { 0, 0, 0 };

						wgpu::Extent3D copySize = { width, height, depth };

						wgpu::CommandEncoder encoder = s_renderWgpu->m_device.CreateCommandEncoder();
						encoder.CopyBufferToTexture(&bufferCopyView, &textureCopyView, &copySize);

						wgpu::CommandBuffer copy = encoder.Finish();
						wgpu::Queue queue = s_renderWgpu->m_queue;
						queue.Submit(1, &copy);
					}

					width  >>= 1;
					height >>= 1;
					depth  >>= 1;
				}
			}

			if (NULL != temp)
			{
				BX_FREE(g_allocator, temp);
			}
		}
	}

	void TextureWgpu::update(uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem)
	{
		BX_UNUSED(_side); BX_UNUSED(_mip); BX_UNUSED(_depth); BX_UNUSED(_z);

		const uint32_t bpp       = bimg::getBitsPerPixel(bimg::TextureFormat::Enum(m_textureFormat) );
		const uint32_t rectpitch = _rect.m_width*bpp/8;
		const uint32_t srcpitch  = UINT16_MAX == _pitch ? rectpitch : _pitch;
		// TODO
		//const uint32_t slice     = ( (m_type == Texture3D) ? 0 : _side + _z * (m_type == TextureCube ? 6 : 1) );
		//const uint16_t zz        = (m_type == Texture3D) ? _z : 0 ;

		const bool convert = m_textureFormat != m_requestedFormat;

		uint8_t* data = _mem->data;
		uint8_t* temp = NULL;

		if (convert)
		{
			temp = (uint8_t*)BX_ALLOC(g_allocator, rectpitch*_rect.m_height);
			bimg::imageDecodeToBgra8(
				  g_allocator
				, temp
				, data
				, _rect.m_width
				, _rect.m_height
				, srcpitch
				, bimg::TextureFormat::Enum(m_requestedFormat)
				);
			data = temp;
		}

		if (s_renderWgpu->m_renderEncoder)
		{
			s_renderWgpu->m_cmd.finish(true);

			//MTLRegion region =
			//{
			//	{ _rect.m_x,     _rect.m_y,      zz     },
			//	{ _rect.m_width, _rect.m_height, _depth },
			//};
			//
			//m_ptr.replaceRegion(region, _mip, slice, data, srcpitch, srcpitch * _rect.m_height);
		}
		else
		{
			wgpu::CommandEncoder& bce = s_renderWgpu->getBlitCommandEncoder();
			BX_UNUSED(bce);

			const uint32_t dstpitch = bx::strideAlign(rectpitch, 64);

			wgpu::BufferDescriptor desc;
			desc.size = dstpitch * _rect.m_height;

			wgpu::Buffer staging = s_renderWgpu->m_device.CreateBuffer(&desc);

			const uint8_t* src = (uint8_t*)data;
			uint64_t offset = 0;

			for (uint32_t yy = 0; yy < _rect.m_height; ++yy, src += srcpitch, offset += dstpitch)
			{
				staging.SetSubData(offset, rectpitch, src);
			}

			//bce.copyFromBuffer(
			//	  tempBuffer
			//	, 0
			//	, dstpitch
			//	, dstpitch * _rect.m_height
			//	, MTLSizeMake(_rect.m_width, _rect.m_height, _depth)
			//	, m_ptr
			//	, slice
			//	, _mip
			//	, MTLOriginMake(_rect.m_x, _rect.m_y, zz)
			//	);
			//release(staging);

			staging.Destroy();
		}

		if (NULL != temp)
		{
			BX_FREE(g_allocator, temp);
		}
	}

	void BindStateWgpu::clear()
	{
		m_uniformsGroup = nullptr;
		m_texturesGroup = nullptr;
		m_samplersGroup = nullptr;
	}

	void ScratchBufferWgpu::create(uint32_t _size) //, uint32_t _maxBindGroups)
	{
		m_offset = 0;
		m_size = _size;
		//m_maxBindStates = 1024; // _maxBindStates;
		m_currentBindState = 0;

		wgpu::BufferDescriptor desc;
		desc.size = _size; // UNIFORM_BUFFER_SIZE
		// TODO (webgpu) use map and wgpu::BufferUsage::MapWrite ?
		desc.usage = wgpu::BufferUsage::Uniform | wgpu::BufferUsage::CopyDst; //wgpu::BufferUsage::TransferDst;
		m_buffer = s_renderWgpu->m_device.CreateBuffer(&desc);

		//m_bindGroups = (wgpu::BindGroup*)BX_ALLOC(g_allocator, m_maxBindGroups * sizeof(wgpu::BindGroup));
		//bx::memSet(m_bindGroups, 0, sizeof(wgpu::BindGroup) * m_maxBindGroups);
	}

	void ScratchBufferWgpu::destroy()
	{
		reset();

		//BX_FREE(g_allocator, m_bindGroups);

		m_buffer.Release();
	}

	void ScratchBufferWgpu::reset()
	{
		for (size_t i = 0; i < m_currentBindState; ++i)
		{
			m_bindStates[i] = {};
		}

		//bx::memSet(m_bindStates, 0, sizeof(wgpu::BindGroup) * m_maxBindStates);

		m_offset = 0;
		m_currentBindState = 0;
	}

	wgpu::TextureView TextureWgpu::getTextureMipLevel(int _mip)
	{
		if (_mip >= 0
		&&  _mip <  m_numMips
		&&  m_ptr)
		{
			if (!m_ptrMips[_mip])
			{
				wgpu::TextureViewDescriptor desc;
				desc.baseMipLevel = _mip;
				desc.mipLevelCount = 1;

				desc.format = s_textureFormat[m_textureFormat];

				if (TextureCube == m_type)
				{
					//desc.dimension = MTLTextureType2DArray;
					desc.baseArrayLayer = 0;
					desc.arrayLayerCount = m_numLayers * 6;
				}
				else
				{
					desc.baseArrayLayer = 0;
					desc.arrayLayerCount = m_numLayers;
				}

				m_ptrMips[_mip] = m_ptr.CreateView(&desc);
			}

			return m_ptrMips[_mip];
		}

		return wgpu::TextureView();
	}

	SwapChainWgpu::~SwapChainWgpu()
	{
		//MTL_RELEASE(m_metalLayer);
		//MTL_RELEASE(m_drawable);
		//MTL_RELEASE(m_drawableTexture);
		//
		//MTL_RELEASE(m_backBufferDepth);
		//MTL_RELEASE(m_backBufferStencil);

		//if (NULL != m_backBufferColorMsaa)
		//{
		//	MTL_RELEASE(m_backBufferColorMsaa);
		//}
	}

	void SwapChainWgpu::init(wgpu::Device _device, void* _nwh, uint32_t _width, uint32_t _height)
	{
		BX_UNUSED(_nwh);

#if !BX_PLATFORM_EMSCRIPTEN
		wgpu::SwapChainDescriptor desc;
		m_impl = CreateSwapChain(_device, _nwh);
		desc.implementation = reinterpret_cast<uint64_t>(&m_impl);
		m_swapChain = _device.CreateSwapChain(&desc);
#else
		wgpu::SurfaceDescriptorFromHTMLCanvas canvasDesc{};
        canvasDesc.target = "#canvas";

        wgpu::SurfaceDescriptor surfDesc{};
        surfDesc.nextInChain = &canvasDesc;
        wgpu::Surface surface = wgpu::Instance().CreateSurface(&surfDesc);

        wgpu::SwapChainDescriptor scDesc{};
		scDesc.presentMode = wgpu::PresentMode::VSync;
        scDesc.format = wgpu::TextureFormat::BGRA8Unorm;
        scDesc.width = _width;
        scDesc.height = _height;
        m_swapChain = _device.CreateSwapChain(surface, &scDesc);
#endif

		//m_swapChain.Configure(wgpu::TextureFormat::RGBA8Unorm, wgpu::TextureUsage::OutputAttachment, 640, 480);

		//m_swapChain.Configure(wgpu::TextureFormat::RGBA8Unorm, wgpu::TextureUsage::OutputAttachment, 640, 480);

		m_colorFormat = wgpu::TextureFormat::RGBA8Unorm;
		m_depthFormat = wgpu::TextureFormat::Depth24PlusStencil8;

		//m_metalLayer.pixelFormat = wgpu::TextureFormat::BGRA8Unorm;
		//m_metalLayer.magnificationFilter = kCAFilterNearest;
	}

	void SwapChainWgpu::resize(FrameBufferWgpu &_frameBuffer, uint32_t _width, uint32_t _height, uint32_t _flags)
	{
		const int32_t sampleCount = s_msaa[(_flags&BGFX_RESET_MSAA_MASK)>>BGFX_RESET_MSAA_SHIFT];

#if BX_PLATFORM_OSX > 101300
		m_metalLayer.displaySyncEnabled = 0 != (_flags&BGFX_RESET_VSYNC);
#endif // BX_PLATFORM_OSX > 101300

		wgpu::TextureFormat format = (_flags & BGFX_RESET_SRGB_BACKBUFFER)
			? wgpu::TextureFormat::RGBA8Unorm //wgpu::TextureFormat::BGRA8Unorm_sRGB
			: wgpu::TextureFormat::RGBA8Unorm
			;

#if !BX_PLATFORM_EMSCRIPTEN
		m_swapChain.Configure(format, wgpu::TextureUsage::OutputAttachment, _width, _height);
#endif

		m_colorFormat = format;
		m_depthFormat = wgpu::TextureFormat::Depth24PlusStencil8;

		bx::HashMurmur2A murmur;
		murmur.begin();
		murmur.add(1);
		murmur.add((uint32_t)m_colorFormat);
		murmur.add((uint32_t)m_depthFormat);
		murmur.add((uint32_t)sampleCount);
		_frameBuffer.m_pixelFormatHash = murmur.end();

		wgpu::TextureDescriptor desc;

		desc.dimension = wgpu::TextureDimension::e2D;

		desc.size.width  = _width;
		desc.size.height = _height;
		desc.size.depth  = 1;
		desc.mipLevelCount = 1;
		desc.sampleCount = sampleCount;
		desc.arrayLayerCount = 1;
		desc.usage = wgpu::TextureUsage::OutputAttachment;

		//desc.cpuCacheMode = MTLCPUCacheModeDefaultCache;
		//desc.storageMode  = MTLStorageModePrivate;
		//desc.usage        = MTLTextureUsageRenderTarget;

		if (m_backBufferDepth)
		{
			m_backBufferDepth.Destroy();
		}

		desc.format = wgpu::TextureFormat::Depth24PlusStencil8;

		m_backBufferDepth = s_renderWgpu->m_device.CreateTexture(&desc);

		if (sampleCount > 1)
		{
			if (m_backBufferColorMsaa)
			{
				m_backBufferColorMsaa.Destroy();
			}

			desc.format = m_colorFormat;
			desc.sampleCount = sampleCount;

			m_backBufferColorMsaa = s_renderWgpu->m_device.CreateTexture(&desc);
		}
	}

	void SwapChainWgpu::flip()
	{
		m_drawable = m_swapChain.GetCurrentTextureView();
	}

	wgpu::TextureView SwapChainWgpu::current()
	{
		if (!m_drawable)
			m_drawable = m_swapChain.GetCurrentTextureView();
		return m_drawable;
	}

	void FrameBufferWgpu::create(uint8_t _num, const Attachment* _attachment)
	{
		m_swapChain = NULL;
		m_denseIdx  = UINT16_MAX;
		m_num       = 0;
		m_width     = 0;
		m_height    = 0;

		for (uint32_t ii = 0; ii < _num; ++ii)
		{
			const Attachment& at = _attachment[ii];
			TextureHandle handle = at.handle;

			if (isValid(handle) )
			{
				const TextureWgpu& texture = s_renderWgpu->m_textures[handle.idx];

				if (0 == m_width)
				{
					m_width = texture.m_width;
					m_height = texture.m_height;
				}

				if (bimg::isDepth(bimg::TextureFormat::Enum(texture.m_textureFormat) ) )
				{
					m_depthHandle = handle;
					m_depthAttachment = at;
				}
				else
				{
					m_colorHandle[m_num] = handle;
					m_colorAttachment[m_num] = at;
					m_num++;
				}
			}
		}

		bx::HashMurmur2A murmur;
		murmur.begin();
		murmur.add(m_num);

		for (uint32_t ii = 0; ii < m_num; ++ii)
		{
			const TextureWgpu& texture = s_renderWgpu->m_textures[m_colorHandle[ii].idx];
			murmur.add(uint32_t(s_textureFormat[texture.m_textureFormat]) );
		}

		if (!isValid(m_depthHandle) )
		{
			murmur.add(uint32_t(wgpu::TextureFormat(0)) );
		}
		else
		{
			const TextureWgpu& depthTexture = s_renderWgpu->m_textures[m_depthHandle.idx];
			murmur.add(uint32_t(s_textureFormat[depthTexture.m_textureFormat]) );
		}

		murmur.add(1); // SampleCount

		m_pixelFormatHash = murmur.end();
	}

	bool FrameBufferWgpu::create(uint16_t _denseIdx, void* _nwh, uint32_t _width, uint32_t _height, TextureFormat::Enum _format, TextureFormat::Enum _depthFormat)
	{
		BX_UNUSED(_format, _depthFormat);
		m_swapChain = BX_NEW(g_allocator, SwapChainWgpu);
		m_num       = 0;
		m_width     = _width;
		m_height    = _height;
		m_nwh       = _nwh;
		m_denseIdx  = _denseIdx;

		m_swapChain->init(s_renderWgpu->m_device, _nwh, _width, _height);
		m_swapChain->resize(*this, _width, _height, 0);

		return m_swapChain->m_swapChain != nullptr;
	}

	void FrameBufferWgpu::postReset()
	{
	}

	uint16_t FrameBufferWgpu::destroy()
	{
		if (NULL != m_swapChain)
		{
			BX_DELETE(g_allocator, m_swapChain);
			m_swapChain = NULL;
		}

		m_num = 0;
		m_nwh = NULL;
		m_depthHandle.idx = kInvalidHandle;

		uint16_t denseIdx = m_denseIdx;
		m_denseIdx = UINT16_MAX;

		return denseIdx;
	}

	void CommandQueueWgpu::init(wgpu::Queue _queue)
	{
		m_queue = _queue;
#if BGFX_CONFIG_MULTITHREADED
		m_framesSemaphore.post(WEBGPU_MAX_FRAMES_IN_FLIGHT);
#endif
	}

	void CommandQueueWgpu::shutdown()
	{
		finish(true);
		//MTL_RELEASE(m_commandQueue);
	}

	void CommandQueueWgpu::begin()
	{
		m_encoder = s_renderWgpu->m_device.CreateCommandEncoder();
		//retain(m_encoder);
	}

	inline void commandBufferFinishedCallback(void* _data)
	{
#if BGFX_CONFIG_MULTITHREADED
		CommandQueueWgpu* queue = (CommandQueueWgpu*)_data;
		if (queue)
		{
			queue->m_framesSemaphore.post();
		}
#else
		BX_UNUSED(_data);
#endif
	}

	void CommandQueueWgpu::kick(bool _endFrame, bool _waitForFinish)
	{
		_waitForFinish = true;
		if (m_encoder)
		{
			if (_endFrame)
			{
				m_releaseWriteIndex = (m_releaseWriteIndex + 1) % WEBGPU_MAX_FRAMES_IN_FLIGHT;
				//m_encoder.addCompletedHandler(commandBufferFinishedCallback, this);
			}

			wgpu::CommandBuffer commands = m_encoder.Finish();

			if (_waitForFinish)
			{
				m_queue.Submit(1, &commands);
#if BGFX_CONFIG_MULTITHREADED
				m_framesSemaphore.post();
#endif
			}

			m_encoder = nullptr;
		}
	}

	void CommandQueueWgpu::finish(bool _finishAll)
	{
		if (_finishAll)
		{
			uint32_t count = m_encoder
				? 2
				: 3
				;

			for (uint32_t ii = 0; ii < count; ++ii)
			{
				consume();
			}

#if BGFX_CONFIG_MULTITHREADED
			m_framesSemaphore.post(count);
#endif
		}
		else
		{
			consume();
		}
	}

	void CommandQueueWgpu::release(wgpu::Buffer _buffer)
	{
		m_release[m_releaseWriteIndex].push_back(_buffer);
	}

	void CommandQueueWgpu::consume()
	{
#if BGFX_CONFIG_MULTITHREADED
		m_framesSemaphore.wait();
#endif

		m_releaseReadIndex = (m_releaseReadIndex + 1) % WEBGPU_MAX_FRAMES_IN_FLIGHT;

		for (wgpu::Buffer& buffer : m_release[m_releaseReadIndex])
		{
			buffer.Destroy();
		}
		
		m_release[m_releaseReadIndex].clear();
	}

	void TimerQueryWgpu::init()
	{
		m_frequency = bx::getHPFrequency();
	}

	void TimerQueryWgpu::shutdown()
	{
	}

	uint32_t TimerQueryWgpu::begin(uint32_t _resultIdx)
	{
		BX_UNUSED(_resultIdx);
		return 0;
	}

	void TimerQueryWgpu::end(uint32_t _idx)
	{
		BX_UNUSED(_idx);
	}

#if 0
	static void setTimestamp(void* _data)
	{
		*( (int64_t*)_data) = bx::getHPCounter();
	}
#endif

	void TimerQueryWgpu::addHandlers(wgpu::CommandBuffer& _commandBuffer)
	{
		BX_UNUSED(_commandBuffer);

		while (0 == m_control.reserve(1) )
		{
			m_control.consume(1);
		}

		//uint32_t offset = m_control.m_current;
		//_commandBuffer.addScheduledHandler(setTimestamp, &m_result[offset].m_begin);
		//_commandBuffer.addCompletedHandler(setTimestamp, &m_result[offset].m_end);
		m_control.commit(1);
	}

	bool TimerQueryWgpu::get()
	{
		if (0 != m_control.available() )
		{
			uint32_t offset = m_control.m_read;
			m_begin = m_result[offset].m_begin;
			m_end   = m_result[offset].m_end;
			m_elapsed = m_end - m_begin;

			m_control.consume(1);

			return true;
		}

		return false;
	}

	void OcclusionQueryWgpu::postReset()
	{
		m_buffer.Destroy();
	}

	void OcclusionQueryWgpu::preReset()
	{
		wgpu::BufferDescriptor desc;
		desc.size = (BX_COUNTOF(m_query) * 8);
		desc.usage = wgpu::BufferUsage::Storage;
		m_buffer = s_renderWgpu->m_device.CreateBuffer(&desc);
	}

	void OcclusionQueryWgpu::begin(wgpu::RenderPassEncoder& _rce, Frame* _render, OcclusionQueryHandle _handle)
	{
		BX_UNUSED(_rce);
		while (0 == m_control.reserve(1) )
		{
			resolve(_render, true);
		}

		Query& query = m_query[m_control.m_current];
		query.m_handle  = _handle;
		//uint32_t offset = _handle.idx * 8;
		//_rce.setVisibilityResultMode(MTLVisibilityResultModeBoolean, offset);
	}

	void OcclusionQueryWgpu::end(wgpu::RenderPassEncoder& _rce)
	{
		BX_UNUSED(_rce);
		//Query& query = m_query[m_control.m_current];
		//uint32_t offset = query.m_handle.idx * 8;
		//_rce.setVisibilityResultMode(MTLVisibilityResultModeDisabled, offset);
		m_control.commit(1);
	}

	void OcclusionQueryWgpu::resolve(Frame* _render, bool _wait)
	{
		BX_UNUSED(_wait);

		while (0 != m_control.available() )
		{
			Query& query = m_query[m_control.m_read];

			if (isValid(query.m_handle) )
			{
				uint64_t result = 0; // ((uint64_t*)m_buffer.contents())[query.m_handle.idx];
				_render->m_occlusion[query.m_handle.idx] = int32_t(result);
			}

			m_control.consume(1);
		}
	}

	void OcclusionQueryWgpu::invalidate(OcclusionQueryHandle _handle)
	{
		const uint32_t size = m_control.m_size;

		for (uint32_t ii = 0, num = m_control.available(); ii < num; ++ii)
		{
			Query& query = m_query[(m_control.m_read + ii) % size];
			if (query.m_handle.idx == _handle.idx)
			{
				query.m_handle.idx = bgfx::kInvalidHandle;
			}
		}
	}

	void RendererContextWgpu::submitBlit(BlitState& _bs, uint16_t _view)
	{
		if (!_bs.hasItem(_view) )
		{
			return;
		}

		endEncoding();

		wgpu::CommandEncoder& bce = getBlitCommandEncoder();

		while (_bs.hasItem(_view) )
		{
			const BlitItem& blit = _bs.advance();

			const TextureWgpu& src = m_textures[blit.m_src.idx];
			const TextureWgpu& dst = m_textures[blit.m_dst.idx];

			uint32_t srcWidth  = bx::uint32_min(src.m_width,  blit.m_srcX + blit.m_width)  - blit.m_srcX;
			uint32_t srcHeight = bx::uint32_min(src.m_height, blit.m_srcY + blit.m_height) - blit.m_srcY;
			uint32_t srcDepth  = bx::uint32_min(src.m_depth,  blit.m_srcZ + blit.m_depth)  - blit.m_srcZ;
			uint32_t dstWidth  = bx::uint32_min(dst.m_width,  blit.m_dstX + blit.m_width)  - blit.m_dstX;
			uint32_t dstHeight = bx::uint32_min(dst.m_height, blit.m_dstY + blit.m_height) - blit.m_dstY;
			uint32_t dstDepth  = bx::uint32_min(dst.m_depth,  blit.m_dstZ + blit.m_depth)  - blit.m_dstZ;
			uint32_t width     = bx::uint32_min(srcWidth,  dstWidth);
			uint32_t height    = bx::uint32_min(srcHeight, dstHeight);
			uint32_t depth     = bx::uint32_min(srcDepth,  dstDepth);
			bool     readBack  = !!(dst.m_flags & BGFX_TEXTURE_READ_BACK);

			BX_UNUSED(depth);
#if 0
			if (MTLTextureType3D == src.m_ptr.textureType() )
			{
				bce.copyFromTexture(
					  src.m_ptr
					, 0
					, 0
					, MTLOriginMake(blit.m_srcX, blit.m_srcY, blit.m_srcZ)
					, MTLSizeMake(width, height, bx::uint32_imax(depth, 1) )
					, dst.m_ptr
					, 0
					, 0
					, MTLOriginMake(blit.m_dstX, blit.m_dstY, blit.m_dstZ)
					);

				if (readBack)
				{
					m_blitCommandEncoder.synchronizeResource(dst.m_ptr);
				}
			}
			else
#endif
			{

				wgpu::TextureCopyView srcView;
				srcView.texture = src.m_ptr;
				srcView.origin = { blit.m_srcX, blit.m_srcY, 0 };
				srcView.mipLevel = blit.m_srcMip;
				srcView.arrayLayer = blit.m_srcZ;

				wgpu::TextureCopyView dstView;
				dstView.texture = dst.m_ptr;
				dstView.origin = { blit.m_dstX, blit.m_dstY, 0 };
				dstView.mipLevel = blit.m_dstMip;
				dstView.arrayLayer = blit.m_dstZ;

				wgpu::Extent3D copyExtent = { width, height, 1 };

				bce.CopyTextureToTexture(&srcView, &dstView, &copyExtent);

				if (readBack)
				{
					//bce..synchronizeTexture(dst.m_ptr, 0, blit.m_dstMip);
				}
			}
		}

		//if (bce)
		//{
		//	bce.endEncoding();
		//	bce = 0;
		//}
	}

	void RendererContextWgpu::submit(Frame* _render, ClearQuad& _clearQuad, TextVideoMemBlitter& _textVideoMemBlitter)
	{
		if(_render->m_capture)
		{
			renderDocTriggerCapture();
		}

		m_cmd.finish(false);

		if (!m_cmd.m_encoder)
		{
			m_cmd.begin();
		}

		BGFX_WEBGPU_PROFILER_BEGIN_LITERAL("rendererSubmit", kColorFrame);

		int64_t timeBegin = bx::getHPCounter();
		int64_t captureElapsed = 0;

		//m_gpuTimer.addHandlers(m_encoder);

		//if (m_blitCommandEncoder)
		//{
		//	m_blitCommandEncoder.endEncoding();
		//	m_blitCommandEncoder = 0;
		//}

		updateResolution(_render->m_resolution);

		m_bufferIndex = (m_bufferIndex + 1) % WEBGPU_MAX_FRAMES_IN_FLIGHT;
		ScratchBufferWgpu& scratchBuffer = m_scratchBuffers[m_bufferIndex]; // TODO index 
		scratchBuffer.reset();

		if (0 < _render->m_iboffset)
		{
			BGFX_PROFILER_SCOPE("bgfx/Update transient index buffer", kColorResource);
			TransientIndexBuffer* ib = _render->m_transientIb;
			m_indexBuffers[ib->handle.idx].update(0, bx::strideAlign(_render->m_iboffset,4), ib->data, true);
		}

		if (0 < _render->m_vboffset)
		{
			BGFX_PROFILER_SCOPE("bgfx/Update transient vertex buffer", kColorResource);
			TransientVertexBuffer* vb = _render->m_transientVb;
			m_vertexBuffers[vb->handle.idx].update(0, bx::strideAlign(_render->m_vboffset,4), vb->data, true);
		}

		_render->sort();

		RenderDraw currentState;
		currentState.clear();
		currentState.m_stateFlags = BGFX_STATE_NONE;
		currentState.m_stencil    = packStencil(BGFX_STENCIL_NONE, BGFX_STENCIL_NONE);

		RenderBind currentBind;
		currentBind.clear();

		static ViewState viewState;
		viewState.reset(_render);
		uint32_t blendFactor = 0;

		//bool wireframe = !!(_render->m_debug&BGFX_DEBUG_WIREFRAME);

		ProgramHandle currentProgram = BGFX_INVALID_HANDLE;
		uint32_t currentBindHash = 0;
		uint32_t currentBindLayoutHash = 0;
		BindStateWgpu* previousBindState = nullptr;
		SortKey key;
		uint16_t view = UINT16_MAX;
		FrameBufferHandle fbh = { BGFX_CONFIG_MAX_FRAME_BUFFERS };

		BlitState bs(_render);

		const uint64_t primType = 0;
		uint8_t primIndex = uint8_t(primType >> BGFX_STATE_PT_SHIFT);
		PrimInfo prim = s_primInfo[primIndex];
		const uint32_t maxComputeBindings = g_caps.limits.maxComputeBindings;

		wgpu::RenderPassEncoder rce;
		PipelineStateWgpu* currentPso = NULL;

		bool wasCompute     = false;
		bool viewHasScissor = false;
		Rect viewScissorRect;
		viewScissorRect.clear();

		uint32_t statsNumPrimsSubmitted[BX_COUNTOF(s_primInfo)] = {};
		uint32_t statsNumPrimsRendered[BX_COUNTOF(s_primInfo)]  = {};
		uint32_t statsNumInstances[BX_COUNTOF(s_primInfo)]      = {};
		uint32_t statsNumDrawIndirect[BX_COUNTOF(s_primInfo)]   = {};
		uint32_t statsNumIndices = 0;
		uint32_t statsKeyType[2] = {};

		Profiler<TimerQueryWgpu> profiler(
			  _render
			, m_gpuTimer
			, s_viewName
			);

		m_occlusionQuery.resolve(_render);

		if (0 == (_render->m_debug&BGFX_DEBUG_IFH) )
		{
			viewState.m_rect = _render->m_view[0].m_rect;
			int32_t numItems = _render->m_numRenderItems;

			for (int32_t item = 0; item < numItems;)
			{
				const uint64_t encodedKey = _render->m_sortKeys[item];
				const bool isCompute = key.decode(encodedKey, _render->m_viewRemap);
				statsKeyType[isCompute]++;

				const bool viewChanged = 0
					|| key.m_view != view
					|| item == numItems
					;

				const uint32_t itemIdx       = _render->m_sortValues[item];
				const RenderItem& renderItem = _render->m_renderItem[itemIdx];
				const RenderBind& renderBind = _render->m_renderItemBind[itemIdx];
				++item;

				if (viewChanged
				|| (!isCompute && wasCompute) )
				{
					view = key.m_view;
					currentProgram = BGFX_INVALID_HANDLE;

					if (item > 1)
					{
						profiler.end();
					}

					BGFX_WEBGPU_PROFILER_END();
					setViewType(view, "  ");
					BGFX_WEBGPU_PROFILER_BEGIN(view, kColorView);

					profiler.begin(view);

					viewState.m_rect = _render->m_view[view].m_rect;

					submitBlit(bs, view);

					if (!isCompute)
					{
						const Rect& scissorRect = _render->m_view[view].m_scissor;
						viewHasScissor = !scissorRect.isZero();
						viewScissorRect = viewHasScissor ? scissorRect : viewState.m_rect;
						Clear& clr = _render->m_view[view].m_clear;

						Rect viewRect = viewState.m_rect;
						bool clearWithRenderPass = false;

						if (!m_renderEncoder
						||  fbh.idx != _render->m_view[view].m_fbh.idx)
						{
							endEncoding();

							fbh = _render->m_view[view].m_fbh;

							uint32_t width = m_resolution.width;
							uint32_t height = m_resolution.height;

							if(isValid(fbh))
							{
								FrameBufferWgpu& frameBuffer = m_frameBuffers[fbh.idx];
								width = frameBuffer.m_width;
								height = frameBuffer.m_height;
							}

							clearWithRenderPass = true
								&& 0 == viewRect.m_x
								&& 0 == viewRect.m_y
								&& width == viewRect.m_width
								&& height == viewRect.m_height
								;

							rce = renderPass(_render, fbh, clearWithRenderPass, clr);
						}
						else if (BX_ENABLED(BGFX_CONFIG_DEBUG_ANNOTATION) )
						{
							rce.PopDebugGroup();
						}

						if (BX_ENABLED(BGFX_CONFIG_DEBUG_ANNOTATION) )
						{
							rce.PushDebugGroup(s_viewName[view]);
						}

						//rce.setTriangleFillMode(wireframe ? MTLTriangleFillModeLines : MTLTriangleFillModeFill);

						//MTLViewport vp;
						//vp.originX = viewState.m_rect.m_x;
						//vp.originY = viewState.m_rect.m_y;
						//vp.width   = viewState.m_rect.m_width;
						//vp.height  = viewState.m_rect.m_height;
						//vp.znear   = 0.0f;
						//vp.zfar    = 1.0f;
						//rce.setViewport(vp);

						if (BGFX_CLEAR_NONE != (clr.m_flags & BGFX_CLEAR_MASK)
						&& !clearWithRenderPass)
						{
							clearQuad(_clearQuad, viewState.m_rect, clr, _render->m_colorPalette);
						}
					}
				}

				if (isCompute)
				{
#if 0
					if (!wasCompute)
					{
						wasCompute = true;

						endEncoding();
						rce = NULL;

						setViewType(view, "C");
						BGFX_WEBGPU_PROFILER_END();
						BGFX_WEBGPU_PROFILER_BEGIN(view, kColorCompute);

						m_computeEncoder = m_cmd.m_encoder.BeginComputePass();
					}
					else if (viewChanged && BX_ENABLED(BGFX_CONFIG_DEBUG_ANNOTATION) )
					{
						m_computeEncoder.PopDebugGroup();
					}

					if (viewChanged
					&&  BX_ENABLED(BGFX_CONFIG_DEBUG_ANNOTATION) )
					{
						s_viewName[view][3] = L'C';
						m_computeEncoder.PushDebugGroup(s_viewName[view]);
						s_viewName[view][3] = L' ';
					}

					const RenderCompute& compute = renderItem.compute;

					bool programChanged = false;
					bool constantsChanged = compute.m_uniformBegin < compute.m_uniformEnd;
					rendererUpdateUniforms(this, _render->m_submitUniforms[compute.m_uniformIdx], compute.m_uniformBegin, compute.m_uniformEnd);

					if (key.m_program.idx != currentProgram.idx)
					{
						currentProgram = key.m_program;

						currentPso = getComputePipelineState(currentProgram);

						if (NULL == currentPso)
						{
							currentProgram = BGFX_INVALID_HANDLE;
							continue;
						}

						m_computeEncoder.SetPipeline(currentPso->m_cps);
						programChanged =
							constantsChanged = true;
					}

					if (isValid(currentProgram)
					&&  NULL != currentPso)
					{
						const ProgramWgpu& program = m_program[currentProgram.idx];

						//const uint32_t align = uint32_t(m_deviceProperties.limits.minUniformBufferOffsetAlignment);
						const uint32_t align = kMinUniformBufferOffsetAlignment;

						const uint32_t vsize = bx::strideAlign(program.m_vsh->m_size, align);
						const uint32_t voffset = scratchBuffer.m_offset;
						scratchBuffer.m_offset += vsize;

						uniforms[0].offset = voffset;
						uniforms[0].size = vsize;

						if (constantsChanged)
						{
							UniformBuffer* vcb = program.m_vsh->m_constantBuffer[UniformSet::Submit];
							if (NULL != vcb)
							{
								commit(*vcb);
							}
						}

						viewState.setPredefined<4>(this, view, program, _render, compute, programChanged || viewChanged);
					}
					BX_UNUSED(programChanged);

					for (uint8_t stage = 0; stage < maxComputeBindings; ++stage)
					{
#if 0
						const Binding& bind = renderBind.m_bind[stage];
						if (kInvalidHandle != bind.m_idx)
						{
							switch (bind.m_type)
							{
								case Binding::Image:
								{
									TextureWgpu& texture = m_textures[bind.m_idx];
									textures[currentSampler].binding = stage;
									textures[currentSampler].textureView = texture.getTextureMipLevel(bind.m_mip);
									currentSampler++;
								}
								break;

								case Binding::Texture:
								{
									TextureWgpu& texture = m_textures[bind.m_idx];
									uint32_t flags = bind.m_samplerFlags;

									textures[currentSampler].binding = stage;
									textures[currentSampler].textureView = texture.m_ptr.CreateView();
									samplers[currentSampler].binding = stage;
									samplers[currentSampler].sampler = 0 == (BGFX_SAMPLER_INTERNAL_DEFAULT & flags)
										? getSamplerState(flags)
										: texture.m_sampler;
									currentSampler++;
								}
								break;

								case Binding::IndexBuffer:
								case Binding::VertexBuffer:
								{
									const BufferWgpu& buffer = Binding::IndexBuffer == bind.m_type
										? m_indexBuffers[bind.m_idx]
										: m_vertexBuffers[bind.m_idx]
										;

									uniforms[currentBuffer].binding = 2+stage;
									uniforms[currentBuffer].offset = 0;
									uniforms[currentBuffer].buffer = buffer.m_ptr;
									currentBuffer++;
								}
								break;
							}
						}
#endif
					}

					ProgramWgpu& program = m_program[currentProgram.idx];

					wgpu::BindGroupDescriptor bindGroupDesc;
					bindGroupDesc.layout = program.m_uniforms;
					bindGroupDesc.bindingCount = currentBuffer;
					bindGroupDesc.bindings = uniforms;

					wgpu::BindGroup bindGroup = m_device.CreateBindGroup(&bindGroupDesc);
					m_computeEncoder.SetBindGroup(0, bindGroup, 0, nullptr);

					currentSampler = 0;
					currentBuffer = 2;

					if (isValid(compute.m_indirectBuffer) )
					{
						//const VertexBufferWgpu& vb = m_vertexBuffers[compute.m_indirectBuffer.idx];
						//
						//uint32_t numDrawIndirect = UINT16_MAX == compute.m_numIndirect
						//? vb.m_size/BGFX_CONFIG_DRAW_INDIRECT_STRIDE
						//: compute.m_numIndirect
						//;
						//
						//uint32_t args = compute.m_startIndirect * BGFX_CONFIG_DRAW_INDIRECT_STRIDE;
						//for (uint32_t ii = 0; ii < numDrawIndirect; ++ii)
						//{
						//	m_computeEncoder.dispatchThreadgroupsWithIndirectBuffer(
						//		  vb.m_ptr
						//		, args
						//		, threadsPerGroup
						//		);
						//	args += BGFX_CONFIG_DRAW_INDIRECT_STRIDE;
						//}
					}
					else
					{
						m_computeEncoder.Dispatch(compute.m_numX, compute.m_numY, compute.m_numZ);
						//	, threadsPerGroup
						//	);
					}
					continue;
#endif
				}


				bool resetState = viewChanged || wasCompute;

				if (wasCompute)
				{
					wasCompute = false;
					currentProgram = BGFX_INVALID_HANDLE;

					setViewType(view, " ");
					BGFX_WEBGPU_PROFILER_END();
					BGFX_WEBGPU_PROFILER_BEGIN(view, kColorDraw);
				}

				const RenderDraw& draw = renderItem.draw;

				const bool hasOcclusionQuery = 0 != (draw.m_stateFlags & BGFX_STATE_INTERNAL_OCCLUSION_QUERY);
				{
					const bool occluded = true
						&& isValid(draw.m_occlusionQuery)
						&& !hasOcclusionQuery
						&& !isVisible(_render, draw.m_occlusionQuery, 0 != (draw.m_submitFlags&BGFX_SUBMIT_INTERNAL_OCCLUSION_VISIBLE) )
						;

					if (occluded
					||  _render->m_frameCache.isZeroArea(viewScissorRect, draw.m_scissor) )
					{
						if (resetState)
						{
							currentState.clear();
							currentState.m_scissor = !draw.m_scissor;
							currentBind.clear();
						}

						continue;
					}
				}

				// TODO (hugoam)
				//const bool depthWrite = !!(BGFX_STATE_WRITE_Z & draw.m_stateFlags);
				const uint64_t newFlags = draw.m_stateFlags;
				uint64_t changedFlags = currentState.m_stateFlags ^ draw.m_stateFlags;
				currentState.m_stateFlags = newFlags;

				const uint64_t newStencil = draw.m_stencil;
				uint64_t changedStencil = currentState.m_stencil ^ draw.m_stencil;
				currentState.m_stencil = newStencil;

				if (resetState)
				{
					currentState.clear();
					currentState.m_scissor = !draw.m_scissor;
					changedFlags = BGFX_STATE_MASK;
					changedStencil = packStencil(BGFX_STENCIL_MASK, BGFX_STENCIL_MASK);
					currentState.m_stateFlags = newFlags;
					currentState.m_stencil    = newStencil;
					// packStencil(BGFX_STENCIL_DEFAULT, BGFX_STENCIL_DEFAULT)

					currentBind.clear();

					currentProgram = BGFX_INVALID_HANDLE;
					const uint64_t pt = newFlags & BGFX_STATE_PT_MASK;
					primIndex = uint8_t(pt >> BGFX_STATE_PT_SHIFT);
				}
				
				if(prim.m_type != s_primInfo[primIndex].m_type)
				{
					prim = s_primInfo[primIndex];
				}

				uint16_t scissor = draw.m_scissor;
				if (currentState.m_scissor != scissor)
				{
					currentState.m_scissor = scissor;

					//MTLScissorRect rc;
					if (UINT16_MAX == scissor)
					{
						if (viewHasScissor)
						{
							rce.SetScissorRect(
								  viewScissorRect.m_x
								, viewScissorRect.m_y
								, viewScissorRect.m_width
								, viewScissorRect.m_height
							);
						}
						else
						{   // can't disable: set to view rect
							rce.SetScissorRect(
								  viewState.m_rect.m_x
								, viewState.m_rect.m_y
								, viewState.m_rect.m_width
								, viewState.m_rect.m_height
							);
						}
					}
					else
					{
						Rect scissorRect;
						scissorRect.setIntersect(viewScissorRect, _render->m_frameCache.m_rectCache.m_cache[scissor]);

						rce.SetScissorRect(
							  scissorRect.m_x
							, scissorRect.m_y
							, scissorRect.m_width
							, scissorRect.m_height
						);
					}

				}

				//uint32_t fstencil = unpackStencil(0, _stencil);
				//uint32_t ref      = (fstencil&BGFX_STENCIL_FUNC_REF_MASK)>>BGFX_STENCIL_FUNC_REF_SHIFT;
				//m_renderEncoder.SetStencilReference(ref);

				if ( (0 | BGFX_STATE_PT_MASK) & changedFlags)
                {
					const uint64_t pt = newFlags&BGFX_STATE_PT_MASK;
					primIndex = uint8_t(pt>>BGFX_STATE_PT_SHIFT);
					if (prim.m_type != s_primInfo[primIndex].m_type)
					{
						prim = s_primInfo[primIndex];
					}
                }

				if (blendFactor != draw.m_rgba
				&& !(newFlags & BGFX_STATE_BLEND_INDEPENDENT) )
				{
					const uint32_t rgba = draw.m_rgba;
					float rr = ( (rgba>>24)     )/255.0f;
					float gg = ( (rgba>>16)&0xff)/255.0f;
					float bb = ( (rgba>> 8)&0xff)/255.0f;
					float aa = ( (rgba    )&0xff)/255.0f;
					wgpu::Color color = { rr, gg, bb, aa };
					rce.SetBlendColor(&color);

					blendFactor = draw.m_rgba;
				}

				bool programChanged = false;
				bool constantsChanged = draw.m_uniformBegin < draw.m_uniformEnd;
				rendererUpdateUniforms(this, _render->m_submitUniforms[draw.m_uniformIdx], draw.m_uniformBegin, draw.m_uniformEnd);

				bool vertexStreamChanged = hasVertexStreamChanged(currentState, draw);

				if (key.m_program.idx != currentProgram.idx
				||  vertexStreamChanged
				|| (0
				   | BGFX_STATE_BLEND_MASK
				   | BGFX_STATE_BLEND_EQUATION_MASK
				   | BGFX_STATE_WRITE_RGB
				   | BGFX_STATE_WRITE_A
				   | BGFX_STATE_BLEND_INDEPENDENT
				   | BGFX_STATE_MSAA
				   | BGFX_STATE_BLEND_ALPHA_TO_COVERAGE
				   ) & changedFlags
				|| ( (blendFactor != draw.m_rgba) && !!(newFlags & BGFX_STATE_BLEND_INDEPENDENT) ) )
				{
					currentProgram = key.m_program;

					currentState.m_streamMask             = draw.m_streamMask;
					currentState.m_instanceDataBuffer.idx = draw.m_instanceDataBuffer.idx;
					currentState.m_instanceDataOffset     = draw.m_instanceDataOffset;
					currentState.m_instanceDataStride     = draw.m_instanceDataStride;

					const VertexLayout* decls[BGFX_CONFIG_MAX_VERTEX_STREAMS];

					uint32_t numVertices = draw.m_numVertices;
					uint8_t  numStreams  = 0;
					for (uint32_t idx = 0, streamMask = draw.m_streamMask
						; 0 != streamMask
						; streamMask >>= 1, idx += 1, ++numStreams
						)
					{
						const uint32_t ntz = bx::uint32_cnttz(streamMask);
						streamMask >>= ntz;
						idx         += ntz;

						currentState.m_stream[idx].m_layoutHandle = draw.m_stream[idx].m_layoutHandle;
						currentState.m_stream[idx].m_handle       = draw.m_stream[idx].m_handle;
						currentState.m_stream[idx].m_startVertex  = draw.m_stream[idx].m_startVertex;

						const uint16_t handle = draw.m_stream[idx].m_handle.idx;
						const VertexBufferWgpu& vb = m_vertexBuffers[handle];
						const uint16_t decl = isValid(draw.m_stream[idx].m_layoutHandle)
							? draw.m_stream[idx].m_layoutHandle.idx
							: vb.m_layoutHandle.idx;
						const VertexLayout& vertexDecl = m_vertexDecls[decl];
						const uint32_t stride = vertexDecl.m_stride;

						decls[numStreams] = &vertexDecl;

						numVertices = bx::uint32_min(UINT32_MAX == draw.m_numVertices
							? vb.m_size/stride
							: draw.m_numVertices
							, numVertices
							);
						const uint32_t offset = draw.m_stream[idx].m_startVertex * stride;

						rce.SetVertexBuffer(idx, vb.m_ptr, offset);
					}

					bool index32 = false;

					if(isValid(draw.m_indexBuffer))
					{
						const IndexBufferWgpu& ib = m_indexBuffers[draw.m_indexBuffer.idx];
						index32 = 0 != (ib.m_flags & BGFX_BUFFER_INDEX32);
					}

					currentState.m_numVertices = numVertices;

					if (!isValid(currentProgram) )
					{
						continue;
					}
					else
					{
						currentPso = NULL;

						if (0 < numStreams)
						{
							currentPso = getPipelineState(
								  newFlags
								, newStencil
								, draw.m_rgba
								, fbh
								, numStreams
								, decls
								, index32
								, currentProgram
								, uint8_t(draw.m_instanceDataStride/16)
								);
						}

						if (NULL == currentPso)
						{
							currentProgram = BGFX_INVALID_HANDLE;
							continue;
						}

						rce.SetPipeline(currentPso->m_rps);
					}

					if (isValid(draw.m_instanceDataBuffer) )
					{
						const VertexBufferWgpu& inst = m_vertexBuffers[draw.m_instanceDataBuffer.idx];
						rce.SetVertexBuffer(numStreams+1, inst.m_ptr, draw.m_instanceDataOffset);
					}

					programChanged =
						constantsChanged = true;
				}

				if (isValid(currentProgram) )
				{
					const ProgramWgpu& program = m_program[currentProgram.idx];

					if (constantsChanged)
					{
						UniformBuffer* vcb = program.m_vsh->m_constantBuffer[UniformSet::Submit];
						if(NULL != vcb)
						{
							commit(*vcb);
						}
					}

					if(constantsChanged)
					{
						UniformBuffer* fcb = program.m_fsh->m_constantBuffer[UniformSet::Submit];
						if (NULL != fcb)
						{
							commit(*fcb);
						}
					}

					viewState.setPredefined<4>(this, view, program, _render, draw, true); // programChanged || viewChanged);

					//const uint32_t align = uint32_t(m_deviceProperties.limits.minUniformBufferOffsetAlignment);
					const uint32_t align = kMinUniformBufferOffsetAlignment;

					const uint32_t vsize = bx::strideAlign(program.m_vsh->m_size, align);
					const uint32_t fsize = bx::strideAlign((NULL != program.m_fsh ? program.m_fsh->m_size : 0), align);
					const uint32_t total = vsize + fsize;

					bool hasPredefined = 0 < program.m_numPredefined;

					uint32_t numOffset = 0;
					uint32_t offsets[2] = { 0, 0 };
					if (constantsChanged
					||  hasPredefined)
					{
						//viewState.setPredefined<4>(this, view, program, _render, draw, programChanged || viewChanged);
						//commitShaderConstants(scratchBuffer, program, voffset, foffset);

						if (vsize > 0)
						{
							//const uint32_t voffset = scratchBuffer.m_offset;
							offsets[numOffset++] = scratchBuffer.m_offset;
							//bx::memCopy(&scratchBuffer.m_data[scratchBuffer.m_offset], m_vsScratch, program.m_vsh->m_size);
							scratchBuffer.m_buffer.SetSubData(scratchBuffer.m_offset, vsize, m_vsScratch);
						}
						if (fsize > 0)
						{
							//const uint32_t foffset = scratchBuffer.m_offset + vsize;
							offsets[numOffset++] = scratchBuffer.m_offset + vsize;
							//bx::memCopy(&scratchBuffer.m_data[scratchBuffer.m_offset + vsize], m_fsScratch, program.m_fsh->m_size);
							scratchBuffer.m_buffer.SetSubData(scratchBuffer.m_offset + vsize, fsize, m_fsScratch);
						}

						scratchBuffer.m_offset += total;
					}

					auto allocBindState = [this, &scratchBuffer](const ProgramWgpu& program, const RenderBind& renderBind)
					{
						BindStateWgpu& bindState = scratchBuffer.m_bindStates[scratchBuffer.m_currentBindState];
						scratchBuffer.m_currentBindState++;

						const uint32_t align = kMinUniformBufferOffsetAlignment;

						const uint32_t vsize = bx::strideAlign(program.m_vsh->m_size, align);
						const uint32_t fsize = bx::strideAlign((NULL != program.m_fsh ? program.m_fsh->m_size : 0), align);

						bindState.numOffset = program.m_numUniforms;

						// first two bindings are always uniform buffer (vertex/fragment)
						bindState.m_uniforms[0].binding = 0;
						bindState.m_uniforms[0].buffer = scratchBuffer.m_buffer;
						bindState.m_uniforms[0].offset = 0;
						bindState.m_uniforms[0].size = vsize;

						bindState.m_uniforms[1].binding = 1;
						bindState.m_uniforms[1].buffer = scratchBuffer.m_buffer;
						bindState.m_uniforms[1].offset = 0;
						bindState.m_uniforms[1].size = fsize;

						uint8_t currentSampler = 0;
						//uint8_t currentBuffer = 2;
#define LIKE_D3D12 0
#if LIKE_D3D12
						for (uint8_t stage = 0; stage < BGFX_CONFIG_MAX_TEXTURE_SAMPLERS; ++stage)
						{
							const Binding& bind = renderBind.m_bind[stage];
							if (kInvalidHandle != bind.m_idx)
							{
								switch (bind.m_type)
								{
								case Binding::Texture:
								{
#else
						for (uint32_t sampler = 0, numSamplers = program.m_numSamplers; sampler < numSamplers; ++sampler)
						{
							const SamplerInfo& samplerInfo = program.m_samplerInfo[sampler];

							UniformHandle handle = samplerInfo.m_uniform;
							int stage = *( (int*)m_uniforms[handle.idx]);

							const Binding& bind = renderBind.m_bind[stage];

							if (kInvalidHandle != bind.m_idx)
							{
#endif
								TextureWgpu& texture = m_textures[bind.m_idx];

								//textures[currentSampler].binding = stage;
								bindState.m_textures[currentSampler].binding = program.m_fsh->m_textures[stage].binding;
								bindState.m_textures[currentSampler].textureView = texture.m_ptr.CreateView();
								//samplers[currentSampler].binding = stage;
								bindState.m_samplers[currentSampler].binding = program.m_fsh->m_samplers[stage].binding;
								bindState.m_samplers[currentSampler].sampler = 0 == (BGFX_SAMPLER_INTERNAL_DEFAULT & bind.m_samplerFlags)
									? getSamplerState(bind.m_samplerFlags)
									: texture.m_sampler;
								currentSampler++;
#if LIKE_D3D12
								}
								break;
								}
							}
#else
							}
#endif
						}

						wgpu::BindGroupDescriptor uniformsDesc;
						uniformsDesc.layout = program.m_uniforms;
						uniformsDesc.bindingCount = program.m_numUniforms;
						uniformsDesc.bindings = bindState.m_uniforms;

						wgpu::BindGroupDescriptor texturesDesc;
						texturesDesc.layout = program.m_textures;
						//texturesDesc.bindingCount = numSamplers;
						texturesDesc.bindingCount = program.m_numSamplers;
						texturesDesc.bindings = bindState.m_textures;

						wgpu::BindGroupDescriptor samplersDesc;
						samplersDesc.layout = program.m_samplers;
						//samplersDesc.bindingCount = numSamplers;
						samplersDesc.bindingCount = program.m_numSamplers;
						samplersDesc.bindings = bindState.m_samplers;

						bindState.m_uniformsGroup = m_device.CreateBindGroup(&uniformsDesc);
						bindState.m_texturesGroup = m_device.CreateBindGroup(&texturesDesc);
						bindState.m_samplersGroup = m_device.CreateBindGroup(&samplersDesc);
					};

					uint32_t bindHash = bx::hash<bx::HashMurmur2A>(renderBind.m_bind, sizeof(renderBind.m_bind));
					if (currentBindHash != bindHash
					||  currentBindLayoutHash != program.m_bindGroupLayoutHash)
					{
						currentBindHash = bindHash;
						currentBindLayoutHash = program.m_bindGroupLayoutHash;
						previousBindState = &scratchBuffer.m_bindStates[scratchBuffer.m_currentBindState];

						allocBindState(program, renderBind);
					}

					BindStateWgpu& bindState = scratchBuffer.m_bindStates[scratchBuffer.m_currentBindState-1];

					BX_CHECK(bindState.numOffset == numOffset, "We're obviously doing something wrong");
					rce.SetBindGroup(0, bindState.m_uniformsGroup, numOffset, offsets);
					rce.SetBindGroup(1, bindState.m_texturesGroup);
					rce.SetBindGroup(2, bindState.m_samplersGroup);
				}

				if (0 != currentState.m_streamMask)
				{
					uint32_t numVertices = draw.m_numVertices;
					if (UINT32_MAX == numVertices)
					{
						const VertexBufferWgpu& vb = m_vertexBuffers[currentState.m_stream[0].m_handle.idx];
						uint16_t decl = !isValid(vb.m_layoutHandle) ? draw.m_stream[0].m_layoutHandle.idx : vb.m_layoutHandle.idx;
						const VertexLayout& vertexDecl = m_vertexDecls[decl];
						numVertices = vb.m_size/vertexDecl.m_stride;
					}

					uint32_t numIndices        = 0;
					uint32_t numPrimsSubmitted = 0;
					uint32_t numInstances      = 0;
					uint32_t numPrimsRendered  = 0;
					uint32_t numDrawIndirect   = 0;

					if (hasOcclusionQuery)
					{
						m_occlusionQuery.begin(rce, _render, draw.m_occlusionQuery);
					}

					if (isValid(draw.m_indirectBuffer) )
					{
#if 0
						const VertexBufferWgpu& vb = m_vertexBuffers[draw.m_indirectBuffer.idx];

						if (isValid(draw.m_indexBuffer) )
						{
							const IndexBufferWgpu& ib = m_indexBuffers[draw.m_indexBuffer.idx];
							MTLIndexType indexType = 0 == (ib.m_flags & BGFX_BUFFER_INDEX32) ? MTLIndexTypeUInt16 : MTLIndexTypeUInt32;

							numDrawIndirect = UINT16_MAX == draw.m_numIndirect
							? vb.m_size/BGFX_CONFIG_DRAW_INDIRECT_STRIDE
							: draw.m_numIndirect
							;

							for (uint32_t ii = 0; ii < numDrawIndirect; ++ii)
							{
								rce.drawIndexedPrimitives(prim.m_type,indexType, ib.m_ptr, 0, vb.m_ptr, (draw.m_startIndirect + ii )* BGFX_CONFIG_DRAW_INDIRECT_STRIDE);
							}
						}
						else
						{
							numDrawIndirect = UINT16_MAX == draw.m_numIndirect
							? vb.m_size/BGFX_CONFIG_DRAW_INDIRECT_STRIDE
							: draw.m_numIndirect
							;
							for (uint32_t ii = 0; ii < numDrawIndirect; ++ii)
							{
								rce.Draw(prim.m_type, vb.m_ptr, (draw.m_startIndirect + ii) * BGFX_CONFIG_DRAW_INDIRECT_STRIDE);
							}
						}
#endif
					}
					else
					{
						if (isValid(draw.m_indexBuffer) )
						{
							const IndexBufferWgpu& ib = m_indexBuffers[draw.m_indexBuffer.idx];

							const uint32_t indexSize = 0 == (ib.m_flags & BGFX_BUFFER_INDEX32) ? 2 : 4;

							if (UINT32_MAX == draw.m_numIndices)
							{
								numIndices        = ib.m_size/indexSize;
								numPrimsSubmitted = numIndices/prim.m_div - prim.m_sub;
								numInstances      = draw.m_numInstances;
								numPrimsRendered  = numPrimsSubmitted*draw.m_numInstances;

								rce.SetIndexBuffer(ib.m_ptr, 0);
								rce.DrawIndexed(numIndices, draw.m_numInstances, 0, 0, 0);
							}
							else if (prim.m_min <= draw.m_numIndices)
							{
								numIndices        = draw.m_numIndices;
								numPrimsSubmitted = numIndices/prim.m_div - prim.m_sub;
								numInstances      = draw.m_numInstances;
								numPrimsRendered  = numPrimsSubmitted*draw.m_numInstances;

								rce.SetIndexBuffer(ib.m_ptr, 0);
								rce.DrawIndexed(numIndices, numInstances, draw.m_startIndex, 0, 0);
							}
						}
						else
						{
							numPrimsSubmitted = numVertices/prim.m_div - prim.m_sub;
							numInstances      = draw.m_numInstances;
							numPrimsRendered  = numPrimsSubmitted*draw.m_numInstances;

							rce.Draw(numVertices, draw.m_numInstances, 0, 0);
						}
					}

					if (hasOcclusionQuery)
					{
						m_occlusionQuery.end(rce);
					}

					statsNumPrimsSubmitted[primIndex] += numPrimsSubmitted;
					statsNumPrimsRendered[primIndex]  += numPrimsRendered;
					statsNumInstances[primIndex]      += numInstances;
					statsNumDrawIndirect[primIndex]   += numDrawIndirect;
					statsNumIndices                   += numIndices;
				}
			}

			if (wasCompute)
			{
				invalidateCompute();

				setViewType(view, "C");
				BGFX_WEBGPU_PROFILER_END();
				BGFX_WEBGPU_PROFILER_BEGIN(view, kColorCompute);
			}

			submitBlit(bs, BGFX_CONFIG_MAX_VIEWS);

			if (0 < _render->m_numRenderItems)
			{
				captureElapsed = -bx::getHPCounter();
				capture();
				rce = m_renderEncoder;
				captureElapsed += bx::getHPCounter();

				profiler.end();
			}
		}

		if (BX_ENABLED(BGFX_CONFIG_DEBUG_ANNOTATION) )
		{
			if (0 < _render->m_numRenderItems)
			{
				rce.PopDebugGroup();
			}
		}

		BGFX_WEBGPU_PROFILER_END();

		int64_t timeEnd = bx::getHPCounter();
		int64_t frameTime = timeEnd - timeBegin;

		static int64_t min = frameTime;
		static int64_t max = frameTime;
		min = bx::min<int64_t>(min, frameTime);
		max = bx::max<int64_t>(max, frameTime);

		static uint32_t maxGpuLatency = 0;
		static double   maxGpuElapsed = 0.0f;
		double elapsedGpuMs = 0.0;

		do
		{
			double toGpuMs = 1000.0 / double(m_gpuTimer.m_frequency);
			elapsedGpuMs   = m_gpuTimer.m_elapsed * toGpuMs;
			maxGpuElapsed  = elapsedGpuMs > maxGpuElapsed ? elapsedGpuMs : maxGpuElapsed;
		}
		while (m_gpuTimer.get() );

		maxGpuLatency = bx::uint32_imax(maxGpuLatency, m_gpuTimer.m_control.available()-1);

		const int64_t timerFreq = bx::getHPFrequency();

		Stats& perfStats = _render->m_perfStats;
		perfStats.cpuTimeBegin  = timeBegin;
		perfStats.cpuTimeEnd    = timeEnd;
		perfStats.cpuTimerFreq  = timerFreq;
		perfStats.gpuTimeBegin  = m_gpuTimer.m_begin;
		perfStats.gpuTimeEnd    = m_gpuTimer.m_end;
		perfStats.gpuTimerFreq  = m_gpuTimer.m_frequency;
		perfStats.numDraw       = statsKeyType[0];
		perfStats.numCompute    = statsKeyType[1];
		perfStats.numBlit       = _render->m_numBlitItems;
		perfStats.maxGpuLatency = maxGpuLatency;
		bx::memCopy(perfStats.numPrims, statsNumPrimsRendered, sizeof(perfStats.numPrims) );
		perfStats.gpuMemoryMax  = -INT64_MAX;
		perfStats.gpuMemoryUsed = -INT64_MAX;

		//rce.setTriangleFillMode(MTLTriangleFillModeFill);
		if (_render->m_debug & (BGFX_DEBUG_IFH|BGFX_DEBUG_STATS) )
		{
			rce = renderPass(_render, BGFX_INVALID_HANDLE, false, Clear());

			rce.PushDebugGroup("debugstats");

			TextVideoMem& tvm = m_textVideoMem;

			static int64_t next = timeEnd;

			if (timeEnd >= next)
			{
				next = timeEnd + timerFreq;

				double freq = double(timerFreq);
				double toMs = 1000.0/freq;

				tvm.clear();
				uint16_t pos = 0;
				tvm.printf(0, pos++, BGFX_CONFIG_DEBUG ? 0x8c : 0x8f
					, " %s / " BX_COMPILER_NAME " / " BX_CPU_NAME " / " BX_ARCH_NAME " / " BX_PLATFORM_NAME " "
					, getRendererName()
					);

				pos = 10;
				tvm.printf(10, pos++, 0x8b, "        Frame: %7.3f, % 7.3f \x1f, % 7.3f \x1e [ms] / % 6.2f FPS "
					, double(frameTime)*toMs
					, double(min)*toMs
					, double(max)*toMs
					, freq/frameTime
					);

				const uint32_t msaa = (m_resolution.reset&BGFX_RESET_MSAA_MASK)>>BGFX_RESET_MSAA_SHIFT;
				tvm.printf(10, pos++, 0x8b, "  Reset flags: [%c] vsync, [%c] MSAAx%d, [%c] MaxAnisotropy "
					, !!(m_resolution.reset&BGFX_RESET_VSYNC) ? '\xfe' : ' '
					, 0 != msaa ? '\xfe' : ' '
					, 1<<msaa
					, !!(m_resolution.reset&BGFX_RESET_MAXANISOTROPY) ? '\xfe' : ' '
					);

				double elapsedCpuMs = double(frameTime)*toMs;
				tvm.printf(10, pos++, 0x8b, "    Submitted: %4d (draw %4d, compute %4d) / CPU %3.4f [ms] %c GPU %3.4f [ms] (latency %d)"
					, _render->m_numRenderItems
					, statsKeyType[0]
					, statsKeyType[1]
					, elapsedCpuMs
					, elapsedCpuMs > maxGpuElapsed ? '>' : '<'
					, maxGpuElapsed
					, maxGpuLatency
					);
				maxGpuLatency = 0;
				maxGpuElapsed = 0.0;

				for (uint32_t ii = 0; ii < Topology::Count; ++ii)
				{
					tvm.printf(10, pos++, 0x8b, "   %10s: %7d (#inst: %5d), submitted: %7d"
						, getName(Topology::Enum(ii) )
						, statsNumPrimsRendered[ii]
						, statsNumInstances[ii]
						, statsNumPrimsSubmitted[ii]
						);
				}

				tvm.printf(10, pos++, 0x8b, "      Indices: %7d ", statsNumIndices);
//				tvm.printf(10, pos++, 0x8b, " Uniform size: %7d, Max: %7d ", _render->m_uniformEnd, _render->m_uniformMax);
				tvm.printf(10, pos++, 0x8b, "     DVB size: %7d ", _render->m_vboffset);
				tvm.printf(10, pos++, 0x8b, "     DIB size: %7d ", _render->m_iboffset);

				pos++;
				double captureMs = double(captureElapsed)*toMs;
				tvm.printf(10, pos++, 0x8b, "     Capture: %3.4f [ms]", captureMs);

				uint8_t attr[2] = { 0x8c, 0x8a };
				uint8_t attrIndex = _render->m_waitSubmit < _render->m_waitRender;

				tvm.printf(10, pos++, attr[attrIndex    &1], " Submit wait: %3.4f [ms]", _render->m_waitSubmit*toMs);
				tvm.printf(10, pos++, attr[(attrIndex+1)&1], " Render wait: %3.4f [ms]", _render->m_waitRender*toMs);

				min = frameTime;
				max = frameTime;
			}

			blit(this, _textVideoMemBlitter, tvm);
			rce = m_renderEncoder;

			rce.PopDebugGroup();
		}
		else if (_render->m_debug & BGFX_DEBUG_TEXT)
		{
			rce.PushDebugGroup("debugtext");

			blit(this, _textVideoMemBlitter, _render->m_textVideoMem);
			rce = m_renderEncoder;

			rce.PopDebugGroup();
		}

		endEncoding();
		m_renderCommandEncoderFrameBufferHandle.idx = kInvalidHandle;

		m_cmd.kick(true);

		for (uint32_t ii = 0, num = m_numWindows; ii < num; ++ii)
		{
			FrameBufferWgpu& frameBuffer = ii == 0 ? m_mainFrameBuffer : m_frameBuffers[m_windows[ii].idx];
			if (NULL != frameBuffer.m_swapChain
			&& frameBuffer.m_swapChain->m_drawable)
			{
				SwapChainWgpu& swapChain = *frameBuffer.m_swapChain;
				swapChain.m_swapChain.Present();
			}
		}
	}

} /* namespace webgpu */ } // namespace bgfx

#else

namespace bgfx { namespace webgpu
	{
		RendererContextI* rendererCreate(const Init& _init)
		{
			BX_UNUSED(_init);
			return NULL;
		}

		void rendererDestroy()
		{
		}
	} /* namespace webgpu */ } // namespace bgfx

#endif // BGFX_CONFIG_RENDERER_WEBGPU
