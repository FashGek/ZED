#include <Matrix3x3.hpp>

namespace ZED
{
	namespace Arithmetic
	{
		Matrix3x3 &Matrix3x3::Clone( ) const
		{
			Matrix3x3 *pClone = new Matrix3x3( );
			pClone->Copy( *this );
			return *pClone;
		}

		void Matrix3x3::Copy( const Matrix3x3 &p_Copy )
		{
			m_M[ 0 ] = p_Copy[ 0 ];
			m_M[ 1 ] = p_Copy[ 1 ];
			m_M[ 2 ] = p_Copy[ 2 ];
			m_M[ 3 ] = p_Copy[ 3 ];
			m_M[ 4 ] = p_Copy[ 4 ];
			m_M[ 5 ] = p_Copy[ 5 ];
			m_M[ 6 ] = p_Copy[ 6 ];
			m_M[ 7 ] = p_Copy[ 7 ];
			m_M[ 8 ] = p_Copy[ 8 ];
		}

		void Matrix3x3::Identity( )
		{
			m_M[ 0 ] = m_M[ 4 ] = m_M[ 8 ] = 1.0f;

			// Cause cache issues by not assigning contiguously?
			m_M[ 1 ] = m_M[ 2 ] = m_M[ 3 ] = m_M[ 5 ] = m_M[ 6 ] = m_M[ 7 ] =
				0.0f;
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
			m_M[ 8 ] = ( Tan* ( p_Axis[ 2 ]*p_Axis[ 2 ] ) ) + Cos;

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
			m_M[ 5 ] = ( CX*SY*SZ ) + ( SX*CZ );

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

			m_M[ 4 ] = Cos;
			m_M[ 5 ] = Sin;

			m_M[ 7 ] = -Sin;
			m_M[ 8 ] = Cos;

			m_M[ 1 ] = m_M[ 2 ] = m_M[ 3 ] = m_M[ 6 ] = 0.0f;

			return *this;
		}

		Matrix3x3 &Matrix3x3::RotateY( const ZED_FLOAT32 p_Y )
		{
			ZED_FLOAT32 Sin = 0.0f, Cos = 0.0f;

			Arithmetic::SinCos( p_Y, Sin, Cos );

			m_M[ 0 ] = Cos;
			m_M[ 2 ] = -Sin;

			m_M[ 4 ] = 1.0f;

			m_M[ 6 ] = Sin;
			m_M[ 8 ] = Cos;

			m_M[ 1 ] = m_M[ 3 ] = m_M[ 5 ] = m_M[ 7 ] = 0.0f;

			return *this;
		}

		Matrix3x3 &Matrix3x3::RotateZ( const ZED_FLOAT32 p_Z )
		{
			ZED_FLOAT32 Sin = 0.0f, Cos = 0.0f;

			Arithmetic::SinCos( p_Z, Sin, Cos );

			m_M[ 0 ] = Cos;
			m_M[ 1 ] = Sin;

			m_M[ 3 ] = -Sin;
			m_M[ 4 ] = Cos;

			m_M[ 8 ] = 1.0f;

			m_M[ 2 ] = m_M[ 5 ] = m_M[ 6 ] = m_M[ 7 ] = 0.0f;

			return *this;
		}

		Matrix3x3 &Matrix3x3::Scale( const ZED_FLOAT32 p_Value )
		{
			m_M[ 0 ] = m_M[ 4 ] = m_M[ 8 ] =  p_Value;
			m_M[ 1 ] = m_M[ 2 ] = m_M[ 3 ] = m_M[ 5 ] = m_M[ 6 ] = m_M[ 7 ] =
				0.0f;
			
			return *this;
		}

		Matrix3x3 &Matrix3x3::Scale( const Vector3 &p_Scale )
		{
			m_M[ 0 ] = p_Scale[ 0 ];
			m_M[ 4 ] = p_Scale[ 1 ];
			m_M[ 8 ] = p_Scale[ 2 ];

			m_M[ 1 ] = m_M[ 2 ] = m_M[ 3 ] = m_M[ 5 ] = m_M[ 6 ] = m_M[ 7 ] =
				0.0f;

			return *this;
		}

		Matrix3x3 &Matrix3x3::ScaleX( const ZED_FLOAT32 p_X )
		{
			m_M[ 0 ] = p_X;

			m_M[ 1 ] = m_M[ 2 ] = m_M[ 3 ] = m_M[ 5 ] = m_M[ 6 ] =
				m_M[ 7 ] = 0.0f;

			return *this;
		}

		Matrix3x3 &Matrix3x3::ScaleY( const ZED_FLOAT32 p_Y )
		{
			m_M[ 4 ] = p_Y;

			m_M[ 1 ] = m_M[ 2 ] = m_M[ 3 ] = m_M[ 5 ] = m_M[ 6 ] = m_M[ 7 ] =
				0.0f;

			return *this;
		}

		Matrix3x3 &Matrix3x3::ScaleZ( const ZED_FLOAT32 p_Z )
		{
			m_M[ 8 ] = p_Z;

			m_M[ 1 ] = m_M[ 2 ] = m_M[ 3 ] = m_M[ 5 ] = m_M[ 6 ] = m_M[ 7 ] =
				0.0f;

			return *this;
		}

		ZED_BOOL Matrix3x3::IsZero( ) const
		{
			for( ZED_MEMSIZE i = 0; i < 9; i++ )
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
				Arithmetic::Equal( m_M[ 1 ], 0.0f ) &&
				Arithmetic::Equal( m_M[ 2 ], 0.0f ) &&
				Arithmetic::Equal( m_M[ 3 ], 0.0f ) &&
				Arithmetic::Equal( m_M[ 4 ], 1.0f ) &&
				Arithmetic::Equal( m_M[ 5 ], 0.0f ) &&
				Arithmetic::Equal( m_M[ 6 ], 0.0f ) &&
				Arithmetic::Equal( m_M[ 7 ], 0.0f ) &&
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

		Vector3 Matrix3x3::GetRow( const ZED_UINT32 p_Index ) const
		{
			return Vector3( m_M[ p_Index ], m_M[ p_Index+3 ],
				m_M[ p_Index+6 ] );
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

		Vector3 Matrix3x3::GetColumn( const ZED_UINT32 p_Index ) const
		{
			return Vector3( m_M[ p_Index*3 ], m_M[ ( p_Index*3 )+1 ],
				m_M[ ( p_Index*3 )+2 ] );
		}

		void Matrix3x3::Clean( )
		{
			for( ZED_MEMSIZE i = 0; i < 9; i++ )
			{
				if( Arithmetic::IsZero( m_M[ i ] ) )
				{
					m_M[ i ] = 0.0f;
				}
			}
		}

		Matrix3x3 &Matrix3x3::Transpose( )
		{
			ZED_FLOAT32 Temp = m_M[ 1 ];
			m_M[ 1 ] = m_M[ 3 ];
			m_M[ 3 ] = Temp;

			Temp = m_M[ 2 ];
			m_M[ 2 ] = m_M[ 6 ];
			m_M[ 6 ] = Temp;

			Temp = m_M[ 5 ];
			m_M[ 5 ] = m_M[ 7 ];
			m_M[ 7 ] = Temp;

			return *this;
		}

		void Matrix3x3::Transpose( Matrix3x3 &p_Matrix ) const
		{
			p_Matrix[ 0 ] = m_M[ 0 ];
			p_Matrix[ 4 ] = m_M[ 4 ];
			p_Matrix[ 8 ] = m_M[ 8 ];

			p_Matrix[ 1 ] = m_M[ 3 ];
			p_Matrix[ 3 ] = m_M[ 1 ];

			p_Matrix[ 2 ] = m_M[ 6 ];
			p_Matrix[ 6 ] = m_M[ 2 ];

			p_Matrix[ 5 ] = m_M[ 7 ];
			p_Matrix[ 7 ] = m_M[ 7 ];
		}

		Matrix3x3 &Matrix3x3::TransposeOf( const Matrix3x3 &p_Transpose )
		{
			p_Transpose.Transpose( *this );

			return *this;
		}

		Matrix3x3 &Matrix3x3::Inverse( )
		{
			ZED_FLOAT32 Det = Determinate( );

			if( Arithmetic::IsZero( Det ) )
			{
				zedTrace( "[ZED:Arithmetic:Matrix3x3:Inverse] <WARN> "
					"Matrix is singular!  No inverse computed.\n" );
				return *this;
			}

			// Save on divisions!
			ZED_FLOAT32 Factor = 1.0f/Det;

			*this = Adjoint( );

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
			ZED_FLOAT32 Det = Determinate( );

			if( Arithmetic::IsZero( Det ) )
			{
				zedTrace( "[ZED:Arithmetic:Matrix3x3:Inverse] <WARN> "
					"Matrix is singular!  No inverse computed.\n" );
				return;
			}

			// Put the divisions back in the deck!
			ZED_FLOAT32 Factor = 1.0f/Det;

			p_Matrix = Adjoint( );
			
			p_Matrix[ 0 ] *= Factor;
			p_Matrix[ 1 ] *= Factor;
			p_Matrix[ 2 ] *= Factor;
			p_Matrix[ 3 ] *= Factor;
			p_Matrix[ 4 ] *= Factor;
			p_Matrix[ 5 ] *= Factor;
			p_Matrix[ 6 ] *= Factor;
			p_Matrix[ 7 ] *= Factor;
			p_Matrix[ 8 ] *= Factor;
		}

		Matrix3x3 &Matrix3x3::InverseOf( const Matrix3x3 &p_Inverse )
		{
			p_Inverse.Inverse( *this );
			return *this;
		}

		Matrix3x3 Matrix3x3::Adjoint( ) const
		{
			Matrix3x3 Adjoint;

			// Get the transposed co-efficients
			Adjoint[ 0 ] = ( m_M[ 4 ]*m_M[ 8 ] ) - ( m_M[ 7 ]*m_M[ 5 ] );
			Adjoint[ 1 ] = ( m_M[ 2 ]*m_M[ 7 ] ) - ( m_M[ 1 ]*m_M[ 8 ] );
			Adjoint[ 2 ] = ( m_M[ 1 ]*m_M[ 5 ] ) - ( m_M[ 2 ]*m_M[ 4 ] );

			Adjoint[ 3 ] = ( m_M[ 5 ]*m_M[ 6 ] ) - ( m_M[ 3 ]*m_M[ 8 ] );
			Adjoint[ 4 ] = ( m_M[ 0 ]*m_M[ 8 ] ) - ( m_M[ 2 ]*m_M[ 6 ] );
			Adjoint[ 5 ] = ( m_M[ 0 ]*m_M[ 5 ] ) - ( m_M[ 3 ]*m_M[ 2 ] );

			Adjoint[ 6 ] = ( m_M[ 3 ]*m_M[ 7 ] ) - ( m_M[ 6 ]*m_M[ 4 ] );
			Adjoint[ 7 ] = ( m_M[ 0 ]*m_M[ 7 ] ) - ( m_M[ 6 ]*m_M[ 1 ] );
			Adjoint[ 8 ] = ( m_M[ 0 ]*m_M[ 4 ] ) - ( m_M[ 3 ]*m_M[ 1 ] );

			return Adjoint;
		}

		ZED_FLOAT32 Matrix3x3::Determinate( ) const
		{
			return m_M[ 0 ]*( ( m_M[ 4 ]*m_M[ 8 ] ) -
								( m_M[ 5 ]*m_M[ 7 ] ) ) +
					m_M[ 3 ]*( ( m_M[ 7 ]*m_M[ 2 ] )-
								( m_M[ 1 ]*m_M[ 8 ] ) ) +
					m_M[ 6 ]*( ( m_M[ 1 ]*m_M[ 5 ] ) -
								( m_M[ 2 ]*m_M[ 4 ] ) );
		}

		ZED_FLOAT32 Matrix3x3::Trace( ) const
		{
			return ( m_M[ 0 ] + m_M[ 4 ] + m_M[ 8 ] );
		}

		System::Writer &operator<<( System::Writer &p_Out,
			const Matrix3x3 &p_Source )
		{
			for( ZED_MEMSIZE R = 0; R < 3; R++ )
			{
				p_Out << "| " << p_Source[ R ] << " " << p_Source[ R+3 ] <<
					" " << p_Source[ R+6 ] << " |" << std::endl;
			}
			return p_Out;
		}

		ZED_BOOL Matrix3x3::operator==( const Matrix3x3 &p_Other ) const
		{
			for( ZED_MEMSIZE i = 0; i < 9; i++ )
			{
				if( !Arithmetic::Equal( m_M[ i ], p_Other[ i ] ) )
				{
					return ZED_FALSE;
				}
			}

			return ZED_TRUE;
		}

		ZED_BOOL Matrix3x3::operator!=( const Matrix3x3 &p_Other ) const
		{
			for( ZED_MEMSIZE i = 0; i < 9; i++ )
			{
				if( Arithmetic::Equal( m_M[ i ], p_Other[ i ] ) )
				{
					return ZED_TRUE;
				}
			}

			return ZED_FALSE;
		}

		Matrix3x3 Matrix3x3::operator+( const Matrix3x3 &p_Other ) const
		{
			Matrix3x3 Matrix;

			Matrix[ 0 ] = m_M[ 0 ]+p_Other[ 0 ];
			Matrix[ 1 ] = m_M[ 1 ]+p_Other[ 1 ];
			Matrix[ 2 ] = m_M[ 2 ]+p_Other[ 2 ];
			Matrix[ 3 ] = m_M[ 3 ]+p_Other[ 3 ];
			Matrix[ 4 ] = m_M[ 4 ]+p_Other[ 4 ];
			Matrix[ 5 ] = m_M[ 5 ]+p_Other[ 5 ];
			Matrix[ 6 ] = m_M[ 6 ]+p_Other[ 6 ];
			Matrix[ 7 ] = m_M[ 7 ]+p_Other[ 7 ];
			Matrix[ 8 ] = m_M[ 8 ]+p_Other[ 8 ];

			return Matrix;
		}

		Matrix3x3 Matrix3x3::operator-( const Matrix3x3 &p_Other ) const
		{
			Matrix3x3 Matrix;

			Matrix[ 0 ] = m_M[ 0 ]-p_Other[ 0 ];
			Matrix[ 1 ] = m_M[ 1 ]-p_Other[ 1 ];
			Matrix[ 2 ] = m_M[ 2 ]-p_Other[ 2 ];
			Matrix[ 3 ] = m_M[ 3 ]-p_Other[ 3 ];
			Matrix[ 4 ] = m_M[ 4 ]-p_Other[ 4 ];
			Matrix[ 5 ] = m_M[ 5 ]-p_Other[ 5 ];
			Matrix[ 6 ] = m_M[ 6 ]-p_Other[ 6 ];
			Matrix[ 7 ] = m_M[ 7 ]-p_Other[ 7 ];
			Matrix[ 8 ] = m_M[ 8 ]-p_Other[ 8 ];

			return Matrix;
		}

		Matrix3x3 Matrix3x3::operator-( ) const
		{
			Matrix3x3 Matrix;

			Matrix[ 0 ] = -m_M[ 0 ];
			Matrix[ 1 ] = -m_M[ 1 ];
			Matrix[ 2 ] = -m_M[ 2 ];
			Matrix[ 3 ] = -m_M[ 3 ];
			Matrix[ 4 ] = -m_M[ 4 ];
			Matrix[ 5 ] = -m_M[ 5 ];
			Matrix[ 6 ] = -m_M[ 6 ];
			Matrix[ 7 ] = -m_M[ 7 ];
			Matrix[ 8 ] = -m_M[ 8 ];

			return Matrix;
		}

		Matrix3x3 Matrix3x3::operator*( const Matrix3x3 &p_Other ) const
		{
			Matrix3x3 Matrix;
			
			Matrix[ 0 ] = m_M[ 0 ]*p_Other[ 0 ] + m_M[ 3 ]*p_Other[ 1 ] +
				m_M[ 6 ]*p_Other[ 2 ];
			Matrix[ 1 ] = m_M[ 1 ]*p_Other[ 0 ] + m_M[ 4 ]*p_Other[ 1 ] +
				m_M[ 7 ]*p_Other[ 2 ];
			Matrix[ 2 ] = m_M[ 2 ]*p_Other[ 0 ] + m_M[ 5 ]*p_Other[ 1 ] +
				m_M[ 8 ]*p_Other[ 2 ];

			Matrix[ 3 ] = m_M[ 0 ]*p_Other[ 3 ] + m_M[ 3 ]*p_Other[ 4 ] +
				m_M[ 6 ]*p_Other[ 5 ];
			Matrix[ 4 ] = m_M[ 1 ]*p_Other[ 3 ] + m_M[ 4 ]*p_Other[ 4 ] +
				m_M[ 7 ]*p_Other[ 5 ];
			Matrix[ 5 ] = m_M[ 2 ]*p_Other[ 3 ] + m_M[ 5 ]*p_Other[ 4 ] +
				m_M[ 8 ]*p_Other[ 5 ];

			Matrix[ 6 ] = m_M[ 0 ]*p_Other[ 6 ] + m_M[ 3 ]*p_Other[ 7 ] +
				m_M[ 6 ]*p_Other[ 8 ];
			Matrix[ 7 ] = m_M[ 1 ]*p_Other[ 6 ] + m_M[ 4 ]*p_Other[ 7 ] +
				m_M[ 7 ]*p_Other[ 8 ];
			Matrix[ 8 ] = m_M[ 2 ]*p_Other[ 6 ] + m_M[ 5 ]*p_Other[ 7 ] +
				m_M[ 8 ]*p_Other[ 8 ];

			return Matrix;
		}

		Vector3 operator*( const Vector3 &p_Vec, const Matrix3x3 &p_Matrix )
		{
			Vector3 Vec;

			Vec[ 0 ] = p_Vec[ 0 ]*p_Matrix[ 0 ] + p_Vec[ 1 ]*p_Matrix[ 1 ] +
				p_Vec[ 2 ]*p_Matrix[ 2 ];
			Vec[ 1 ] = p_Vec[ 0 ]*p_Matrix[ 3 ] + p_Vec[ 1 ]*p_Matrix[ 4 ] +
				p_Vec[ 2 ]*p_Matrix[ 5 ];
			Vec[ 2 ] = p_Vec[ 0 ]*p_Matrix[ 6 ] + p_Vec[ 1 ]*p_Matrix[ 7 ] +
				p_Vec[ 2 ]*p_Matrix[ 8 ];

			return Vec;
		}

		Matrix3x3 operator*( const ZED_FLOAT32 p_Scalar,
			const Matrix3x3 &p_Matrix )
		{
			Matrix3x3 Matrix;

			Matrix[ 0 ] = p_Matrix[ 0 ]*p_Scalar;
			Matrix[ 1 ] = p_Matrix[ 1 ]*p_Scalar;
			Matrix[ 2 ] = p_Matrix[ 2 ]*p_Scalar;
			Matrix[ 3 ] = p_Matrix[ 3 ]*p_Scalar;
			Matrix[ 4 ] = p_Matrix[ 4 ]*p_Scalar;
			Matrix[ 5 ] = p_Matrix[ 5 ]*p_Scalar;
			Matrix[ 6 ] = p_Matrix[ 6 ]*p_Scalar;
			Matrix[ 7 ] = p_Matrix[ 7 ]*p_Scalar;
			Matrix[ 8 ] = p_Matrix[ 8 ]*p_Scalar;

			return Matrix;
		}

		Matrix3x3 Matrix3x3::operator*( const ZED_FLOAT32 p_Scalar ) const
		{
			Matrix3x3 Matrix;

			Matrix[ 0 ] = m_M[ 0 ]*p_Scalar;
			Matrix[ 1 ] = m_M[ 1 ]*p_Scalar;
			Matrix[ 2 ] = m_M[ 2 ]*p_Scalar;
			Matrix[ 3 ] = m_M[ 3 ]*p_Scalar;
			Matrix[ 4 ] = m_M[ 4 ]*p_Scalar;
			Matrix[ 5 ] = m_M[ 5 ]*p_Scalar;
			Matrix[ 6 ] = m_M[ 6 ]*p_Scalar;
			Matrix[ 7 ] = m_M[ 7 ]*p_Scalar;
			Matrix[ 8 ] = m_M[ 8 ]*p_Scalar;

			return Matrix;
		}

		Vector3 Matrix3x3::operator*( const Vector3 &p_Vec ) const
		{
			Vector3 Vec;

			Vec[ 0 ] = m_M[ 0 ]*p_Vec[ 0 ] + m_M[ 3 ]*p_Vec[ 1 ] +
				m_M[ 6 ]*p_Vec[ 2 ];
			Vec[ 1 ] = m_M[ 1 ]*p_Vec[ 0 ] + m_M[ 4 ]*p_Vec[ 1 ] +
				m_M[ 7 ]*p_Vec[ 2 ];
			Vec[ 2 ] = m_M[ 2 ]*p_Vec[ 0 ] + m_M[ 5 ]*p_Vec[ 1 ] +
				m_M[ 8 ]*p_Vec[ 2 ];

			return Vec;
		}

		Matrix3x3 &Matrix3x3::operator+=( const Matrix3x3 &p_Other )
		{
			m_M[ 0 ] += p_Other[ 0 ];
			m_M[ 1 ] += p_Other[ 1 ];
			m_M[ 2 ] += p_Other[ 2 ];
			m_M[ 3 ] += p_Other[ 3 ];
			m_M[ 4 ] += p_Other[ 4 ];
			m_M[ 5 ] += p_Other[ 5 ];
			m_M[ 6 ] += p_Other[ 6 ];
			m_M[ 7 ] += p_Other[ 7 ];
			m_M[ 8 ] += p_Other[ 8 ];

			return *this;
		}

		Matrix3x3 &Matrix3x3::operator-=( const Matrix3x3 &p_Other )
		{
			m_M[ 0 ] -= p_Other[ 0 ];
			m_M[ 1 ] -= p_Other[ 1 ];
			m_M[ 2 ] -= p_Other[ 2 ];
			m_M[ 3 ] -= p_Other[ 3 ];
			m_M[ 4 ] -= p_Other[ 4 ];
			m_M[ 5 ] -= p_Other[ 5 ];
			m_M[ 6 ] -= p_Other[ 6 ];
			m_M[ 7 ] -= p_Other[ 7 ];
			m_M[ 8 ] -= p_Other[ 8 ];
			
			return *this;
		}

		Matrix3x3 &Matrix3x3::operator*=( const Matrix3x3 &p_Other )
		{
			Matrix3x3 Copy;
			Copy.Copy( *this );

			m_M[ 0 ] = Copy[ 0 ]*p_Other[ 0 ] + Copy[ 3 ]*p_Other[ 1 ] +
				Copy[ 6 ]*p_Other[ 2 ];
			m_M[ 1 ] = Copy[ 1 ]*p_Other[ 0 ] + Copy[ 4 ]*p_Other[ 1 ] +
				Copy[ 7 ]*p_Other[ 2 ];
			m_M[ 2 ] = Copy[ 2 ]*p_Other[ 0 ] + Copy[ 5 ]*p_Other[ 1 ] +
				Copy[ 8 ]*p_Other[ 2 ];
			
			m_M[ 3 ] = Copy[ 0 ]*p_Other[ 3 ] + Copy[ 3 ]*p_Other[ 4 ] +
				Copy[ 6 ]*p_Other[ 5 ];
			m_M[ 4 ] = Copy[ 1 ]*p_Other[ 3 ] + Copy[ 4 ]*p_Other[ 4 ] +
				Copy[ 7 ]*p_Other[ 5 ];
			m_M[ 5 ] = Copy[ 2 ]*p_Other[ 3 ] + Copy[ 5 ]*p_Other[ 4 ] +
				Copy[ 8 ]*p_Other[ 5 ];

			m_M[ 6 ] = Copy[ 0 ]*p_Other[ 6 ] + Copy[ 3 ]*p_Other[ 7 ] +
				Copy[ 6 ]*p_Other[ 8 ];
			m_M[ 7 ] = Copy[ 1 ]*p_Other[ 6 ] + Copy[ 4 ]*p_Other[ 7 ] +
				Copy[ 7 ]*p_Other[ 8 ];
			m_M[ 8 ] = Copy[ 2 ]*p_Other[ 6 ] + Copy[ 5 ]*p_Other[ 7 ] +
				Copy[ 8 ]*p_Other[ 8 ];
			
			return *this;
		}

		Matrix3x3 &Matrix3x3::operator*=( const ZED_FLOAT32 p_Scalar )
		{
			m_M[ 0 ] *= p_Scalar;
			m_M[ 1 ] *= p_Scalar;
			m_M[ 2 ] *= p_Scalar;
			m_M[ 3 ] *= p_Scalar;
			m_M[ 4 ] *= p_Scalar;
			m_M[ 5 ] *= p_Scalar;
			m_M[ 6 ] *= p_Scalar;
			m_M[ 7 ] *= p_Scalar;
			m_M[ 8 ] *= p_Scalar;

			return *this;
		}

		ZED_FLOAT32 &Matrix3x3::operator( )( const ZED_UINT32 p_Row,
			const ZED_UINT32 p_Column )
		{
			// No bounds checking
			return ( m_M[ p_Row+( p_Column*3 ) ] );
		}

		ZED_FLOAT32 Matrix3x3::operator( )( const ZED_UINT32 p_Row,
			const ZED_UINT32 p_Column ) const
		{
			// No bounds checking
			return ( m_M[ p_Row+( p_Column*3 ) ] );
		}
	}
}

