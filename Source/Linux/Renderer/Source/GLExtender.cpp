#include <OGL/GLExtender.hpp>

///////////////////////////////////////////////////////////////////////////////
// GLX Extensions /////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
PFNGLXCREATECONTEXTATTRIBSARBPROC	__zglCreateContextAttribsARB = ZED_NULL;

///////////////////////////////////////////////////////////////////////////////
// OpenGL 2.0 Extensions //////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

PFNGLGETSTRINGIPROC					__zglGetStringi = ZED_NULL;

// Define all the possible OpenGL extensions, initialising them to zero
// OpenGL 2.0 [Shaders]
PFNGLCREATESHADERPROC				__zglCreateShader = ZED_NULL;
PFNGLDELETESHADERPROC				__zglDeleteShader = ZED_NULL;
PFNGLSHADERSOURCEPROC				__zglShaderSource = ZED_NULL;
PFNGLCOMPILESHADERPROC				__zglCompileShader = ZED_NULL;
PFNGLGETSHADERINFOLOGPROC			__zglGetShaderInfoLog = ZED_NULL;
PFNGLCREATEPROGRAMPROC				__zglCreateProgram = ZED_NULL;
PFNGLATTACHSHADERPROC				__zglAttachShader = ZED_NULL;
PFNGLDETACHSHADERPROC				__zglDetachShader = ZED_NULL;
PFNGLISSHADERPROC					__zglIsShader = ZED_NULL;
PFNGLGETSHADERIVPROC				__zglGetShaderiv = ZED_NULL;
PFNGLLINKPROGRAMPROC				__zglLinkProgram = ZED_NULL;
PFNGLGETPROGRAMINFOLOGPROC			__zglGetProgramInfoLog = ZED_NULL;
PFNGLUSEPROGRAMPROC					__zglUseProgram = ZED_NULL;
PFNGLDELETEPROGRAMPROC				__zglDeleteProgram = ZED_NULL;
PFNGLISPROGRAMPROC					__zglIsProgram = ZED_NULL;
PFNGLVALIDATEPROGRAMPROC			__zglValidateProgram = ZED_NULL;
PFNGLGETPROGRAMIVPROC				__zglGetProgramiv = ZED_NULL;
PFNGLGENVERTEXARRAYSPROC			__zglGenVertexArrays = ZED_NULL;
PFNGLBINDVERTEXARRAYPROC			__zglBindVertexArray = ZED_NULL;
PFNGLDELETEVERTEXARRAYSPROC			__zglDeleteVertexArrays = ZED_NULL;
PFNGLGENBUFFERSPROC					__zglGenBuffers = ZED_NULL;
PFNGLBINDBUFFERPROC					__zglBindBuffer = ZED_NULL;
PFNGLBUFFERDATAPROC					__zglBufferData = ZED_NULL;
PFNGLBUFFERSUBDATAPROC				__zglBufferSubData = ZED_NULL;
PFNGLDELETEBUFFERSPROC				__zglDeleteBuffers = ZED_NULL;
PFNGLBINDATTRIBLOCATIONPROC			__zglBindAttribLocation = ZED_NULL;
PFNGLVERTEXATTRIBPOINTERPROC		__zglVertexAttribPointer = ZED_NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC	__zglEnableVertexAttribArray = ZED_NULL;
PFNGLGETUNIFORMLOCATIONPROC			__zglGetUniformLocation = ZED_NULL;
PFNGLUNIFORMMATRIX4FVPROC			__zglUniformMatrix4fv = ZED_NULL;
PFNGLBINDFRAGDATALOCATIONPROC		__zglBindFragDataLocation = ZED_NULL;
PFNGLUNIFORM1IPROC					__zglUniform1i = ZED_NULL;
PFNGLUNIFORM1FPROC					__zglUniform1f = ZED_NULL;
PFNGLUNIFORM3FVPROC					__zglUniform3fv = ZED_NULL;

// OpenGL 2.0 [Textures]
PFNGLACTIVETEXTUREPROC				__zglActiveTexture = ZED_NULL;
PFNGLDELETETEXTURESEXTPROC			__zglDeleteTextures = ZED_NULL;

namespace ZED
{
	namespace Renderer
	{
		// Initialise all OpenGL 2.0 extensions
		static ZED_UINT32 zglInitGLVer20( )
		{
			ZED_BOOL Ret = ZED_FALSE;

			Ret = ( ( __zglCreateShader =
				( PFNGLCREATESHADERPROC )zglGetProcAddress(
					"glCreateShader" ) ) == ZED_NULL ) || Ret;
			
			Ret = ( ( __zglDeleteShader =
				( PFNGLDELETESHADERPROC )zglGetProcAddress(
					"glDeleteShader" ) ) == ZED_NULL ) || Ret;

			Ret = ( ( __zglShaderSource =
				( PFNGLSHADERSOURCEPROC )zglGetProcAddress( 
					"glShaderSource" ) ) == ZED_NULL ) || Ret;

			Ret = ( ( __zglCompileShader =
				( PFNGLCOMPILESHADERPROC )zglGetProcAddress(
					"glCompileShader" ) ) == ZED_NULL ) || Ret;

			Ret = ( ( __zglGetShaderInfoLog =
				( PFNGLGETSHADERINFOLOGPROC )zglGetProcAddress(
					"glGetShaderInfoLog" ) ) == ZED_NULL ) || Ret;

			Ret = ( ( __zglCreateProgram =
				( PFNGLCREATEPROGRAMPROC )zglGetProcAddress(
					"glCreateProgram" ) ) == ZED_NULL ) || Ret;

			Ret = ( ( __zglAttachShader =
				( PFNGLATTACHSHADERPROC )zglGetProcAddress(
					"glAttachShader" ) ) == ZED_NULL ) || Ret;

			Ret = ( ( __zglDetachShader =
				( PFNGLDETACHSHADERPROC )zglGetProcAddress(
					"glDetachShader" ) ) == ZED_NULL ) || Ret;

			Ret = ( ( __zglIsShader =
				( PFNGLISSHADERPROC )zglGetProcAddress(
					"glIsShader" ) ) == ZED_NULL ) || Ret;

			Ret = ( ( __zglGetShaderiv =
				( PFNGLGETSHADERIVPROC )zglGetProcAddress(
					"glGetShaderiv" ) ) == ZED_NULL ) || Ret;

			Ret = ( ( __zglLinkProgram =
				( PFNGLLINKPROGRAMPROC )zglGetProcAddress(
					"glLinkProgram" ) ) == ZED_NULL ) || Ret;

			Ret = ( ( __zglGetProgramInfoLog =
				( PFNGLGETPROGRAMINFOLOGPROC )zglGetProcAddress(
					"glGetProgramInfoLog" ) ) == ZED_NULL ) || Ret;

			Ret = ( ( __zglUseProgram =
				( PFNGLUSEPROGRAMPROC )zglGetProcAddress(
					"glUseProgram" ) ) == ZED_NULL ) || Ret;

			Ret = ( ( __zglDeleteProgram =
				( PFNGLDELETEPROGRAMPROC )zglGetProcAddress(
					"glDeleteProgram" ) ) == ZED_NULL ) || Ret;

			Ret = ( ( __zglIsProgram =
				( PFNGLISPROGRAMPROC )zglGetProcAddress(
					"glIsProgram" ) ) == ZED_NULL ) || Ret;
			
			Ret = ( ( __zglValidateProgram =
				( PFNGLVALIDATEPROGRAMPROC )zglGetProcAddress(
					"glValidateProgram" ) ) == ZED_NULL ) || Ret;
			
			Ret = ( ( __zglGetProgramiv =
				( PFNGLGETPROGRAMIVPROC )zglGetProcAddress(
					"glGetProgramiv" ) ) == ZED_NULL ) || Ret;

			Ret = ( ( __zglGenVertexArrays =
				( PFNGLGENVERTEXARRAYSPROC )zglGetProcAddress(
					"glGenVertexArrays" ) ) == ZED_NULL ) || Ret;

			Ret = ( ( __zglBindVertexArray =
				( PFNGLBINDVERTEXARRAYPROC )zglGetProcAddress(
					"glBindVertexArray" ) ) == ZED_NULL ) || Ret;

			Ret = ( ( __zglDeleteVertexArrays =
				( PFNGLDELETEVERTEXARRAYSPROC )zglGetProcAddress(
					"glDeleteVertexArrays" ) ) == ZED_NULL ) || Ret;

			Ret = ( ( __zglGenBuffers =
				( PFNGLGENBUFFERSPROC )zglGetProcAddress(
					"glGenBuffers" ) ) == ZED_NULL ) || Ret;

			Ret = ( ( __zglBindBuffer =
				( PFNGLBINDBUFFERPROC )zglGetProcAddress(
					"glBindBuffer" ) ) == ZED_NULL ) || Ret;

			Ret = ( ( __zglBufferData =
				( PFNGLBUFFERDATAPROC )zglGetProcAddress(
					"glBufferData" ) ) == ZED_NULL ) || Ret;

			Ret = ( ( __zglBufferSubData =
				( PFNGLBUFFERSUBDATAPROC )zglGetProcAddress(
					"glBufferSubData" ) ) == ZED_NULL ) || Ret;

			Ret = ( ( __zglDeleteBuffers =
				( PFNGLDELETEBUFFERSPROC )zglGetProcAddress(
					"glDeleteBuffers" ) ) == ZED_NULL ) || Ret;

			Ret = ( ( __zglBindAttribLocation =
				( PFNGLBINDATTRIBLOCATIONPROC )zglGetProcAddress(
					"glBindAttribLocation" ) ) == ZED_NULL ) || Ret;

			Ret = ( ( __zglVertexAttribPointer =
				( PFNGLVERTEXATTRIBPOINTERPROC )zglGetProcAddress(
					"glVertexAttribPointer" ) ) == ZED_NULL ) || Ret;

			Ret = ( ( __zglEnableVertexAttribArray =
				( PFNGLENABLEVERTEXATTRIBARRAYPROC )zglGetProcAddress(
					"glEnableVertexAttribArray" ) ) == ZED_NULL ) || Ret;

			Ret = ( ( __zglGetUniformLocation =
				( PFNGLGETUNIFORMLOCATIONPROC )zglGetProcAddress(
					"glGetUniformLocation" ) ) == ZED_NULL ) || Ret;

			Ret = ( ( __zglUniformMatrix4fv =
				( PFNGLUNIFORMMATRIX4FVPROC )zglGetProcAddress(
					"glUniformMatrix4fv" ) ) == ZED_NULL ) || Ret;

			Ret = ( ( __zglBindFragDataLocation =
				( PFNGLBINDFRAGDATALOCATIONPROC )zglGetProcAddress(
					"glBindFragDataLocation" ) ) == ZED_NULL ) || Ret;

			Ret = ( ( __zglUniform1i =
				( PFNGLUNIFORM1IPROC )zglGetProcAddress(
					"glUniform1i" ) ) == ZED_NULL ) || Ret;

			Ret = ( ( __zglUniform1f =
				( PFNGLUNIFORM1FPROC )zglGetProcAddress(
					"glUniform1f" ) ) == ZED_NULL ) || Ret;

			Ret = ( ( __zglUniform3fv =
				( PFNGLUNIFORM3FVPROC )zglGetProcAddress(
					"glUniform3fv" ) ) == ZED_NULL ) || Ret;

			Ret = ( ( __zglActiveTexture =
				( PFNGLACTIVETEXTUREPROC )zglGetProcAddress(
					"glActiveTexture" ) ) == ZED_NULL ) || Ret;

			Ret = ( ( __zglDeleteTextures =
				( PFNGLDELETETEXTURESEXTPROC )zglGetProcAddress(
					"glDeleteTextures" ) ) == ZED_NULL ) || Ret;

			return ( Ret ? ZED_FAIL : ZED_OK );
		}

		GLExtender::GLExtender( )
		{
		}

		GLExtender::~GLExtender( )
		{
		}

		ZED_BOOL GLExtender::IsSupported( const char *p_pExtension )
		{
			if( m_Extensions.size( ) == 0 )
			{
				zedTrace( "[ZED::Renderer::GLExtender::IsSupported] <ERROR> "
					"Failed to get extensions.\n" );
				zedAssert( ZED_FALSE );

				return ZED_FALSE;
			}

			ZED_BOOL Ret = ZED_FALSE;

			std::list< std::string >::iterator ExtItr = m_Extensions.begin( );
			
			while( ( Ret == ZED_FALSE ) && ( ExtItr != m_Extensions.end( ) ) )
			{
				if( ( *ExtItr ).compare( p_pExtension ) == 0 )
				{
					Ret = ZED_TRUE;
				}

				ExtItr++;
			}

			return Ret;
		}
		
		ZED_BOOL GLExtender::IsWindowExtSupported( const char *p_pWinExt )
		{
			if( m_WindowExtensions.size( ) == 0 )
			{
				zedTrace( "[ZED::Renderer::GLExtender::IsWindowExtSupported "
					"<ERROR> Failed to get extensions\n" );
				zedAssert( ZED_FALSE );
				return ZED_FALSE;
			}
			
			ZED_BOOL Ret = ZED_FALSE;
			std::list< std::string >::iterator Itr =
				m_WindowExtensions.begin( );

			while( ( Ret == ZED_FALSE ) &&
				( Itr != m_WindowExtensions.end( ) ) )
			{
				if( ( *Itr ).compare( p_pWinExt ) == 0 )
				{
					Ret = ZED_TRUE;
				}

				Itr++;				
			}

			return Ret;
		}

		ZED_UINT32 GLExtender::Initialise( const ZED_GLVERSION &p_Version )
		{
			m_GLVersion = p_Version;

			// If the OpenGL version is greater than 3.0, use glGetStringi
			if( m_GLVersion.Major >= 3 )
			{
				// Initialise zglGetStringi
				__zglGetStringi = ( PFNGLGETSTRINGIPROC )zglGetProcAddress(
					"glGetStringi" );
				if( __zglGetStringi == ZED_NULL )
				{
					// Something went wrong!
					zedAssert( ZED_FALSE );
					zedTrace( "[ZED::Renderer::GLExtender::Initialise] "
						"<ERROR> Failed to get zglGetString\n" );
					return ZED_FAIL;
				}
				
				ZED_SINT32 NumExtensions = 0;
				zglGetIntegerv( GL_NUM_EXTENSIONS, &NumExtensions );
				
				zedTrace( "[ZED::Renderer::GLExtender::Initialise] <INFO> "
					"%d OpenGL Extensions supported:\n", NumExtensions );
				// Store all extensions in the extensions list
				for( ZED_MEMSIZE i = 0; i < NumExtensions; i++ )
				{
					std::string GLExt(
						( char* )zglGetStringi( GL_EXTENSIONS, i ) );
					m_Extensions.push_back( GLExt );
					zedTrace( "%s\n", GLExt.c_str( ) );
				}
			}
			// Have to use OGL <=2.x method
			else
			{
				ZED_SINT32 NumExtensions = 0;
				zglGetIntegerv( GL_NUM_EXTENSIONS, &NumExtensions );

				zedTrace( "[ZED::Renderer::GLExtender::Initialise] <INFO> "
					"%d OpenGL Extensions supported:\n", NumExtensions );

				char CurExt[ 64 ] = { '\0' };
				ZED_MEMSIZE Position = 0, CharCount = 0;
				ZED_BOOL Loop = ZED_TRUE;
				const char *pGLExtensions =
					( const char * )glGetString( GL_EXTENSIONS );

				do
				{
					CurExt[ Position++ ] = pGLExtensions[ CharCount ];

					if( pGLExtensions[ CharCount+1 ] == 0x20 )
					{
						std::string CopyString;
						CopyString.insert( 0, CurExt, Position );

						m_Extensions.push_back( CopyString );

						zedTrace( "%s\n", CopyString.c_str( ) );

						Position = 0;

						CharCount++;
					}

					CharCount++;

					if( pGLExtensions[ CharCount ] == 0x00 )
					{
						Loop = ZED_FALSE;
					}

				}while( Loop );
			}

			if( m_GLVersion.Major >= 2 )
			{
				if( zglInitGLVer20( ) != ZED_OK )
				{
					return ZED_GRAPHICS_ERROR;
				}
			}

			return ZED_OK;
		}

		ZED_UINT32 GLExtender::InitialiseWindowExt( Display *p_pDisplay,
			ZED_SINT32 p_Screen )
		{
			// Process the string
			const char *pWinExt = 
				glXQueryExtensionsString( p_pDisplay, p_Screen );

			ZED_UINT32 NumExtensions = 0;

			zedTrace( "[ZED::Renderer::GLExtender::InitialiseWindowExt] "
				"<INFO> Getting GLX Extensions.\n" );

			char CurExt[ 64 ] = { '\0' };
			ZED_MEMSIZE Position = 0, CharCount = 0;
			ZED_BOOL Loop = ZED_TRUE;

			do
			{
				CurExt[ Position++ ] = pWinExt[ CharCount ];

				if( pWinExt[ CharCount+1 ] == 0x20 )
				{
					std::string Copy;
					Copy.insert( 0, CurExt, Position );

					m_WindowExtensions.push_back( Copy );

					zedTrace( "%s\n", Copy.c_str( ) );

					Position = 0;
					NumExtensions++;
					CharCount++;
				}

				CharCount++;

				if( pWinExt[ CharCount ] == 0x00 )
				{
					Loop = ZED_FALSE;
				}
			}while( Loop );

			zedTrace( "[ZED::Renderer::GLExtender::InitialiseWindowExt] "
				"<INFO> %d GLX Extensions available.\n", NumExtensions );

			return ZED_OK;
		}

		ZED_UINT32 GLExtender::RegisterBaseGLExtensions( )
		{
			// Just register the CreateContextAttribsARB
			return ZED_OK;
		}
	}
}

