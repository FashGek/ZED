#ifndef __ZED_SYSTEM_INPUT_KEYBOARD_HPP__
#define __ZED_SYSTEM_INPUT_KEYBOARD_HPP__

#include <InputDevice.hpp>

namespace ZED
{
	namespace System
	{
		class Keyboard : public InputDevice
		{
		public:
			Keyboard( );
			virtual ~Keyboard( ) { }

			virtual int State( void *p_pState );

			virtual ZED_INLINE ZED_INPUT_DEVICE_TYPE Type( )
			{
				return ZED_INPUT_DEVICE_KEYBOARD;
			}

		private:
			char m_Keys[ 256 ];
		};
	}
}

#endif

