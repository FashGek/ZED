#include <LinuxWindow.hpp>
#include <X11/extensions/Xrandr.h>
#include <Renderer.hpp>
#include <Debugger.hpp>

namespace ZED
{
	namespace Renderer
	{
		ZED_UINT32 GetNativeScreenSize( ZED_UINT32 p_ScreenNumber )
		{
			return ZED_OK;
		}

		ZED_UINT32 GetScreenCount( ZED_UINT32 *p_pScreenCount )
		{
			Display *pDisplay = XOpenDisplay( ZED_NULL );
			if( pDisplay == ZED_NULL )
			{
				( *p_pScreenCount ) = 0;
				
				zedTrace( "[ZED::Renderer::GetScreenCount] <ERROR> "
					"Could not open display\n" );

				return ZED_FAIL;
			}

			ZED_UINT32 ScreenCount = ScreenCount( pDisplay );
			XCloseDisplay( pDisplay );

			( *p_pScreenCount ) = ScreenCount;

			return ZED_OK;
		}

		ZED_UINT32 EnumerateScreenSizes( ZED_SCREENSIZE **p_ppSizes,
			ZED_MEMSIZE *p_pCount, const ZED_UINT32 p_ScreenNumber )
		{
			Display *pDisplay = XOpenDisplay( ZED_NULL );
			ZED_SINT32 TotalSizes = 0;
			XRRScreenSize *pScreenSize = XRRSizes( pDisplay, p_ScreenNumber,
				&TotalSizes );
			XCloseDisplay( pDisplay );

			zedTrace( "[ZED::Renderer::EnumerateScreenSizes] <INFO> "
				"Found %d resolutions\n", TotalSizes );

			( *p_ppSizes ) = new ZED_SCREENSIZE[ TotalSizes ];

			for( ZED_SINT32 i = 0; i < TotalSizes; ++i )
			{
				zedTrace( "\t%d: %dx%d\n",
					i, pScreenSize[ i ].width, pScreenSize[ i ].height );

				( *p_ppSizes )[ i ].Width = pScreenSize[ i ].width;
				( *p_ppSizes )[ i ].Height = pScreenSize[ i ].height;
			}

			( *p_pCount ) = TotalSizes;
			
			return ZED_OK;
		}

		LinuxWindow::LinuxWindow( )
		{
			m_pDisplay = ZED_NULL;
		}

		LinuxWindow::~LinuxWindow( )
		{
			this->Destroy( );
		}

		ZED_UINT32 LinuxWindow::Create( const ZED_UINT32 p_X,
			const ZED_UINT32 p_Y, const ZED_UINT32 p_Width,
			const ZED_UINT32 p_Height )
		{
			m_pDisplay = XOpenDisplay( 0 );

			// Is there a way to detach this?
			int VisualAttribs[ ] =
			{
				GLX_X_RENDERABLE,	True,
				GLX_DRAWABLE_TYPE,	GLX_WINDOW_BIT,
				GLX_RENDER_TYPE,	GLX_RGBA_BIT,
				GLX_X_VISUAL_TYPE,	GLX_TRUE_COLOR,
				GLX_RED_SIZE,		8,
				GLX_GREEN_SIZE,		8,
				GLX_BLUE_SIZE,		8,
				GLX_ALPHA_SIZE,		8,
				GLX_DEPTH_SIZE,		24,
				GLX_STENCIL_SIZE,	8,
				GLX_DOUBLEBUFFER,	True,
				None
			};

			ZED_SINT32	GLXMajor = 0, GLXMinor = 0;

			if( !glXQueryVersion( m_pDisplay, &GLXMajor, &GLXMinor ) ||
				( ( GLXMajor == 1 ) && ( GLXMinor < 3 ) ) || GLXMajor < 1 )
			{
				return ZED_FAIL;
			}

			ZED_SINT32 FBCount = 0;
			GLXFBConfig *pFBC = glXChooseFBConfig( m_pDisplay,
				DefaultScreen( m_pDisplay ), VisualAttribs, &FBCount );

			if( !pFBC )
			{
				return ZED_FAIL;
			}

			// For now, just use the first one found
			GLXFBConfig GLFBConfig = pFBC[ 0 ];

			XFree( pFBC );
			pFBC = ZED_NULL;

			m_pVisualInfo = glXGetVisualFromFBConfig( m_pDisplay,
				GLFBConfig );

			XSetWindowAttributes WinAttribs;

			WinAttribs.colormap = XCreateColormap( m_pDisplay,
				RootWindow( m_pDisplay, m_pVisualInfo->screen ),
				m_pVisualInfo->visual, AllocNone );
			WinAttribs.background_pixmap = None;
			WinAttribs.border_pixel = 0;
			WinAttribs.event_mask = StructureNotifyMask | ExposureMask |
				KeyPressMask | KeyPressMask |
				ButtonPressMask | ButtonReleaseMask |
				ResizeRedirectMask | PointerMotionMask |
				FocusChangeMask | EnterWindowMask | LeaveWindowMask;
			WinAttribs.override_redirect = True;

			m_Window = XCreateWindow( m_pDisplay,
				RootWindow( m_pDisplay, m_pVisualInfo->screen ),
				p_X, p_Y, p_Width, p_Height, 0,
				m_pVisualInfo->depth, InputOutput,
				m_pVisualInfo->visual,
				CWEventMask | CWColormap | CWBorderPixel |
				CWOverrideRedirect, &WinAttribs );
			
			XMapWindow( m_pDisplay, m_Window );
			XMapRaised( m_pDisplay, m_Window );
			XMoveWindow( m_pDisplay, m_Window, p_X, p_Y );
			XRaiseWindow( m_pDisplay, m_Window );

			m_WindowData.X11Window = m_Window;
			m_WindowData.pX11Display = m_pDisplay;
			m_WindowData.pX11VisualInfo = m_pVisualInfo;
			m_WindowData.X11GLXFBConfig = GLFBConfig;

			return ZED_OK;
		}

		void LinuxWindow::Destroy( )
		{
			if( m_Window )
			{
				XDestroyWindow( m_pDisplay, m_Window );
			}

			if( m_pDisplay )
			{
				XCloseDisplay( m_pDisplay );
				m_pDisplay = ZED_NULL;
			}
		}

		ZED_UINT32 LinuxWindow::Update( )
		{
			return ZED_OK;
		}
	}
}

