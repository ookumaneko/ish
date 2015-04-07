#ifndef _DX_MESH
#define _DX_MESH

#include "DxLibraryDef.h"
#include <vector>
#include <string>
#include <D3DX9Mesh.h>

class DxTexture;

class DxMesh
{
	//constructor and destructor
	public:
		DxMesh			(void);
		DxMesh			(const std::string& fileName, DxTexture* texture = 0);
		virtual ~DxMesh	(void);

	//Accessors
	public:
		ID3DXMesh*							GetMesh				(void) 		 { return _mesh; }
		const ID3DXMesh*					GetMesh				(void) const { return _mesh; }
		LPD3DXMESH*							GetMeshPointer		(void)		 { return &_mesh; }
		std::vector<DxTexture*>&			GetTextures			(void) 		 { return _textures; }
		std::vector<D3DMATERIAL9>&			GetMaterials		(void) 		 { return _materials; }
		DxTexture*						GetSingleTexture	(void) 		 { return _singleTexture; }

	// loading and drawing methods
	public:
		void Draw();
		void LoadXFile(const std::string& fileName, DxTexture* texture = 0);
		void LoadXFile(const std::string& fileName, ID3DXMesh** meshOut, std::vector<D3DMATERIAL9>& mtrls, std::vector<DxTexture*>& texs, DxTexture* texture = 0);

	// member variables
	protected:
		ID3DXMesh*					_mesh;
		std::vector<DxTexture*>		_textures;
		std::vector<D3DMATERIAL9>	_materials;
		DxTexture*					_singleTexture;
};

#endif