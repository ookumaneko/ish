#ifndef _DX_VIEW_FRUSTUM_
#define _DX_VIEW_FRUSTUM_

#include "DxLibraryDef.h"
#include <D3dx9math.h>

class DxMatrix;
class DxShape;

class DxViewFrustum
{
	// Constructor and destructors
	public:
		DxViewFrustum(void);
		DxViewFrustum(DxViewFrustum& rhs);
		~DxViewFrustum(void);

	// operators
	public:
		DxViewFrustum&	operator=	(const DxViewFrustum& rhs);
		bool			operator==	(const DxViewFrustum& rhs);	
		bool			operator!=	(const DxViewFrustum& rhs);

	// Accesors
	public:
		D3DXMATRIX& GetMatrix(void) { return _viewProjection; }
		void SetMatrix(DxMatrix& viewProjection);

	// Update and Bound Check
	public:
		void Update		(DxMatrix& viewProjection);
		bool BoundCheck	(DxShape* pShape);

	// member variables
	protected:
		D3DXMATRIX	_viewProjection;
		D3DXPLANE	_planes[6];
};

#endif