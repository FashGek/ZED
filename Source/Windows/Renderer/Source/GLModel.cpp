#include <GLModel.hpp>
#include <GLExtender.hpp>
#include <GLShader.hpp>

namespace ZED
{
	namespace Renderer
	{
		GLModel::GLModel( const Renderer *p_pRenderer )
		{
			// Null all pointers and set other variables to sane values
			m_pFile = ZED_NULL;
			m_ppVertices = ZED_NULL;
			m_ppIndices = ZED_NULL;
			m_pAttributes = ZED_NULL;
			m_pMaterialID = ZED_NULL;
			m_pStride = ZED_NULL;

			m_pIndexCount = ZED_NULL;
			m_pVertexCount = ZED_NULL;

			m_pJointBindPosition = ZED_NULL;
			m_pJointBindOrientation = ZED_NULL;
			m_pJointParents = ZED_NULL;

			m_MeshCount = 0;
			m_JointCount = 0;
			m_SwapBytes = ZED_FALSE;
			m_World.Identity( );

			m_pRenderer = const_cast< Renderer * >( p_pRenderer );
			
#ifdef ZED_BUILD_DEBUG
			m_RenderWireframe = ZED_FALSE;
			m_RenderVNormals = ZED_FALSE;
			m_RenderFNormals = ZED_FALSE;
			m_RenderBones = ZED_FALSE;

			m_pBoneVertices = ZED_NULL;
			m_pBoneIndices = ZED_NULL;
#endif
		}

		GLModel::~GLModel( )
		{
			if( m_ppVertices != ZED_NULL )
			{
				for( ZED_MEMSIZE i = 0; i < m_MeshCount; i++ )
				{
					if( m_ppVertices[ i ] != ZED_NULL )
					{
						delete [ ] m_ppVertices[ i ];
						m_ppVertices[ i ] = ZED_NULL;
					}
				}
				delete [ ] m_ppVertices;
				m_ppVertices = ZED_NULL;
			}

			if( m_ppIndices != ZED_NULL )
			{
				for( ZED_MEMSIZE i = 0; i < m_MeshCount; i++ )
				{
					if( m_ppIndices[ i ] != ZED_NULL )
					{
						delete [ ] m_ppIndices[ i ];
						m_ppIndices[ i ] = ZED_NULL;
					}
				}
				delete [ ] m_ppIndices;
				m_ppIndices = ZED_NULL;
			}

			if( m_pJointBindPosition != ZED_NULL )
			{
				delete [ ] m_pJointBindPosition;
				m_pJointBindPosition = ZED_NULL;
			}

			if( m_pJointBindOrientation != ZED_NULL )
			{
				delete [ ] m_pJointBindOrientation;
				m_pJointBindOrientation = ZED_NULL;
			}

			if( m_pJointParents != ZED_NULL )
			{
				delete [ ] m_pJointParents;
				m_pJointParents = ZED_NULL;
			}

#ifdef ZED_BUILD_DEBUG
			if( m_pBoneVertices != ZED_NULL )
			{
				delete [ ] m_pBoneVertices;
				m_pBoneVertices = ZED_NULL;
			}

			if( m_pBoneIndices != ZED_NULL )
			{
				delete [ ] m_pBoneIndices;
				m_pBoneIndices = ZED_NULL;
			}
#endif

			if( m_pFile != ZED_NULL )
			{
				fclose( m_pFile );
				m_pFile = ZED_NULL;
			}
		}

		ZED_UINT32 GLModel::Load( const ZED_CHAR8 *p_pFileName )
		{
			m_pFile = fopen( p_pFileName, "rb" );

			if( m_pFile == ZED_NULL )
			{
				zedTrace( "[ZED|Renderer|Model|Load] <ERROR> "
					"Failed to load model: %s\n.", p_pFileName );
				return ZED_FAIL;
			}

			// The first chunk MUST be the header
			if( LoadHeader( ) != ZED_OK )
			{
				fclose( m_pFile );
				m_pFile = ZED_NULL;
				return ZED_FAIL;
			}

			ZED_UINT16 Type;
			ZED_UINT64 Size;

			ReadChunk( Type, Size );

			// Read all remaining chunks
			while( Type != ZED_MODEL_END ) 
			{
				switch( Type )
				{
					case ZED_MODEL_MESH:
					{
						LoadMeshes( Size );
						// Get more?
						ReadChunk( Type, Size );
						break;
					}
					case ZED_MODEL_ANIMATION:
					{
						LoadAnimation( Size );
						// Get more?
						ReadChunk( Type, Size );
						break;
					}
					default:
					{
						zedTrace( "[ZED::Renderer::GLModel::Load] <ERROR> "
							"Unknown type chunk.\n" );

						fclose( m_pFile );
						m_pFile = ZED_NULL;

						return ZED_FAIL;
					}
				}
			}

			fclose( m_pFile );
			m_pFile = ZED_NULL;

			return ZED_OK;
		}

		void GLModel::Render( )
		{
#ifdef ZED_BUILD_DEBUG
			// For debugging purposes, check if the model is to be rendered
			// as a wireframe mesh, the vertex normals, face normals, and bones
			if( m_RenderWireframe )
			{
				m_pRenderer->Render( m_BoneVCount, m_pBoneVertices,
					m_BoneICount, m_pBoneIndices, 0x6, 0 );
			}
			if( !m_RenderWireframe )
			{
#endif
				for( ZED_MEMSIZE i = 0; i < m_MeshCount; i++ )
				{
					m_pRenderer->Render( m_pVertexCount[ i ],
						m_ppVertices[ i ], m_pIndexCount[ i ],
						m_ppIndices[ i ], m_pAttributes[ i ],
						m_pMaterialID[ i ] );
				}
#ifdef	ZED_BUILD_DEBUG
			}
#endif
		}

		void GLModel::Update( const ZED_FLOAT32 p_Delta,
			const Arithmetic::Matrix4x4 &p_ViewProjection )
		{
			//m_WorldMatrix = m_Scale*m_Orientation*m_Position;
			/*ZED_FLOAT32 *pMatrix = new ZED_FLOAT32[ 16 ];
			pMatrix = ( p_ViewProjection*m_WorldMatrix ).GetMatrix( );
#ifdef ZED_BUILD_DEBUG
			if( m_RenderWireframe )
			{
				m_pDebugShader->Activate( );
				m_pDebugShader->SetVariable( 0, pMatrix );
			}
#endif
			delete pMatrix;*/
		}

		void GLModel::SetPosition( const Arithmetic::Vector3 &p_Position )
		{
			m_Position.Copy( p_Position );
			m_World.Translate( m_Position );
		}

		void GLModel::SetScale( const Arithmetic::Vector3 &p_Scale )
		{
			m_Scale.Copy( p_Scale );
			m_World.Scale( m_Scale );
		}

		void GLModel::SetOrientation( const Arithmetic::Quaternion &p_Orientation )
		{
			m_Orientation.Copy( p_Orientation );
			m_World.Rotate( m_Orientation );
		}

		ZED_UINT32 GLModel::LoadHeader( )
		{
			LPFILEHEADER_V2 pHeaderInfo = new FILEHEADER_V2;
			// Assume file is already open
			ZED_UINT16 ChunkType;
			ZED_UINT64 ChunkSize;

			ReadChunk( ChunkType, ChunkSize );

			if( ChunkType != ZED_MODEL_HEADER )
			{
				zedTrace( "[ZED|Renderer|Model|LoadHeader] <ERROR> "
					"Chunk is not a header chunk.\n" );
				delete pHeaderInfo;
				return ZED_FAIL;
			}

			fread( pHeaderInfo, sizeof( FILEHEADER_V2 ), 1, m_pFile );

			// Make sure that this is in the correct format
			ReadChunk( ChunkType, ChunkSize );

			if( ChunkType != ZED_MODEL_END )
			{
				zedTrace( "[ZED|Renderer|Model|LoadHeader] <ERROR> "
					"Unexpected data: Non-end chunk.\n" );
				delete pHeaderInfo;
				return ZED_FAIL;
			}

			if( pHeaderInfo->ID[ 0 ] != 'Z' &&
				pHeaderInfo->ID[ 1 ] != 'E' &&
				pHeaderInfo->ID[ 2 ] != 'D' )
			{
				zedTrace( "[ZED|Renderer|Model|LoadHeader] <ERROR> "
					"Not a ZED Model.\n" );
				return ZED_FAIL;
			}

			m_Flags = pHeaderInfo->Flags;

			// Swap endian?
			if( m_Flags && 0x00000001 )
			{
				zedTrace( "[ZED::Renderer::Model::LoadHeader] <INFO> "
					"Swapping byte order.\n" );
				m_SwapBytes = ZED_TRUE;
			}

			m_MeshCount = pHeaderInfo->MeshCount;
			m_JointCount = pHeaderInfo->JointCount;

#ifdef ZED_BUILD_DEBUG
			ZED_CHAR8 *pEndianess = ZED_NULL;

			if( m_Flags && 0x00000001 )
			{
				pEndianess = new ZED_CHAR8[ 4 ];
				strncpy( pEndianess, "Big\0", 4 );
			}
			else
			{
				pEndianess = new ZED_CHAR8[ 7 ];
				strncpy( pEndianess, "Little\0", 7 );
			}

			zedTrace( "[ZED::Renderer::Model::LoadHeader] <INFO >"
				"Header loaded successfully.\n" );
			zedTrace( "\tEndianess: %s | Version: %d.%d.%d | "
				"Meshes: %d | Joints: %d\n", pEndianess,
				pHeaderInfo->Version[ 0 ], pHeaderInfo->Version[ 1 ],
				pHeaderInfo->Version[ 2 ], m_MeshCount, m_JointCount );
#endif
			if( pHeaderInfo != ZED_NULL )
			{
				delete pHeaderInfo;
				pHeaderInfo = ZED_NULL;
			}

			return ZED_OK;
		}
		
		ZED_UINT32 GLModel::LoadMeshes( ZED_UINT64 p_Size )
		{
			ZED_UINT32 TempSize = p_Size;

			// The total indices stores the offset for the next set of indices
			ZED_UINT16 TotalIndices = 0;
			ZED_UINT16 TotalWireIndices = 0;

			if( m_pAttributes )
			{
				delete [ ] m_pAttributes;
				m_pAttributes = ZED_NULL;
			}

			m_pAttributes = new ZED_UINT64[ m_MeshCount ];
			m_pMaterialID = new ZED_UINT32[ m_MeshCount ];
			m_pStride = new ZED_BYTE[ m_MeshCount ];
			m_pVertexCount = new ZED_UINT16[ m_MeshCount ];
			m_pIndexCount = new ZED_UINT16[ m_MeshCount ];
			m_ppVertices = new ZED_BYTE*[ m_MeshCount ];
			m_ppIndices = new ZED_UINT16*[ m_MeshCount ];

			// Read in each mesh
			for( ZED_UINT32 i = 0; i < m_MeshCount; i++ )
			{
				fread( &m_pAttributes[ i ], sizeof( ZED_UINT64 ), 1, m_pFile );
				fread( &m_pMaterialID[ i ], sizeof( ZED_UINT32 ), 1, m_pFile );
				fread( &m_pVertexCount[ i ], sizeof( ZED_UINT16 ), 1,
					m_pFile );
				fread( &m_pIndexCount[ i ], sizeof( ZED_UINT16 ), 1, m_pFile );
				fread( &m_pStride[ i ], sizeof( ZED_BYTE ), 1, m_pFile );

				m_ppVertices[ i ] =
					new ZED_BYTE[ m_pVertexCount[ i ]*m_pStride[ i ] ];
				m_ppIndices[ i ] = new ZED_UINT16[ m_pIndexCount[ i ] ];
				fread( m_ppVertices[ i ], sizeof( ZED_BYTE )*m_pStride[ i ],
					m_pVertexCount[ i ], m_pFile );
				fread( m_ppIndices[ i ], sizeof( ZED_UINT16 ),
					m_pIndexCount[ i ], m_pFile );

				// Add the indices in the mesh to the total count for the whole
				// model
				TotalIndices += m_pIndexCount[ i ];
			}

			ZED_UINT16 Type;
			ZED_UINT64 Size;
			ReadChunk( Type, Size );

			// It should end with the end chunk
			if( Type != ZED_MODEL_END )
			{
				zedTrace( "[ZED|Renderer|Model|LoadMeshes] <ERROR> "
					"Unexpected data: Non-end chunk.\n" );
				return ZED_FAIL;
			}

			return ZED_OK;
		}

		ZED_UINT32 GLModel::LoadAnimation( const ZED_UINT64 p_Size )
		{
			m_JointCount = p_Size / sizeof( JOINT_V2 );
			m_pJointBindPosition = new Arithmetic::Vector3[ m_JointCount ];
			m_pJointBindOrientation =
				new Arithmetic::Quaternion[ m_JointCount ];
			m_pJointParents = new ZED_BYTE[ m_JointCount ];

			m_pJoints = new JOINT_V2[ m_JointCount ];

			ZED_MEMSIZE BoneCount = 0;

			// Read in joints
			for( ZED_MEMSIZE i = 0; i < m_JointCount; i++ )
			{
				fread( &m_pJoints[ i ].Orientation, sizeof( ZED_FLOAT32 ), 4,
					m_pFile );
				fread( &m_pJoints[ i ].Position, sizeof( ZED_FLOAT32 ), 3,
					m_pFile );
				fread( &m_pJoints[ i ].Parent, sizeof( ZED_BYTE ), 1, m_pFile );

				if( m_pJoints[ i ].Parent != 255 )
				{
					BoneCount++;
				}
			}

#ifdef ZED_BUILD_DEBUG
			// Set up the debug bone rendering
			// Each bone is composed of six vertices
			m_BoneVCount = 3*BoneCount;
			// There should be 24 indices in each bone
			m_BoneICount = BoneCount*3;

			ZED_MEMSIZE BoneSize = sizeof( ZED_FLOAT32 )*3*m_BoneVCount;
			m_pBoneVertices = new ZED_BYTE[ BoneSize ];
			m_pBoneIndices = new ZED_UINT16[ m_BoneICount ];

			ZED_MEMSIZE SingleBone = sizeof( ZED_FLOAT32 )*3*3;
			ZED_MEMSIZE Curr = 0;

			// Construct the bones
			for( ZED_MEMSIZE i = 0; i < BoneCount; i++ )
			{
				if( m_pJoints[ i ].Parent != 255 )
				{
					Arithmetic::Vector3 Normal;
					Arithmetic::Vector3 Parent, Child;
					Arithmetic::Matrix3x3 ZRot;
					ZRot.RotateZ( 90.0f );

					Parent.Set(
						m_pJoints[ m_pJoints[ i ].Parent ].Position[ 0 ],
						m_pJoints[ m_pJoints[ i ].Parent ].Position[ 1 ],
						m_pJoints[ m_pJoints[ i ].Parent ].Position[ 2 ] );
					Child.Set( m_pJoints[ i ].Position[ 0 ],
						m_pJoints[ i ].Position[ 1 ],
						 m_pJoints[ i ].Position[ 2 ] );

					Normal.Copy( Child - Parent );
					Normal.Normalise( );

					
					// Create four vertices along the normal
					ZED::Arithmetic::Vector3 V1, V2, V3, V4;
					ZED::Arithmetic::Vector3 Base, ParentL, ParentR;
					Base.Copy( Normal*2 );
					V1.Copy( ZRot*Base );
					// Now rotate around the Y axis
					ZED::Arithmetic::Matrix3x3 RotY;
					RotY.RotateY( 90.0f );
					V2.Copy( RotY*Base );
					RotY.RotateY( 90.0f );
					V3.Copy( RotY*Base );
					RotY.RotateY( 90.0f );
					V4.Copy( RotY*Base );

					ParentL.Copy( Parent );
					ParentL.SetX( Parent[ 0 ] -1.0f );

					ParentR.Copy( Parent );
					ParentR.SetX( Parent[ 0 ] +1.0f );

					// First, the parent
					memcpy( &m_pBoneVertices[ Curr*SingleBone ],
						&ParentL, sizeof( ZED_FLOAT32 )*3 );
					// Next the four vertices along the normal
					/*memcpy( &m_pBoneVertices[
							i*SingleBone+sizeof( ZED_FLOAT32 )*3 ],
						&V1, sizeof( ZED_FLOAT32 )*3 );
					memcpy( &m_pBoneVertices[
							i*SingleBone+sizeof( ZED_FLOAT32 )*6 ],
						&V2, sizeof( ZED_FLOAT32 )*3 );
					memcpy( &m_pBoneVertices[
							i*SingleBone+sizeof( ZED_FLOAT32 )*9 ],
						&V3, sizeof( ZED_FLOAT32 )*3 );
					memcpy( &m_pBoneVertices[
							i*SingleBone+sizeof( ZED_FLOAT32 )*12 ],
						&V4, sizeof( ZED_FLOAT32 )*3 );*/
					// Finally, the child
					memcpy( &m_pBoneVertices[ Curr*SingleBone+sizeof( ZED_FLOAT32 )*3 ],
						&ParentR, sizeof( ZED_FLOAT32 )*3 );
					memcpy( &m_pBoneVertices[
							Curr*SingleBone+sizeof( ZED_FLOAT32 )*6 ],
						&Child, sizeof( ZED_FLOAT32 )*3 );

					ZED_UINT16 *Indices = new ZED_UINT16[ 24 ];

					Indices[ 0 ] = Curr*3;
					Indices[ 1 ] = ( Curr*3 )+1;
					Indices[ 2 ] = ( Curr*3 )+2;
					/*Indices[ 3 ] = ( i*6 )+0;
					Indices[ 4 ] = ( i*6 )+2;
					Indices[ 5 ] = ( i*6 )+3;
					Indices[ 6 ] = ( i*6 )+0;
					Indices[ 7 ] = ( i*6 )+3;
					Indices[ 8 ] = ( i*6 )+4;
					Indices[ 9 ] = ( i*6 )+0;
					Indices[ 10 ] = ( i*6 )+4;
					Indices[ 11 ] = ( i*6 )+1;
					Indices[ 12 ] = ( i*6 )+2;
					Indices[ 13 ] = ( i*6 )+5;
					Indices[ 14 ] = ( i*6 )+1;
					Indices[ 15 ] = ( i*6 )+3;
					Indices[ 16 ] = ( i*6 )+5;
					Indices[ 17 ] = ( i*6 )+2;
					Indices[ 18 ] = ( i*6 )+4;
					Indices[ 19 ] = ( i*6 )+5;
					Indices[ 20 ] = ( i*6 )+3;
					Indices[ 21 ] = ( i*6 )+1;
					Indices[ 22 ] = ( i*6 )+5;
					Indices[ 23 ] = ( i*6 )+4;*/

					memcpy( &m_pBoneIndices[ Curr*3 ], Indices,
						sizeof( ZED_UINT16 )*3 );

					delete [ ] Indices;

					Curr++;
				}
			}
#endif

			ZED_UINT16 Type;
			ZED_UINT64 Size;
			ReadChunk( Type, Size );

			if( Type != ZED_MODEL_END )
			{
				zedTrace( "[ZED::Renderer::GLModel::LoadAnimation] <ERROR>"
					"Unexpected data: Non-end chunk.\n" );
				zedTrace( "Type: 0x%04X | Size: 0x%016X\n" );
				return ZED_FAIL;
			}

			return ZED_OK;
		}

		void GLModel::ReadChunk( ZED_UINT16 &p_Type, ZED_UINT64 &p_Size )
		{
			fread( &p_Type, sizeof( ZED_UINT16 ), 1, m_pFile );
			fread( &p_Size, sizeof( ZED_UINT64 ), 1, m_pFile );
		}

#ifdef ZED_BUILD_DEBUG
		void GLModel::SetWireframeColour( const ZED_COLOUR &p_Colour )
		{
			m_MeshWireColour = p_Colour;
		}

		void GLModel::ToggleWireframe( )
		{
			m_RenderWireframe = !m_RenderWireframe;
		}

		void GLModel::ToggleVertexNormals( )
		{
			m_RenderVNormals != m_RenderVNormals;
		}

		void GLModel::ToggleFaceNormals( )
		{
			m_RenderFNormals != m_RenderFNormals;
		}

		void GLModel::ToggleBones( )
		{
			m_RenderBones != m_RenderBones;
		}
#endif
	}
}
