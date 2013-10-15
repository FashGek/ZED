#ifndef __ZED_RENDERER_CAMERA_HPP__
#define __ZED_RENDERER_CAMERA_HPP__

#include <Renderer/Renderer.hpp>

namespace ZED
{
	namespace Arithmetic
	{
		// Forward declarations
		class Vector3;
		class Plane;
		class Quaternion;
	}
	namespace Renderer
	{
		class Camera
		{
		public:
			void Position( const ZED::Arithmetic::Vector3 &p_Position );
			void Direction(
				const ZED::Arithmetic::Quaternion &p_Direction );

			ZED_INLINE void Position(
				ZED::Arithmetic::Vector3 *p_pPosition ) const
				{ ( *p_pPosition ) = m_Position; }
			ZED::Arithmetic::Vector3 Direction( ) const
				{ return m_Direction; }

			void ClippingPlanes( const ZED_FLOAT32 p_Near,
				const ZED_FLOAT32 p_Far );

			void ViewMode( const ZED_VIEWMODE p_Mode );
			ZED_VIEWMODE ViewMode( ) const;

			// p_pFrustum must be an array of six planes
			void Frustum( Arithmetic::Plane *p_pFrustum );
			void RenderFrustum( ) const;

			void View3D(
				const Arithmetic::Vector3 &p_Right,
				const Arithmetic::Vector3 &p_Up,
				const Arithmetic::Vector3 &p_Direction,
				const Arithmetic::Vector3 &p_Position );

			void ViewLookAt(
				const Arithmetic::Vector3 &p_Position,
				const Arithmetic::Vector3 &p_Point,
				const Arithmetic::Vector3 &p_WorldUp );

			ZED_BOOL Active( ) const { return m_Active; }
			void Activate( ) { m_Active = ZED_TRUE; }
			void Deactivate( ) { m_Active = ZED_FALSE; }

		protected:
			ZED::Arithmetic::Vector3 m_Position;
			ZED::Arithmetic::Vector3 m_Direction;

			// View can be in 2D (screen-space) or in 3D (camera space)
			Arithmetic::Matrix4x4 m_View;
			// Projection can be perspective or orthogonal
			Arithmetic::Matrix4x4 m_Projection;
			Arithmetic::Matrix4x4 m_ViewProjection;
			
			ZED_BOOL		m_Active;
			ZED_VIEWMODE	m_Mode;

			// Clip plane limits
			ZED_FLOAT32		m_Near;
			ZED_FLOAT32		m_Far;
		};
	}
}

#endif
