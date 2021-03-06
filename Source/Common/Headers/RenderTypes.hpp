#ifndef __ZED_RENDERER_RENDERTYPES_HPP__
#define __ZED_RENDERER_RENDERTYPES_HPP__

#include <DataTypes.hpp>

// Include patform-specific headers
#if ( ZED_PLATFORM_WINDOWS )
	#include <RenderTypes_Windows_x86.hpp>
#elif ZED_PLATFORM_XBOX
	#include <xtl.h>
	#include <RenderTypes_Xbox.hpp>
#elif ( ZED_PLATFORM_LINUX )
	#include <RenderTypes_Linux_x86.hpp>
#endif

// -- CONSTANTS --
const ZED_MEMSIZE ZED_ENABLE = 1;
const ZED_MEMSIZE ZED_DISABLE = 0;

// Define the texture file types
const ZED_UINT32	ZED_PNG = 0x00000001;
const ZED_UINT32	ZED_DDS = 0x00000002;
const ZED_UINT32	ZED_BMP = 0x00000004;
const ZED_UINT32	ZED_TGA = 0x00000008;

// -- ENUMS --
// How should the world be rendered?
typedef enum _ZED_VIEWMODE
{
	// View with Z
	ZED_VIEW_PERSPECTIVE,
	// View without Z
	ZED_VIEW_ORTHOGONAL,
	// View aligned to screen coordinates
	ZED_VIEW_SCREEN
}ZED_VIEWMODE;

// The ZED_RENDERSTATEs are used for setting the various graphics functions
// on the GPU
typedef enum __ZED_RENDERSTATE
{
	ZED_RS_DEPTH,
	ZED_RS_FILLMODE,
	ZED_RS_CULLMODE,
	ZED_RS_PADDING	= ZED_ENUM_PAD,
}ZED_RENDERSTATE;

// Fill mode is only applicable to fixed function pipeline GPUs
typedef enum __ZED_FILLMODE
{
	ZEDFILL_WIREFRAME,
	ZEDFILL_SOLID,
	ZEDFILL_POINT,
	ZEDFILL_PADDING = ZED_ENUM_PAD,
}ZED_FULLMODE;

// Culling is CCW by default
typedef enum __ZED_CULLMODE
{	
	ZEDCULL_NONE,
	ZEDCULL_CCW,
	ZEDCULL_CW,
	ZEDCULL_PADDING = ZED_ENUM_PAD,
}ZED_CULLMODE;

// -- STRUCTS --
// Used for colour data
typedef struct _ZED_COLOUR
{
	ZED_FLOAT32 Red;
	ZED_FLOAT32 Green;
	ZED_FLOAT32 Blue;
	ZED_FLOAT32 Alpha;
} ZED_COLOUR;

// Viewport stucture for rendering different views within a Canvas
// Note:	Rendering to different render targets/textures would be more
//			ideal for newer hardware (nVIDIA GF3> && ATi R7500>)
//			[Performance levels can be queried at runtime]
typedef struct _ZED_VIEWPORT
{
	// Upper-left corner
	ZED_UINT32 X;
	ZED_UINT32 Y;

	ZED_UINT32 Width;
	ZED_UINT32 Height;
}ZED_VIEWPORT;

// Screen-space points
typedef struct _ZED_POINT
{
	ZED_UINT32 X;
	ZED_UINT32 Y;
}ZED_POINT;

// Used to specify shader uniform variables
// N.B.
//	pName should always be ZED_NULL on Xbox, as it isn't required.
typedef struct __ZED_SHADER_UNIFORM_MAP
{
	// Index for the user to use for identifying where the input is
	// logically
	ZED_UINT32			Index;
	// The /real/ location of the input
	ZED_UINT32			Location;
	// The type of input, i.e. ZED_VEC[1|2|3|4]
	ZED_SHADER_UNIFORM_TYPE Type;
	// Name is used for OpenGL shaders
	ZED_CHAR8	*pName;
}ZED_SHADER_UNIFORM_MAP;

typedef struct __ZED_SHADER_ATTRIBUTE_MAP
{
	char			*pName;
	ZED_UINT32		Index;
	ZED_SHADER_TYPE Type;
}ZED_SHADER_ATTRIBUTE_MAP;

typedef struct __ZED_GLVERSION
{
	ZED_SINT32	Major;
	ZED_SINT32	Minor;
}ZED_GLVERSION;

#endif

