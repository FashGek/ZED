#include <Renderer.hpp>
#include <WindowsRendererOGL3.hpp>
#include <CanvasDescription.hpp>
#include <Debugger.hpp>

namespace ZED
{
	namespace Renderer
	{
		WindowsRendererOGL3::WindowsRendererOGL3( )
		{
			memset( &m_PixelFormat, 0, sizeof( PIXELFORMATDESCRIPTOR ) );
			memset( &m_Canvas, 0, sizeof( CanvasDescription ) );
		}

		WindowsRendererOGL3::~WindowsRendererOGL3( )
		{
			// Release the GL RC (if not already done)
			wglMakeCurrent( NULL, NULL );

			if( m_HGLRC )
			{
				wglDeleteContext( m_HGLRC );
				m_HGLRC = NULL;
			}
		}

		ZED_UINT32 WindowsRendererOGL3::Create( GraphicsAdapter *p_Adapter,
			const CanvasDescription &p_Canvas )
		{
			// Grab the canvas
			m_Canvas = p_Canvas;

			if( !m_HDC )
			{
				zedTrace( "The HDC has not been set" );
				return ZED_FAIL;
			}

			switch( m_Canvas.GetBPP( ) )
			{
			case ZED_FORMAT_A8R8G8B8:
				{
					m_PixelFormat.cColorBits = 32;
					m_PixelFormat.iPixelType = PFD_TYPE_RGBA;
					break;
				}
			default:
				{
					zedTrace( "Failed to set the colour format" );
					return ZED_FAIL;
				}
			}

			switch( m_Canvas.GetDepthStencil( ) )
			{
			case ZED_FORMAT_D24S8:
				{
					m_PixelFormat.cDepthBits = 24;
					m_PixelFormat.cStencilBits = 8;
					break;
				}
			default:
				{
					zedTrace( "Failed to set the depth/stencil format" );
					return ZED_FAIL;
				}
			}

			m_PixelFormat.nSize = sizeof( PIXELFORMATDESCRIPTOR );
			m_PixelFormat.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW |
				PFD_DOUBLEBUFFER | PFD_TYPE_RGBA;
			m_PixelFormat.iLayerType = PFD_MAIN_PLANE;

			// Select the most appropriate pixel format
			ZED_UINT32 PixelFormat = ChoosePixelFormat( m_HDC,
				&m_PixelFormat );

			if( PixelFormat == 0 )
			{
				zedTrace( "Failed to choose the pixel format" );
				return ZED_FAIL;
			}

			ZED_BOOL PixelResult = SetPixelFormat( m_HDC, PixelFormat,
				&m_PixelFormat );

			if( PixelResult == ZED_FALSE )
			{
				zedTrace( "Failed to set the pixel format\n" );
				return ZED_FAIL;
			}

			// Create a fallback GL RC (this is necessary, anyway)
			HGLRC TempHGLRC = wglCreateContext( m_HDC );

			if( wglMakeCurrent( m_HDC, TempHGLRC ) == ZED_FALSE )
			{
				zedTrace( "Could not make the HGLRC current\n" );
				return ZED_FAIL;
			}

			m_Ext = GLExtender( m_HDC );

			const ZED_INT32 Attribs[ ] =
			{
				WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
				WGL_CONTEXT_MINOR_VERSION_ARB, 3,
				WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
				0
			};
			
			// Attempt to create an OGL 3.3 context
			if( m_Ext.IsGLExtSupported( "WGL_ARB_create_context" ) ==
				ZED_TRUE )
			{
				m_HGLRC = m_Ext.wglCreateContextAttribsARB( m_HDC, 0, Attribs );
				wglMakeCurrent( NULL, NULL );
				wglDeleteContext( TempHGLRC );
				wglMakeCurrent( m_HDC, m_HGLRC );
			}
			else
			{
				m_HGLRC = TempHGLRC;
			}
			
			if( !m_HGLRC )
			{
				zedTrace( "Failed to create GL Render Context" );
				return ZED_FAIL;
			}

			// Set the viewport
			ResizeCanvas( m_Canvas.GetWidth( ), m_Canvas.GetHeight( ) );

			ZED_INT32 OpenGLVersion [ 2 ];
			glGetIntegerv( GL_MAJOR_VERSION, &OpenGLVersion[ 0 ] );
			glGetIntegerv( GL_MINOR_VERSION, &OpenGLVersion[ 1 ] );

			const GLubyte *GLVersionString = glGetString(GL_VERSION);
			zedTrace( "OpenGL Version: %s\n", GLVersionString );

			return ZED_OK;
		}

		ZED_UINT32 WindowsRendererOGL3::SetHDC( const HDC &p_HDC )
		{
			if( !p_HDC )
			{
				zedTrace( "Failed to set the HDC" );
				return ZED_FAIL;
			}

			m_HDC = p_HDC;

			return ZED_OK;
		}

		void WindowsRendererOGL3::Release( )
		{
			// Release the GL RC
			wglMakeCurrent( NULL, NULL );

			if( m_HGLRC )
			{
				wglDeleteContext( m_HGLRC );
				m_HGLRC = NULL;
			}
		}

		void WindowsRendererOGL3::ForceClear( ZED_BOOL p_Colour, ZED_BOOL p_Depth,
			ZED_BOOL p_Stencil )
		{
			// Set the glClear flags
			ZED_DWORD Flags = 0;
			
			if( p_Colour == ZED_TRUE )
			{
				Flags |= GL_COLOR_BUFFER_BIT;
			}

			if( p_Depth == ZED_TRUE )
			{
				Flags |= GL_DEPTH_BUFFER_BIT;
			}

			if( p_Stencil == ZED_TRUE )
			{
				Flags |= GL_STENCIL_BUFFER_BIT;
			}

			glClear( Flags );
		}

		ZED_UINT32 WindowsRendererOGL3::BeginScene( ZED_BOOL p_Colour,
			ZED_BOOL p_Depth, ZED_BOOL p_Stencil )
		{
			// Set the glClear flags
			ZED_DWORD Flags = 0;
			
			if( p_Colour == ZED_TRUE )
			{
				Flags |= GL_COLOR_BUFFER_BIT;
			}

			if( p_Depth == ZED_TRUE )
			{
				Flags |= GL_DEPTH_BUFFER_BIT;
			}

			if( p_Stencil == ZED_TRUE )
			{
				Flags |= GL_STENCIL_BUFFER_BIT;
			}

			glClear( Flags );

			return ZED_OK;
		}

		void WindowsRendererOGL3::EndScene( )
		{
			SwapBuffers( m_HDC );
		}

		void WindowsRendererOGL3::ClearColour( ZED_FLOAT32 p_Red,
			ZED_FLOAT32 p_Green, ZED_FLOAT32 p_Blue )
		{
			glClearColor( p_Red, p_Green, p_Blue, 1.0f );
		}

		ZED_BOOL WindowsRendererOGL3::ToggleFullscreen( )
		{
			return ZED_TRUE;
		}

		ZED_BOOL WindowsRendererOGL3::ResizeCanvas( ZED_UINT32 p_Width,
			ZED_UINT32 p_Height )
		{
			// Make sure that there isn't a divide by zero
			if( p_Width == 0 )
			{
				return ZED_FALSE;
			}

			if( p_Height == 0 )
			{
				return ZED_FALSE;
			}

			// Reset the coordinate system
			glLoadIdentity( );

			m_Canvas.SetWidth( p_Width );
			m_Canvas.SetHeight( p_Height );

			// Get the aspect ratio for the window
			m_AspectRatio = static_cast< ZED_FLOAT32 >( m_Canvas.GetWidth( ) )
				/ static_cast< ZED_FLOAT32 >( m_Canvas.GetHeight( ) );

			return ZED_TRUE;
		}
	}
}