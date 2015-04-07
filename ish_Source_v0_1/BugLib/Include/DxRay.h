#ifndef _DX_RAY_
#define _DX_RAY_

#include "DxLibraryDef.h"
#include "D3dx9math.h"

class DxMatrix;
class DxVector3;
class DxMesh;
class DxShape;
class DxShapeSphere;
class DxAABB;

class DxRay
{
	// Constructor and destructor
	public:
		DxRay(const DxVector3& origin, const DxVector3& direction);
		~DxRay(void);

	// intersection test methods
	public:
		float IntersectMesh( DxMesh* mesh );
		float IntersectMesh( DxMesh* mesh, const DxMatrix& mat );										// mesh teat

		float IntersectShape( DxShape* shape );
		float IntersectShape( DxShape* shape, const DxMatrix& mat );
		
		float IntersectSphere( DxShapeSphere* sphere );										// for any shape
		float IntersectSphere( DxShapeSphere* sphere, const DxMatrix& mat );								// spherer test
		
		float IntersectAABB( DxAABB* box );
		float IntersectAABB( DxAABB* box, const DxMatrix& mat );
		
		float IntersectTri( const DxVector3& v1, const DxVector3& v2, const DxVector3& v3 );
		float IntersectTri( const DxVector3& v1, const DxVector3& v2, const DxVector3& v3, const DxMatrix& mat );		// triangle test

	// member variables
	private:
		D3DXVECTOR3 _origin, _direction;
};

#endif