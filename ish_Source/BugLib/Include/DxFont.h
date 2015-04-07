#ifndef _DX_FONT
#define _DX_FONT

#include "DxLibraryDef.h"
#include <D3dx9core.h>

class DxFont
{
	// constructors and destructors
	public:
		DxFont(void);
		DxFont(int size, char* fontName);
		~DxFont(void);

	// initialization
	public:
		bool Initialize(int size, char* fontName = "Arial");

	// Accessor
	public:
		const LPD3DXFONT& GetFont(void) const;

	// member variable
	private:
		LPD3DXFONT _font;
};

#endif