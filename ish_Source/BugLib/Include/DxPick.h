#ifndef _DX_PICK_
#define _DX_PICK_
//#include "DxRay.h"

#include "DxLibraryDef.h"

class DxVector2;
class DxMatrix;
class DxRay;

class DxPick
{
	// constructor and destructor
	public:
		DxPick(void);
		~DxPick(void);

	// picking methods
	public:
		DxRay GetPickResult(void);
		DxRay GetPickResult( const DxVector2& position, bool isMouse);  
};

#endif