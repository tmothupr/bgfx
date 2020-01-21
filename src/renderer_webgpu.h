/*
 * Copyright 2011-2019 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BGFX_RENDERER_WEBGPU_H_HEADER_GUARD
#define BGFX_RENDERER_WEBGPU_H_HEADER_GUARD

#include "bgfx_p.h"

#if BGFX_CONFIG_RENDERER_WEBGPU

#if !BX_PLATFORM_EMSCRIPTEN
#include <dawn/webgpu_cpp.h>
#include <dawn/dawn_wsi.h>
#else
#include <webgpu/webgpu_cpp.h>
#endif

#define BGFX_WEBGPU_PROFILER_BEGIN(_view, _abgr)         \
	BX_MACRO_BLOCK_BEGIN                              \
		BGFX_PROFILER_BEGIN(s_viewName[view], _abgr); \
	BX_MACRO_BLOCK_END

#define BGFX_WEBGPU_PROFILER_BEGIN_LITERAL(_name, _abgr)   \
	BX_MACRO_BLOCK_BEGIN                                \
		BGFX_PROFILER_BEGIN_LITERAL("" # _name, _abgr); \
	BX_MACRO_BLOCK_END

#define BGFX_WEBGPU_PROFILER_END() \
	BX_MACRO_BLOCK_BEGIN        \
		BGFX_PROFILER_END();    \
	BX_MACRO_BLOCK_END

#define WEBGPU_MAX_FRAMES_IN_FLIGHT 3

namespace bgfx {
	namespace webgpu
	{

		template <typename Ty>
		class StateCacheT
		{
		public:
			void add(uint64_t _id, Ty _item)
			{
				invalidate(_id);
				m_hashMap.insert(stl::make_pair(_id, _item));
			}

			Ty find(uint64_t _id)
			{
				typename HashMap::iterator it = m_hashMap.find(_id);
				if(it != m_hashMap.end())
				{
					return it->second;
				}

				return NULL;
			}

			void invalidate(uint64_t _id)
			{
				typename HashMap::iterator it = m_hashMap.find(_id);
				if(it != m_hashMap.end())
				{
					release(it->second);
					m_hashMap.erase(it);
				}
			}

			void invalidate()
			{
				for(typename HashMap::iterator it = m_hashMap.begin(), itEnd = m_hashMap.end(); it != itEnd; ++it)
				{
					release(it->second);
				}

				m_hashMap.clear();
			}

			uint32_t getCount() const
			{
				return uint32_t(m_hashMap.size());
			}

		private:
			typedef stl::unordered_map<uint64_t, Ty> HashMap;
			HashMap m_hashMap;
		};

		struct BufferWgpu
		{
			BufferWgpu()
				: m_flags(BGFX_BUFFER_NONE)
				, m_dynamic(NULL)
			{
			}

			void create(uint32_t _size, void* _data, uint16_t _flags, uint16_t _stride = 0, bool _vertex = false);
			void update(uint32_t _offset, uint32_t _size, void* _data, bool _discard = false);

			void destroy()
			{
				m_ptr.Destroy();

				if(NULL != m_dynamic)
				{
					BX_DELETE(g_allocator, m_dynamic);
					m_dynamic = NULL;
				}
			}

			uint32_t m_size;
			uint16_t m_flags;
			bool     m_vertex;

			wgpu::Buffer   m_ptr;
			uint8_t* m_dynamic;
		};

		typedef BufferWgpu IndexBufferWgpu;

		struct VertexBufferWgpu : public BufferWgpu
		{
			VertexBufferWgpu()
				: BufferWgpu()
			{
			}

			void create(uint32_t _size, void* _data, VertexLayoutHandle _declHandle, uint16_t _flags);

			VertexLayoutHandle m_layoutHandle;
		};

		struct SamplerInfo
		{
			uint32_t      m_index;
			UniformHandle m_uniform;
			bool          m_fragment;
		};

		struct ShaderWgpu
		{
			void create(ShaderHandle _handle, const Memory* _mem);
			void destroy()
			{
				m_module = nullptr;
			}

			String name() { return getName(m_handle); }

			ShaderHandle m_handle;

			wgpu::ShaderModule m_module;

			uint32_t* m_code = nullptr;
			size_t m_codeSize = 0;

			UniformBuffer* m_constantBuffer[UniformSet::Count] = {};

			PredefinedUniform m_predefined[PredefinedUniform::Count];
			uint16_t m_attrMask[Attrib::Count];
			uint8_t m_attrRemap[Attrib::Count];

			uint32_t m_hash = 0;
			uint16_t m_numUniforms = 0;
			uint16_t m_size = 0;
			uint8_t m_numPredefined = 0;
			uint8_t m_numAttrs = 0;
			uint16_t m_numThreads[3];

			SamplerInfo m_samplerInfo[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];
			wgpu::BindGroupLayoutBinding m_samplers[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];
			wgpu::BindGroupLayoutBinding m_textures[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];
			uint8_t m_numSamplers = 0;
		};

		struct PipelineStateWgpu;

		struct ProgramWgpu
		{
			ProgramWgpu()
				: m_vsh(NULL)
				, m_fsh(NULL)
				, m_computePS(NULL)
				, m_numSamplers(0)
			{
			}

			void create(const ShaderWgpu* _vsh, const ShaderWgpu* _fsh);
			void destroy();

			const ShaderWgpu* m_vsh;
			const ShaderWgpu* m_fsh;

			PredefinedUniform m_predefined[PredefinedUniform::Count * 2];
			uint8_t m_numPredefined;

			PipelineStateWgpu* m_computePS;

			wgpu::BindGroupLayout m_uniforms;
			wgpu::BindGroupLayout m_textures;
			wgpu::BindGroupLayout m_samplers;
			uint32_t			  m_bindGroupLayoutHash;

			SamplerInfo m_samplerInfo[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];
			uint32_t	m_numSamplers;
		};

		constexpr size_t kMaxVertexInputs = 16;
		constexpr size_t kMaxVertexAttributes = 16;
		constexpr size_t kMaxColorAttachments = BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS;

		constexpr uint32_t kMinUniformBufferOffsetAlignment = 256;

		struct RenderPassDescriptor
		{
			RenderPassDescriptor();

			wgpu::RenderPassDescriptor desc;

			wgpu::RenderPassColorAttachmentDescriptor colorAttachments[kMaxColorAttachments];
			//uint32_t colorAttachmentCount = 0;

			wgpu::RenderPassDepthStencilAttachmentDescriptor depthStencilAttachment;
		};

		struct VertexStateDescriptor
		{
			VertexStateDescriptor();

			wgpu::VertexStateDescriptor desc;

			wgpu::VertexBufferLayoutDescriptor vertexBuffers[kMaxVertexInputs];
			//uint32_t numVertexBuffers = 0;

			wgpu::VertexAttributeDescriptor attributes[kMaxVertexAttributes];
			//uint32_t numAttributes = 0;
		};

		struct RenderPipelineDescriptor
		{
			RenderPipelineDescriptor();

			wgpu::RenderPipelineDescriptor desc;

			//wgpu::ProgrammableStageDescriptor vertexStage;
			wgpu::ProgrammableStageDescriptor fragmentStage;

			wgpu::VertexStateDescriptor inputState;

			wgpu::RasterizationStateDescriptor rasterizationState;
			wgpu::DepthStencilStateDescriptor depthStencilState;
			wgpu::ColorStateDescriptor colorStates[kMaxColorAttachments];
		};

		struct BindStateWgpu
		{
			void clear();

			wgpu::BindGroupBinding m_uniforms[2];
			wgpu::BindGroupBinding m_textures[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];
			wgpu::BindGroupBinding m_samplers[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];

			wgpu::BindGroup m_uniformsGroup;
			wgpu::BindGroup m_texturesGroup;
			wgpu::BindGroup m_samplersGroup;
		};

		struct PipelineStateWgpu
		{
			RenderPipelineDescriptor m_rpd;

			uint16_t m_numThreads[3] = { 1, 1, 1 };

			wgpu::BindGroupLayout m_bind;

			wgpu::RenderPipeline m_rps;
			wgpu::ComputePipeline m_cps;
		};

		void release(PipelineStateWgpu* _ptr)
		{
			BX_DELETE(g_allocator, _ptr);
		}

		class ScratchBufferWgpu
		{
		public:
			void create(uint32_t _size); // , uint32_t _maxBindGroups);
			void destroy();
			void reset();

			BindStateWgpu m_bindStates[1024] = {};
			wgpu::Buffer m_buffer;
			uint32_t m_offset;
			uint32_t m_size;
			uint32_t m_currentBindState;
			//uint32_t m_maxBindStates;
		};

		struct TextureWgpu
		{
			enum Enum
			{
				Texture2D,
				Texture3D,
				TextureCube,
			};

			TextureWgpu()
				: m_flags(0)
				, m_width(0)
				, m_height(0)
				, m_depth(0)
				, m_numMips(0)
			{
				for(uint32_t ii = 0; ii < BX_COUNTOF(m_ptrMips); ++ii)
				{
					m_ptrMips[ii] = NULL;
				}
			}

			void create(const Memory* _mem, uint64_t _flags, uint8_t _skip);

			void destroy()
			{
				m_ptr.Destroy();
			}

			void update(
				uint8_t _side
				, uint8_t _mip
				, const Rect& _rect
				, uint16_t _z
				, uint16_t _depth
				, uint16_t _pitch
				, const Memory* _mem
			);

			wgpu::TextureView m_view;
			wgpu::TextureView getTextureMipLevel(int _mip);

			wgpu::Texture m_ptr;
			wgpu::Texture m_ptrMsaa;
			wgpu::TextureView m_ptrMips[14];
			wgpu::Sampler m_sampler;
			uint64_t m_flags;
			uint32_t m_width;
			uint32_t m_height;
			uint32_t m_depth;
			uint8_t m_type;
			uint8_t m_requestedFormat;
			uint8_t m_textureFormat;
			uint8_t m_numMips;
			uint8_t m_numLayers;
			uint8_t m_sampleCount;
		};

		struct SamplerStateWgpu
		{
			wgpu::Sampler m_sampler;
		};

		void release(SamplerStateWgpu* _ptr)
		{
			BX_DELETE(g_allocator, _ptr);
		}

		struct FrameBufferWgpu;

		struct SwapChainWgpu
		{
			SwapChainWgpu()
				//: m_metalLayer(nil)
				//, m_drawable(nil)
				//, m_drawableTexture(nil)
				: m_backBufferColorMsaa()
				, m_backBufferDepth()
				, m_maxAnisotropy(0)
			{
			}

			~SwapChainWgpu();

			void init(wgpu::Device _device, void* _nwh, uint32_t _width, uint32_t _height);
			void resize(FrameBufferWgpu& _frameBuffer, uint32_t _width, uint32_t _height, uint32_t _flags);

			void flip();

			wgpu::TextureView current();

#if !BX_PLATFORM_EMSCRIPTEN
			DawnSwapChainImplementation m_impl;
#endif

			wgpu::SwapChain m_swapChain;

			wgpu::TextureView m_drawable;

			wgpu::Texture m_backBufferColorMsaa;
			wgpu::Texture m_backBufferDepth;

			wgpu::TextureFormat m_colorFormat;
			wgpu::TextureFormat m_depthFormat;

			uint32_t m_maxAnisotropy;
			uint8_t m_sampleCount;
		};

		struct FrameBufferWgpu
		{
			FrameBufferWgpu()
				: m_swapChain(NULL)
				, m_nwh(NULL)
				, m_denseIdx(UINT16_MAX)
				, m_pixelFormatHash(0)
				, m_num(0)
			{
				m_depthHandle.idx = kInvalidHandle;
			}

			void create(uint8_t _num, const Attachment* _attachment);
			bool create(
				uint16_t _denseIdx
				, void* _nwh
				, uint32_t _width
				, uint32_t _height
				, TextureFormat::Enum _format
				, TextureFormat::Enum _depthFormat
			);
			void postReset();
			uint16_t destroy();

			SwapChainWgpu* m_swapChain;
			void* m_nwh;
			uint32_t m_width;
			uint32_t m_height;
			uint16_t m_denseIdx;

			uint32_t m_pixelFormatHash;

			TextureHandle m_colorHandle[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS - 1];
			TextureHandle m_depthHandle;
			Attachment m_colorAttachment[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS - 1];
			Attachment m_depthAttachment;
			uint8_t m_num; // number of color handles
		};

		struct CommandQueueWgpu
		{
			CommandQueueWgpu()
				: m_releaseWriteIndex(0)
				, m_releaseReadIndex(0)
			{
			}

			void init(wgpu::Queue _queue);
			void shutdown();
			void begin();
			void kick(bool _endFrame, bool _waitForFinish = false);
			void finish(bool _finishAll = false);
			void release(wgpu::Buffer _buffer);
			void consume();

#if BGFX_CONFIG_MULTITHREADED
			bx::Semaphore 		 m_framesSemaphore;
#endif

			wgpu::Queue		     m_queue;
			wgpu::CommandEncoder m_encoder;

			int m_releaseWriteIndex;
			int m_releaseReadIndex;

			typedef stl::vector<wgpu::Buffer> ResourceArray;
			ResourceArray m_release[WEBGPU_MAX_FRAMES_IN_FLIGHT];
		};

		struct TimerQueryWgpu
		{
			TimerQueryWgpu()
				: m_control(4)
			{
			}

			void init();
			void shutdown();
			uint32_t begin(uint32_t _resultIdx);
			void end(uint32_t _idx);
			void addHandlers(wgpu::CommandBuffer& _commandBuffer);
			bool get();

			struct Result
			{
				void reset()
				{
					m_begin = 0;
					m_end = 0;
					m_pending = 0;
				}

				uint64_t m_begin;
				uint64_t m_end;
				uint32_t m_pending;
			};

			uint64_t m_begin;
			uint64_t m_end;
			uint64_t m_elapsed;
			uint64_t m_frequency;

			Result m_result[4 * 2];
			bx::RingBufferControl m_control;
		};

		struct OcclusionQueryWgpu
		{
			OcclusionQueryWgpu()
				: m_control(BX_COUNTOF(m_query))
			{
			}

			void postReset();
			void preReset();
			void begin(wgpu::RenderPassEncoder& _rce, Frame* _render, OcclusionQueryHandle _handle);
			void end(wgpu::RenderPassEncoder& _rce);
			void resolve(Frame* _render, bool _wait = false);
			void invalidate(OcclusionQueryHandle _handle);

			struct Query
			{
				OcclusionQueryHandle m_handle;
			};

			wgpu::Buffer m_buffer;
			Query m_query[BGFX_CONFIG_MAX_OCCLUSION_QUERIES];
			bx::RingBufferControl m_control;
		};

	} /* namespace metal */
} // namespace bgfx

#endif // BGFX_CONFIG_RENDERER_WEBGPU

#endif // BGFX_RENDERER_WEBGPU_H_HEADER_GUARD
