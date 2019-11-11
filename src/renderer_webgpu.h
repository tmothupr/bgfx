/*
 * Copyright 2011-2019 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BGFX_RENDERER_WEBGPU_H_HEADER_GUARD
#define BGFX_RENDERER_WEBGPU_H_HEADER_GUARD

#include "bgfx_p.h"

#if BGFX_CONFIG_RENDERER_WEBGPU

#include <dawn/dawncpp.h>
#include <dawn/dawn_wsi.h>

namespace webgpu = dawn;

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
	namespace wgpu
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

			webgpu::Buffer   m_ptr;
			uint8_t* m_dynamic;
		};

		typedef BufferWgpu IndexBufferWgpu;

		struct VertexBufferWgpu : public BufferWgpu
		{
			VertexBufferWgpu()
				: BufferWgpu()
			{
			}

			void create(uint32_t _size, void* _data, VertexDeclHandle _declHandle, uint16_t _flags);

			VertexDeclHandle m_decl;
		};

		struct SamplerInfo
		{
			uint32_t      m_index;
			UniformHandle m_uniform;
			bool          m_fragment;
		};

		struct ShaderWgpu
		{
			ShaderWgpu()
				: m_constantBuffer{}
				, m_hash(0)
				, m_numUniforms(0)
				, m_numPredefined(0)
			{
			}

			void create(const Memory* _mem);
			void destroy()
			{
				m_module.Release();
			}

			webgpu::ShaderModule m_module;

			UniformBuffer* m_constantBuffer[UniformSet::Count];

			PredefinedUniform m_predefined[PredefinedUniform::Count];
			uint16_t m_attrMask[Attrib::Count];
			uint8_t m_attrRemap[Attrib::Count];

			uint32_t m_hash;
			uint16_t m_numUniforms;
			uint16_t m_size;
			uint8_t m_numPredefined;
			uint8_t m_numAttrs;
			uint16_t m_numThreads[3];

			SamplerInfo m_samplerInfo[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];
			webgpu::BindGroupLayoutBinding m_samplers[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];
			webgpu::BindGroupLayoutBinding m_textures[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];
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

			webgpu::BindGroupLayout m_uniforms;
			webgpu::BindGroupLayout m_textures;
			webgpu::BindGroupLayout m_samplers;

			SamplerInfo m_samplerInfo[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];
			uint32_t	m_numSamplers;
		};

		struct PipelineStateWgpu
		{
			PipelineStateWgpu()
			{
				m_numThreads[0] = 1;
				m_numThreads[1] = 1;
				m_numThreads[2] = 1;
			}

			~PipelineStateWgpu()
			{
			}

			uint16_t 	m_numThreads[3];

			webgpu::BindGroupLayout m_bind;

			webgpu::RenderPipeline m_rps;
			webgpu::ComputePipeline m_cps;
		};

		void release(PipelineStateWgpu* _ptr)
		{
			BX_DELETE(g_allocator, _ptr);
		}

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

			webgpu::TextureView m_view;
			webgpu::TextureView getTextureMipLevel(int _mip);

			webgpu::Texture m_ptr;
			webgpu::Texture m_ptrMsaa;
			webgpu::TextureView m_ptrMips[14];
			webgpu::Sampler m_sampler;
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
			webgpu::Sampler m_sampler;
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

			void init(webgpu::Device _device, void* _nwh);
			void resize(FrameBufferWgpu& _frameBuffer, uint32_t _width, uint32_t _height, uint32_t _flags);

			webgpu::Texture current();

			DawnSwapChainImplementation m_impl;

			webgpu::SwapChain m_swapChain;

			webgpu::Texture m_drawable;
			webgpu::Texture m_backBufferColorMsaa;
			webgpu::Texture m_backBufferDepth;

			webgpu::TextureFormat m_colorFormat;
			webgpu::TextureFormat m_depthFormat;

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
			void create(
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

			void init(webgpu::Device _device);
			void shutdown();
			void begin();
			void kick(bool _endFrame, bool _waitForFinish = false);
			void finish(bool _finishAll = false);
			void release(webgpu::Buffer _buffer);
			void consume();

			bx::Semaphore m_framesSemaphore;

			webgpu::Queue		   m_queue;
			webgpu::CommandEncoder m_encoder;

			int m_releaseWriteIndex;
			int m_releaseReadIndex;

			typedef stl::vector<webgpu::Buffer> ResourceArray;
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
			void addHandlers(CommandBuffer& _commandBuffer);
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
			void begin(webgpu::RenderPassEncoder& _rce, Frame* _render, OcclusionQueryHandle _handle);
			void end(webgpu::RenderPassEncoder& _rce);
			void resolve(Frame* _render, bool _wait = false);
			void invalidate(OcclusionQueryHandle _handle);

			struct Query
			{
				OcclusionQueryHandle m_handle;
			};

			webgpu::Buffer m_buffer;
			Query m_query[BGFX_CONFIG_MAX_OCCLUSION_QUERIES];
			bx::RingBufferControl m_control;
		};

	} /* namespace metal */
} // namespace bgfx

#endif // BGFX_CONFIG_RENDERER_WEBGPU

#endif // BGFX_RENDERER_WEBGPU_H_HEADER_GUARD
