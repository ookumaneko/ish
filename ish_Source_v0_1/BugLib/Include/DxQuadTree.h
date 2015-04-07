#ifndef _DX_QUAD_TREE_
#define _DX_QUAD_TREE_

#include <windows.h>
#include <list>

// farward decleration
class DxQuadNode;
class DxQuadObject;
class DxViewFrustum;
class DxMatrix;
class DxVector3;
class DxSceneNode;
class DxShape;

class DxQuadTree
{
	// constructor and destructor
	private:
		DxQuadTree(void);

	public:
		virtual ~DxQuadTree(void);

	// member methods
	public:
		static DxQuadTree* GetInstance(void);

	public:
		bool BuildTree	(unsigned int level, float x, float y, float width, float height); 
		bool Submit		(float x, float y, float width, float height, DxQuadObject* object); 
		void CullNodes	(DxViewFrustum& frust); 
		void CheckCollision(DxShape* volume, std::list<DxSceneNode*>& objects);

	// Recursive methods
	protected:
		void ProcessCollisionCheck(DWORD index, DxShape* volume, std::list<DxSceneNode*>& objects);
		void ProcessCulling		  (DxViewFrustum& frust, DWORD index);
		void ProcessBuild		  (DWORD index);

	// Bit separetion and Direct Access Methods
	protected:
		DWORD GetIndex			(float x, float y, float right, float bottom, DWORD& level);
		DWORD SeparateBits		(DWORD num);
		WORD  Get2DIndex		(WORD x, WORD y);
		DWORD GetIndexFromXY	(float x, float y);

	public:
		const static int _MAX_LEVEL;
		int _drawCount;		// for degbug

	// members
	protected:			
		DxQuadNode**		_nodes;
		unsigned int		_iPow[ 10 ];		// number of nodes in each level
		float				_width, _height;
		float				_x, _y;
		float				_minWidth, _minHeight;
		DWORD				_numNodes;
		unsigned int		_minLevel;
		float				_h;

	private:
		static DxQuadTree* _instance;

};


#endif