#ifndef _DX_SUB_GRID_H
#define _DX_SUB_GRID_H

#include "dxscenenode.h"

class DxTexture;

class DxSubGrid : public DxSceneNode
{
	public:
		DxSubGrid(std::string name, ID3DXMesh* mesh, DxTexture* tex, DxAABB& aabb);
		~DxSubGrid(void);

	public:
		void Update(float delta);
		void Draw(float delta);

	public:
		static int _numDrawn;
		ID3DXMesh* _mesh;
		DxTexture* _texture;
};

#endif