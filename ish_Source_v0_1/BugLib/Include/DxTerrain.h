#ifndef _DX_TERRAIN_NODE
#define _DX_TERRAIN_NODE
#include "DxGrid.h"

class DxTexture;
class DxSubGrid;

class DxTerrain : public DxGrid
{
	//constructors
	private:
		DxTerrain(void);

	public:
		DxTerrain( std::string name, const DWORD size, DWORD colour, unsigned int fillMode, bool tileTexture, DxTexture* pTexture = NULL );
		DxTerrain( std::string name, std::string path, const DWORD size, DWORD colour, bool tileTexture, DxTexture* pTexture = NULL );

		DxTerrain( std::string name, const DWORD numRows, const DWORD numCols, const float spacingX, 
					   const float spacingZ, const DWORD colour, bool tileTexture, DxTexture* pTexture = NULL );

		DxTerrain( std::string name, std::string path, const DWORD numRows, const DWORD numCols, const float spacingX, 
					   const float spacingZ, const DWORD colour, unsigned int fillMode, bool tileTexture, DxTexture* pTexture = NULL );

		~DxTerrain(void);

	//overloaded methods
	protected:
		virtual bool Initialize			(void);
		virtual bool GenerateVertices	(void);
		virtual bool GenerateIndices	(void);
		virtual void Draw				(float delta);

	//Hight map loader method
	protected:
		bool LoadFile (const char* fileName);			// Load the height map data
	
	// Accesor
	public:
		float GetHeightmapEntry(int row, int col);

	// mesh generation
	public:
		void CreateMesh(int numSubGridVerts);

	protected:
		void BuildSubGridMesh(RECT& R, GRID_NODE_VERTEX* gridVerts); 
		void GenerateGridData(int numRows, int numCols, float dx, float dz, D3DXVECTOR3& center, std::vector<D3DXVECTOR3>& verts, std::vector<DWORD>& indices );

	// height generation methods
	public:
		void MakeTerrainFaultFormation		(int iterations,int maxDelta,int minDelta,int iterationsPerFilter,float filter);
		void MakeTerrainMidpointDisplace	(float rough);
		void MakeTerrainDeposition			(int jumps, int peakWalk, int minParticlesPerJump, int maxParticlesPerJump, float caldera);

		void ScaleHeight					(float scale);

		bool GenerateTexture				(void);

	private:
		void FilterHeightField	(float filter); 
		void FilterHeightBand	(int index, int stride, int count, float filter); 
		void NormalizeHeight	(void);

	public:
		int _numDrawn;
		std::vector<DxSubGrid*> _subGrids;

	// members
	protected:
		std::string			_path;
		std::vector<float>	_heights;			// Array if height values

		std::vector<ID3DXMesh*> _subGridMeshes;
		std::vector<DxAABB>		_subGridAABB;
};

#endif