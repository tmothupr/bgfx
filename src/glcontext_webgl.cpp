/*
 * Copyright 2011-2019 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "bgfx_p.h"

#if (BGFX_CONFIG_RENDERER_OPENGLES || BGFX_CONFIG_RENDERER_OPENGL)
#	include "renderer_gl.h"

#	if BGFX_USE_WEBGL

namespace bgfx { namespace gl
{
#	define GL_IMPORT(_optional, _proto, _func, _import) _proto _func = NULL
#	include "glimports.h"

	struct SwapChainGL
	{
		SwapChainGL(const char* _target, EmscriptenWebGLContextAttributes _config)
			//: m_nwh(_nwh)
			: m_target(_target)
			, m_display(_display)
		{
			m_context = emscripten_webgl_create_context(_target, &_config);
			//BGFX_FATAL(m_context == 0, Fatal::UnableToInitialize, "Failed to create surface.");
			//BX_CHECK(NULL != m_context, "Create swap chain failed: %x", eglGetError());

			makeCurrent();
			GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f) );
			GL_CHECK(glClear(GL_COLOR_BUFFER_BIT) );
			swapBuffers();
			GL_CHECK(glClear(GL_COLOR_BUFFER_BIT) );
			swapBuffers();
		}

		~SwapChainGL()
		{
			//emscripten_webgl_make_context_current(0);
			emscripten_webgl_destroy_context(m_context);
		}

		void makeCurrent()
		{
			emscripten_webgl_make_context_current(m_window);
		}

		void swapBuffers()
		{
			//eglSwapBuffers(m_display, m_surface);
		}

		//EGLNativeWindowType m_nwh;
		const char* m_target;
		EMSCRIPTEN_WEBGL_CONTEXT_HANDLE m_context;
	};

	void GlContext::create(uint32_t _width, uint32_t _height)
	{
		if (NULL == g_platformData.context)
		{
			emscripten_webgl_init_context_attributes(&attrs);
			attrs.depth = 1;
			attrs.stencil = 1;
			//attrs.antialias = 1;
			attrs.majorVersion = 2;
			attrs.minorVersion = 0;
			attrs.enableExtensionsByDefault = 1;

			for (uint32_t ii = 2; ii > 0; --ii)
			{
				attrs.majorVersion = ii;

				m_context = emscripten_webgl_create_context(0, &attrs);
				//m_context = emscripten_webgl_create_context("#canvas", &attrs);
				if (0 != m_context)
				{
					break;
				}

				BX_TRACE("Failed to create WebGL context with version %i.", ii);
			}

			BGFX_FATAL(m_context == 0, Fatal::UnableToInitialize, "Failed to create context.");

			m_config = attrs;

			//BX_TRACE("EGL info:");
			//const char* clientApis = eglQueryString(m_display, EGL_CLIENT_APIS);
			//BX_TRACE("   APIs: %s", clientApis); BX_UNUSED(clientApis);
			//
			//const char* vendor = eglQueryString(m_display, EGL_VENDOR);
			//BX_TRACE(" Vendor: %s", vendor); BX_UNUSED(vendor);
			//
			//const char* version = eglQueryString(m_display, EGL_VERSION);
			//BX_TRACE("Version: %s", version); BX_UNUSED(version);
			//
			//const char* extensions = eglQueryString(m_display, EGL_EXTENSIONS);
			//BX_TRACE("Supported EGL extensions:");
			//dumpExtensions(extensions);

			EMSCRIPTEN_RESULT success = emscripten_webgl_make_context_current(m_context);

			BGFX_FATAL(success != EMSCRIPTEN_RESULT_SUCCESS, Fatal::UnableToInitialize, "Failed to set context.");
			m_current = NULL;
		}

		import();

		g_internalData.context = m_context;
	}

	void GlContext::destroy()
	{
		if (0 != m_context)
		{
			emscripten_webgl_destroy_context(m_context);
			m_context = 0;
		}
	}

	void GlContext::resize(uint32_t _width, uint32_t _height, uint32_t _flags)
	{
		emscripten_set_canvas_size(_width, _height);

		if (NULL != m_display)
		{
			//bool vsync = !!(_flags&BGFX_RESET_VSYNC);
			//eglSwapInterval(m_display, vsync ? 1 : 0);
		}
	}

	uint64_t GlContext::getCaps() const
	{
		return BGFX_CAPS_SWAP_CHAIN;
		//return 0;
	}

	SwapChainGL* GlContext::createSwapChain(void* _nwh)
	{
		return BX_NEW(g_allocator, SwapChainGL)((const char*) _nwh, m_config);
	}

	void GlContext::destroySwapChain(SwapChainGL* _swapChain)
	{
		BX_DELETE(g_allocator, _swapChain);
	}

	void GlContext::swap(SwapChainGL* _swapChain)
	{
		makeCurrent(_swapChain);

		if (NULL == _swapChain)
		{
			if (NULL != m_display)
			{
				eglSwapBuffers(m_display, m_surface);
			}
		}
		else
		{
			_swapChain->swapBuffers();
		}
	}

	void GlContext::makeCurrent(SwapChainGL* _swapChain)
	{
		if (m_current != _swapChain)
		{
			m_current = _swapChain;

			if (NULL == _swapChain)
			{
				if (0 != m_context)
				{
					emscripten_webgl_make_context_current(m_window);
				}
			}
			else
			{
				_swapChain->makeCurrent();
			}
		}
	}

	void GlContext::import()
	{
		BX_TRACE("Import:");
#		define GL_EXTENSION(_optional, _proto, _func, _import) \
					{ \
						if (NULL == _func) \
						{ \
							_func = (_proto)eglGetProcAddress(#_import); \
							BX_TRACE("\t%p " #_func " (" #_import ")", _func); \
							BGFX_FATAL(_optional || NULL != _func, Fatal::UnableToInitialize, "Failed to create OpenGLES context. eglGetProcAddress(\"%s\")", #_import); \
						} \
					}
#	include "glimports.h"
	}

} /* namespace gl */ } // namespace bgfx

#	endif // BGFX_USE_WEBGL
#endif // (BGFX_CONFIG_RENDERER_OPENGLES || BGFX_CONFIG_RENDERER_OPENGL)
