#include <System/WindowsWindow.hpp>
#include <System/Debugger.hpp>

namespace ZED
{
	namespace System
	{
		ZED_UINT32 GetNativeScreenSize( const ZED_UINT32 p_DisplayNumber,
			const ZED_UINT32 p_ScreenNumber, ZED_SCREENSIZE &p_ScreenSize )
		{
			return ZED_OK;
		}

		ZED_UINT32 GetDisplayCount( ZED_UINT32 *p_pDisplayCount )
		{
			DISPLAY_DEVICE Display;
			memset( &Display, 0, sizeof( Display ) );
			Display.cb = sizeof( Display );
			ZED_UINT32 DeviceNum = 0;
			while( EnumDisplayDevices( NULL, DeviceNum, &Display, 0 ) )
			{
				++DeviceNum;
			}

			( *p_pDisplayCount ) = DeviceNum;

			return ZED_OK;
		}

		ZED_UINT32 GetScreenCount( const ZED_UINT32 p_DisplayNumber,
			ZED_UINT32 *p_pScreenCount )
		{
			ZED_UINT32 ScreenCount = 0;
			TCHAR DisplayName[ 32 ];
			DISPLAY_DEVICE Display;
			memset( &Display, 0, sizeof( Display ) );
			Display.cb = sizeof( Display );
			memset( DisplayName, '\0', sizeof( DisplayName ) );

			// Get the display name to use for enumerating the screen count
			if( !EnumDisplayDevices( NULL, p_DisplayNumber, &Display, 0 ) )
			{
				zedTrace( "[ZED::System::GetScreenCount] <ERROR> "
					"Failed to enumerate the display\n" );
				return ZED_FAIL;
			}

			memcpy( DisplayName, Display.DeviceName,
				sizeof( Display.DeviceName ) );

			// Now get the amount of screens
			while( EnumDisplayDevices( DisplayName, ScreenCount, &Display,
				0 ) )
			{
				++ScreenCount;
			}

			( *p_pScreenCount ) = ScreenCount;

			return ZED_OK;
		}
	}
}

