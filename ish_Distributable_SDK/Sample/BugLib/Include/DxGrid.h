#ifndef _DX_GRID_NODE
#define _DX_GRID_NODE

#include "DxSceneNode.h"

#define D3DFVF_GRID_NODE_VERTEX ( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 )

class DxTexture;
class DxVector3;
class DxMesh;

class DxGrid : public DxSceneNode
{
	// default constructor
	private:
		DxGrid(void);
		
	public:
		// vertex data for the terrain
		struct GRID_NODE_VERTEX
		{
			D3DXVECTOR3 position; // The position
			D3DXVECTOR3 normal;	  // The normal
			D3DCOLOR    color;    // The color
			FLOAT       tu, tv;   // The texture coordinates

			static IDirect3DVertexDeclaration9* decl;
		};

	// public constructor and destructors
	public:
		DxGrid(std::string name, const DWORD size, const DWORD colour, unsigned int fillMode, bool tileTexture, DxTexture* pTexture = NULL );

		DxGrid(std::string name, const DWORD numRows, const DWORD numCols, const float spacingX, 
				   const float spacingZ, const DWORD colour, unsigned int fillMode, bool tileTexture, DxTexture* pTexture = NULL );

		virtual ~DxGrid(void);

	// Accessor
	public:
		void	GetTriangle	( int index, DxVector3& v1, DxVector3& v2, DxVector3& v3 );
		void	GetTriangle	( const DxVector3& pos, DxVector3& v1, DxVector3& v2, DxVector3& v3 );

	//framwork methods
	public:
		virtual bool	Initialize	(void);
		virtual void	Update		(float delta);
		virtual void	Draw		(float delta);		
		virtual bool	Shutdown	(void) {return true;}

	//Events
	protected:
		virtual void	OnAdded		(void);
		virtual void	OnRemoved	(void) {};
	
	//initialization
	protected:
		virtual bool GenerateVertices	(void);
		virtual bool GenerateIndices	(void);

	// member variables
	protected:
		DxTexture*								_texture;		// the grid texture
		std::vector<GRID_NODE_VERTEX>			_vertices;		// The grid vertices
		std::vector<DWORD>						_indices;		// the grid indices
		LPDIRECT3DVERTEXBUFFER9					_vertexBuffer;	// The grid vertex buffer
		LPDIRECT3DINDEXBUFFER9					_indexBuffer;	// the grid index buffer
		IDirect3DVertexDeclaration9*			_declaration;
		DWORD									_numVertices;	// The total number of vertices
		D3DXVECTOR3								_center;
		DWORD									_numPolys;		// The total number of polygons created

		unsigned int							_fillMode;
		int										_numRows;			// Number of polygons width
		int										_numCols;			// Number of polygons length
		float									_spacingX, _spacingZ;		// Space between each vertex
		DWORD									_colour;		// Colour of the entire grid
		bool									_tileTexture;

		ID3DXEffect* 							_FX;
		D3DXHANDLE								_hTech;
		D3DXHANDLE								_hWVP;
		D3DXHANDLE								_hTime;
};

#endif