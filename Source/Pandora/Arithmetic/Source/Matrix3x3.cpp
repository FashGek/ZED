#include <Matrix3x3.hpp>
#include <Quaternion.hpp>

namespace ZED
{
	namespace Arithmetic
	{
		Matrix3x3::Matrix3x3( const Quaternion &p_Quaternion )
		{
			this->Rotate( p_Quaternion );
		}

		void Matrix3x3::Identity( )
		{
			m_M[ 0 ] = m_M[ 4 ] = m_M[ 8 ] = 1.0f;
			m_M[ 1 ] = m_M[ 2 ] = m_M[ 3 ] = m_M[ 5 ] = m_M[ 6 ] = m_M[ 7 ] =
				0.0f;
		}

		Matrix3x3 &Matrix3x3::Rotate( const Quaternion &p_Q )
		{
			m_M[ 0 ] = 1.0f - ( 2*( p_Q[ 1 ]*p_Q[ 1 ] ) ) -
				( 2*( p_Q[ 2 ]*p_Q[ 2 ] ) );
			m_M[ 1 ] = ( 2* p_Q[ 0 ]*p_Q[ 1 ] ) + ( 2*p_Q[ 3 ]*p_Q[ 2 ] );
			m_M[ 2 ] = 2*( p_Q[ 0 ]*p_Q[ 2 ] ) - 2*( p_Q[ 3 ]*p_Q[ 1 ] );

			m_M[ 3 ] = 2*( p_Q[ 0 ]*p_Q[ 1 ] ) - 2*( p_Q[ 3 ]*p_Q[ 2 ] );
			m_M[ 4 ] = 1-( 2*( p_Q[ 0 ]*p_Q[ 0 ] ) ) -
				( 2*( p_Q[ 3 ]*p_Q[ 3 ] ) );
			m_M[ 5 ] = 2*p_Q[ 1 ]*p_Q[ 2 ] + 2*p_Q[ 3 ]*p_Q[ 0 ];

			m_M[ 6 ] = 2*( p_Q[ 0 ]*p_Q[ 2 ] ) + 2*( p_Q[ 3 ]*p_Q[ 1 ] );
			m_M[ 7 ] = 2*( p_Q[ 1 ]*p_Q[ 2 ] ) - 2*( p_Q[ 3 ]*p_Q[ 0 ] );
			m_M[ 8 ] = 1 - ( 2*( p_Q[ 0 ]*p_Q[ 0 ] ) ) -
				( 2*( p_Q[ 1 ]*p_Q[ 1 ] ) );

			return *this;
		}

		Matrix3x3 &Matrix3x3::Rotate( const ZED_FLOAT32 p_Angle,
			const Vector3 &p_Axis )
		{
			ZED_FLOAT32 Cos = 0.0f, Sin = 0.0f;
			
			Arithmetic::SinCos( p_Angle, Sin, Cos );

			ZED_FLOAT32 Tan = ( 1.0f - Cos );

			m_M[ 0 ] = ( Tan*( p_Axis[ 0 ]*p_Axis[ 0 ] ) ) + Cos;
			m_M[ 1 ] = ( Tan*p_Axis[ 0 ]*p_Axis[ 1 ] ) + ( Sin*p_Axis[ 2 ] );
			m_M[ 2 ] = ( Tan*p_Axis[ 0 ]*p_Axis[ 2 ] ) + ( Sin*p_Axis[ 1 ] );

			m_M[ 3 ] = ( Tan*p_Axis[ 0 ]*p_Axis[ 1 ] ) - ( Sin*p_Axis[ 2 ] );
			m_M[ 4 ] = ( Tan*( p_Axis[ 1 ]*p_Axis[ 1 ] ) ) + Cos;
			m_M[ 5 ] = ( Tan*p_Axis[ 1 ]*p_Axis[ 2 ] ) + ( Sin*p_Axis[ 0 ] );

			m_M[ 6 ] = ( Tan*p_Axis[ 0 ]*p_Axis[ 1 ] ) + ( Sin*p_Axis[ 1 ] );
			m_M[ 7 ] = ( Tan*p_Axis[ 1 ]*p_Axis[ 2 ] ) - ( Sin*p_Axis[ 0 ] );
			m_M[ 8 ] = ( Tan*( p_Axis[ 2 ]*p_Axis[ 2 ] ) ) + Cos;

			return *this;
		}

		Matrix3x3 &Matrix3x3::Rotate( const ZED_FLOAT32 p_Roll,
			const ZED_FLOAT32 p_Pitch, const ZED_FLOAT32 p_Yaw )
		{
			ZED_FLOAT32 CX = 0.0f, CY = 0.0f, CZ = 0.0f;
			ZED_FLOAT32 SX = 0.0f, SY = 0.0f, SZ = 0.0f;

			Arithmetic::SinCos( p_Pitch, SX, CX );
			Arithmetic::SinCos( p_Yaw, SY, CY );
			Arithmetic::SinCos( p_Roll, SZ, CZ );

			m_M[ 0 ] = CY*CZ;
			m_M[ 1 ] = ( SX*SY*CZ ) + ( CX*SZ );
			m_M[ 2 ] = -( CX*SY*CZ ) + ( SX*SZ );

			m_M[ 3 ] = -( CY*SZ );
			m_M[ 4 ] = -( SX*SY*SZ ) + ( CX*CZ );
			m_M[ 5 ] = ( CZ*SY*SZ ) + ( SX*CZ );

			m_M[ 6 ] = SY;
			m_M[ 7 ] = -( SX*CY );
			m_M[ 8 ] = CX*CY;

			return *this;
		}

		Matrix3x3 &Matrix3x3::RotateX( const ZED_FLOAT32 p_X )
		{
			ZED_FLOAT32 Sin = 0.0f, Cos = 0.0f;
			Arithmetic::SinCos( p_X, Sin, Cos );

			m_M[ 0 ] = 1.0f;
			m_M[ 1 ] = Cos;
			m_M[ 2 ] = Sin;

			m_M[ 3 ] = 0.0f;
			m_M[ 4 ] = -Sin;
			m_M[ 5 ] = Cos;

			m_M[ 6 ] = 0.0f;
			m_M[ 7 ] = 0.0f;
			m_M[ 8 ] = 1.0f;

			return *this;
		}

		Matrix3x3 &Matrix3x3::RotateY( const ZED_FLOAT32 p_Y )
		{
			ZED_FLOAT32 Sin = 0.0f, Cos = 0.0f;
			Arithmetic::SinCos( p_Y, Sin, Cos );

			m_M[ 0 ] = Cos;
			m_M[ 1 ] = 0.0f;
			m_M[ 2 ] = -Sin;
			
			m_M[ 3 ] = 0.0f;
			m_M[ 4 ] = 1.0f;
			m_M[ 5 ] = 0.0f;

			m_M[ 6 ] = Sin;
			m_M[ 7 ] = 0.0f;
			m_M[ 8 ] = Cos;

			return *this;
		}

		Matrix3x3 &Matrix3x3::RotateZ( const ZED_FLOAT32 p_Z )
		{
			ZED_FLOAT32 Sin = 0.0f, Cos = 0.0f;
			Arithmetic::SinCos( p_Z, Sin, Cos );

			m_M[ 0 ] = Cos;
			m_M[ 1 ] = Sin;
			m_M[ 2 ] = 0.0f;

			m_M[ 3 ] = -Sin;
			m_M[ 4 ] = Cos;
			m_M[ 5 ] = 0.0f;

			m_M[ 6 ] = 0.0f;
			m_M[ 7 ] = 0.0f;
			m_M[ 8 ] = 1.0f;

			return *this;
		}

		ZED_BOOL Matrix3x3::IsZero( ) const
		{
			for( ZED_MEMSIZE i = 0; i < 9; ++i )
			{
				if( !Arithmetic::IsZero( m_M[ i ] ) )
				{
					return ZED_FALSE;
				}
			}

			return ZED_TRUE;
		}

		ZED_BOOL Matrix3x3::IsIdentity( ) const
		{
			if( Arithmetic::Equal( m_M[ 0 ], 1.0f ) &&
				Arithmetic::IsZero( m_M[ 1 ] ) &&
				Arithmetic::IsZero( m_M[ 2 ] ) &&
				Arithmetic::IsZero( m_M[ 3 ] ) &&
				Arithmetic::Equal( m_M[ 4 ], 1.0f ) &&
				Arithmetic::IsZero( m_M[ 5 ] ) &&
				Arithmetic::IsZero( m_M[ 6 ] ) &&
				Arithmetic::IsZero( m_M[ 7 ] ) &&
				Arithmetic::Equal( m_M[ 8 ], 1.0f ) )
			{
				return ZED_TRUE;
			}

			return ZED_FALSE;
		}

		void Matrix3x3::SetRows( const Vector3 &p_Row1, const Vector3 &p_Row2,
			const Vector3 &p_Row3 )
		{
			m_M[ 0 ] = p_Row1[ 0 ];
			m_M[ 3 ] = p_Row1[ 1 ];
			m_M[ 6 ] = p_Row1[ 2 ];

			m_M[ 1 ] = p_Row2[ 0 ];
			m_M[ 4 ] = p_Row2[ 1 ];
			m_M[ 7 ] = p_Row2[ 2 ];

			m_M[ 2 ] = p_Row3[ 0 ];
			m_M[ 5 ] = p_Row3[ 1 ];
			m_M[ 8 ] = p_Row3[ 2 ];
		}

		void Matrix3x3::GetRows( Vector3 &p_Row1, Vector3 &p_Row2,
			Vector3 &p_Row3 ) const
		{
			p_Row1[ 0 ] = m_M[ 0 ];
			p_Row1[ 1 ] = m_M[ 3 ];
			p_Row1[ 2 ] = m_M[ 6 ];

			p_Row2[ 0 ] = m_M[ 1 ];
			p_Row2[ 1 ] = m_M[ 4 ];
			p_Row2[ 2 ] = m_M[ 7 ];

			p_Row3[ 0 ] = m_M[ 2 ];
			p_Row3[ 1 ] = m_M[ 5 ];
			p_Row3[ 2 ] = m_M[ 8 ];
		}

		Vector3 Matrix3x3::GetRow( const ZED_MEMSIZE p_Index ) const
		{
			// No index range checking!
			return Vector3( m_M[ 0+p_Index ],
							m_M[ 3+p_Index ],
							m_M[ 6+p_Index ] );
		}

		void Matrix3x3::SetColumns( const Vector3 &p_Column1,
			const Vector3 &p_Column2, const Vector3 &p_Column3 )
		{
			m_M[ 0 ] = p_Column1[ 0 ];
			m_M[ 1 ] = p_Column1[ 1 ];
			m_M[ 2 ] = p_Column1[ 2 ];

			m_M[ 3 ] = p_Column2[ 0 ];
			m_M[ 4 ] = p_Column2[ 1 ];
			m_M[ 5 ] = p_Column2[ 2 ];

			m_M[ 6 ] = p_Column3[ 0 ];
			m_M[ 7 ] = p_Column3[ 1 ];
			m_M[ 8 ] = p_Column3[ 2 ];
		}

		void Matrix3x3::GetColumns( Vector3 &p_Column1, Vector3 &p_Column2,
			Vector3 &p_Column3 ) const
		{
			p_Column1[ 0 ] = m_M[ 0 ];
			p_Column1[ 1 ] = m_M[ 1 ];
			p_Column1[ 2 ] = m_M[ 2 ];

			p_Column2[ 0 ] = m_M[ 3 ];
			p_Column2[ 1 ] = m_M[ 4 ];
			p_Column2[ 2 ] = m_M[ 5 ];
			
			p_Column3[ 0 ] = m_M[ 6 ];
			p_Column3[ 1 ] = m_M[ 7 ];
			p_Column3[ 2 ] = m_M[ 8 ];
		}

		Vector3 Matrix3x3::GetColumn( const ZED_MEMSIZE p_Index ) const
		{
			// No checking of the index's range!
			ZED_MEMSIZE Offset = p_Index*3;

			return Vector3( m_M[ 0+Offset ],
							m_M[ 1+Offset ],
							m_M[ 2*Offset ] );
		}

		void Matrix3x3::Clean( )
		{
			for( ZED_MEMSIZE i = 0; i < 9; ++i )
			{
				if( Arithmetic::IsZero( m_M[ i ] ) )
				{
					m_M[ i ] = 0.0f;
				}
			}
		}

		Matrix3x3 &Matrix3x3::Transpose( )
		{
			// 0 3 6
			// 1 4 7
			// 2 5 8
			// -----
			// 0 1 2
			// 3 4 5
			// 6 7 8

			ZED_FLOAT32 Tmp = m_M[ 1 ];
			m_M[ 1 ] = m_M[ 3 ];
			m_M[ 3 ] = Tmp;

			Tmp = m_M[ 2 ];
			m_M[ 2 ] = m_M[ 6 ];
			m_M[ 6 ] = Tmp;

			Tmp = m_M[ 5 ];
			m_M[ 5 ] = m_M[ 7 ];
			m_M[ 7 ] = Tmp;

			return *this;
		}

		void Matrix3x3::Transpose( Matrix3x3 &p_Matrix ) const
		{
			p_Matrix.m_M[ 0 ] = m_M[ 0 ];
			p_Matrix.m_M[ 4 ] = m_M[ 4 ];
			p_Matrix.m_M[ 8 ] = m_M[ 8 ];

			p_Matrix.m_M[ 1 ] = m_M[ 3 ];
			p_Matrix.m_M[ 2 ] = m_M[ 6 ];
			p_Matrix.m_M[ 3 ] = m_M[ 1 ];
			p_Matrix.m_M[ 5 ] = m_M[ 7 ];
			p_Matrix.m_M[ 6 ] = m_M[ 2 ];
			p_Matrix.m_M[ 7 ] = m_M[ 5 ];
		}

		Matrix3x3 &Matrix3x3::TransposeOf( const Matrix3x3 &p_Transpose )
		{
			p_Transpose.Transpose( *this );

			return *this;
		}

		Matrix3x3 &Matrix3x3::Inverse( )
		{
			ZED_FLOAT32 Det = this->Determinate( );

			if( Arithmetic::IsZero( Det ) )
			{
				zedTrace( "[ZED::Arithmetic::Matrix3x3::Inverse] "
					"<WARN> Matrix is singular!  No inverse computed.\n" );
				return *this;
			}

			// Save on the divisions later
			ZED_FLOAT32 Factor = 1.0f/Det;

			*this = this->Adjoint( );
			
			m_M[ 0 ] *= Factor;
			m_M[ 1 ] *= Factor;
			m_M[ 2 ] *= Factor;
			m_M[ 3 ] *= Factor;
			m_M[ 4 ] *= Factor;
			m_M[ 5 ] *= Factor;
			m_M[ 6 ] *= Factor;
			m_M[ 7 ] *= Factor;
			m_M[ 8 ] *= Factor;

			return *this;
		}

		void Matrix3x3::Inverse( Matrix3x3 &p_Matrix ) const
		{
			ZED_FLOAT32 Det = p_Matrix.Determinate( );

			if( Arithmetic::IsZero( Det ) )
			{
				zedTrace( "[ZED::Aritmetic::Matrix3x3::Inverse] <WARN> "
					"Matrix is singular!  No inverse computed." );
				return;
			}

			ZED_FLOAT32 Factor = 1.0f/Det;

			p_Matrix.Adjoint( );

			p_Matrix.m_M[ 0 ] *= Factor;
			p_Matrix.m_M[ 1 ] *= Factor;
			p_Matrix.m_M[ 2 ] *= Factor;
			p_Matrix.m_M[ 3 ] *= Factor;
			p_Matrix.m_M[ 4 ] *= Factor;
			p_Matrix.m_M[ 5 ] *= Factor;
			p_Matrix.m_M[ 6 ] *= Factor;
			p_Matrix.m_M[ 7 ] *= Factor;
			p_Matrix.m_M[ 8 ] *= Factor;
		}

		Matrix3x3 &Matrix3x3::InverseOf( const Matrix3x3 &p_Inverse )
		{
			p_Inverse.Inverse( *this );
			return *this;
		}

		Matrix3x3 Matrix3x3::Adjoint( ) const
		{
			Matrix3x3 Adjoint;
			
			// Just to speed things up, already invert the matrix's cofactors
			Adjoint.m_M[ 0 ] = ( m_M[ 4 ]*m_M[ 8 ] - m_M[ 7 ]*m_M[ 5 ] );
			Adjoint.m_M[ 1 ] = ( m_M[ 2 ]*m_M[ 7 ] - m_M[ 1 ]*m_M[ 8 ] );
			Adjoint.m_M[ 2 ] = ( m_M[ 1 ]*m_M[ 5 ] - m_M[ 2 ]*m_M[ 4 ] );

			Adjoint.m_M[ 3 ] = ( m_M[ 5 ]*m_M[ 6 ] - m_M[ 3 ]*m_M[ 8 ] );
			Adjoint.m_M[ 4 ] = ( m_M[ 0 ]*m_M[ 8 ] - m_M[ 2 ]*m_M[ 6 ] );
			Adjoint.m_M[ 5 ] = ( m_M[ 0 ]*m_M[ 5 ] - m_M[ 3 ]*m_M[ 2 ] );

			Adjoint.m_M[ 6 ] = ( m_M[ 3 ]*m_M[ 7 ] - m_M[ 6 ]*m_M[ 4 ] );
			Adjoint.m_M[ 7 ] = ( m_M[ 0 ]*m_M[ 7 ] - m_M[ 6 ]*m_M[ 1 ] );
			Adjoint.m_M[ 8 ] = ( m_M[ 0 ]*m_M[ 4 ] - m_M[ 3 ]*m_M[ 1 ] );

			return Adjoint;
		}

		ZED_FLOAT32 Matrix3x3::Determinate( ) const
		{
			ZED_FLOAT32 Determinate = 0.0f;

			Determinate = m_M[ 0 ]*( ( m_M[ 4 ]*m_M[ 8 ] ) -
									 ( m_M[ 5 ]*m_M[ 7 ] ) ) +
						  m_M[ 3 ]*( ( m_M[ 1 ]*m_M[ 8 ] ) -
						  			 ( m_M[ 7 ]*m_M[ 2 ] ) ) +
						  m_M[ 6 ]*( ( m_M[ 1 ]*m_M[ 5 ] ) -
						  			 ( m_M[ 4 ]*m_M[ 2 ] ) );

			return Determinate;
		}

		ZED_FLOAT32 Matrix3x3::Trace( ) const
		{
			return ( m_M[ 0 ] + m_M[ 4 ] + m_M[ 8 ] );
		}
	}
}
