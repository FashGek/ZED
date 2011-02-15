#ifndef __ZEDLINUXRENDERTYPES_HPP__
#define __ZEDLINUXRENDERTYPES_HPP__

// Format types for the different buffers, etc.
typedef enum _ZED_FORMAT
{
	// Hope to hell that nothing takes this (other than more undefined formats)
	ZED_FORMAT_UNDEFINED = 0xFFFFFFFF,

	// Colour
	ZED_FORMAT_A8R8G8B8 =	0x00000001,
	ZED_FORMAT_X8R8G8B8 =	0x00000002,

	// Depth/Stencil
	ZED_FORMAT_D24S8 =		0x0000000F,
} ZED_FORMAT;

#endif
