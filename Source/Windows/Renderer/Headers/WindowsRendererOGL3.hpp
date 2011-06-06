#ifndef __ZEDWINDOWSRENDERER_HPP__
#define __ZEDWINDOWSRENDERER_HPP__

#include <DataTypes.hpp>
#include <GLExtender.hpp>
#include <CanvasDescription.hpp>
#include <Renderer.hpp>
#include <Vector3.hpp>

namespace ZED
{
	namespace Renderer
	{
		class WindowsRendererOGL3 : public Renderer
		{
		public:
			WindowsRendererOGL3( );
			virtual ~WindowsRendererOGL3( );

			virtual ZED_UINT32 Create( GraphicsAdapter *p_pAdapter,
				const CanvasDescription &p_Canvas );

			// Provide an alternative to allow the HDC to be set in Create
			ZED_UINT32 Create( GraphicsAdapter *p_pAdapter,
				const CanvasDescription &p_Canvas, const HDC &p_HDC );

			virtual void ForceClear( const ZED_BOOL p_Colour,
				const ZED_BOOL p_Depth, const ZED_BOOL p_Stencil );
			virtual ZED_UINT32 BeginScene( const ZED_BOOL p_Colour,
				const ZED_BOOL p_Depth, const ZED_BOOL p_Stencil );
			virtual void EndScene( );

			virtual void ClearColour( const ZED_FLOAT32 p_Red,
				const ZED_FLOAT32 p_Green, const ZED_FLOAT32 p_Blue );

			virtual ZED_BOOL ToggleFullscreen( );
			virtual ZED_BOOL ResizeCanvas( const ZED_UINT32 p_Width,
				const ZED_UINT32 p_Height );

			virtual void Release( );

			// Windows-specific functions
			ZED_UINT32 SetHDC( const HDC &p_HDC );
			
			virtual void SetView3D( const Arithmetic::Vector3 &p_Right,
				const Arithmetic::Vector3 &p_Up,
				const Arithmetic::Vector3 &p_Direction,
				const Arithmetic::Vector3 &p_Position );

			virtual void SetViewLookAt(
				const Arithmetic::Vector3 &p_Position,
				const Arithmetic::Vector3 &p_Point, 
				const Arithmetic::Vector3 &p_WorldUp );

			virtual void CalcViewProjMatrix( );
			virtual void CalcWorldViewProjMatrix( );

			virtual void SetClippingPlanes( const ZED_FLOAT32 p_Near,
				const ZED_FLOAT32 p_Far );

			virtual void Prepare2D( );

			virtual ZED_UINT32 CalcPerspProjMatrix(
				const ZED_FLOAT32 p_FOV,
				const ZED_FLOAT32 p_AspectRatio,
				Arithmetic::Matrix4x4 *p_pMatrix );

			virtual ZED_UINT32 SetMode( const ZED_UINT32 p_Stage,
				const ZED_VIEWMODE p_Mode );

			/*virtual ZED_UINT32 InitStage( const ZED_FLOAT32 p_FOV,
				const ZED_VIEWPORT &p_Viewport, ZED_UINT32 p_Stage );

			virtual void GetFrustum( Arithmetic::Plane *p_pFrustum );

			virtual void SetWorldTransform(
				Arithmetic::Matrix4x4 *p_pWorld );

			virtual void Transform2DTo3D( const ZED_POINT &p_Point,
				Arithmetic::Vector3 *p_pOrigin,
				Arithmetic::Vector3 *p_pDirection );
			virtual ZED_POINT Transform2DTo3D(
				const Arithmetic::Vector3 &p_Point );*/

		private:
			PIXELFORMATDESCRIPTOR	m_PixelFormat;
			HGLRC					m_HGLRC;
			HDC						m_HDC;
			GLExtender				m_Ext;
			CanvasDescription		m_Canvas;

			// Near and far clipping planes
			ZED_FLOAT32 m_Near;
			ZED_FLOAT32 m_Far;

			// The view mode to apply
			ZED_VIEWMODE m_ViewMode;

			// Up to four viewports can be rendered
			ZED_VIEWPORT m_Viewport[ 4 ];

			// Which viewport should be rendered
			ZED_UINT32 m_Stage;

			// If the graphics engine winds down, this will be set to false so
			// further sub-systems can clean up
			ZED_BOOL m_Running;
			
			// View matrices
			Arithmetic::Matrix4x4 m_View2D;
			Arithmetic::Matrix4x4 m_View3D;

			// For the different view and projection matrices
			Arithmetic::Matrix4x4 m_ProjectionOrthogonal[ 4 ];
			Arithmetic::Matrix4x4 m_ProjectionPerspective[ 4 ];
			Arithmetic::Matrix4x4 m_World;
			Arithmetic::Matrix4x4 m_ViewScreen;
			Arithmetic::Matrix4x4 m_ProjectionScreen;
			Arithmetic::Matrix4x4 m_ViewProjection;
			Arithmetic::Matrix4x4 m_WorldViewProjection;

			// Framebuffer objects for multiple viewports

		};
	}
}

#endif
