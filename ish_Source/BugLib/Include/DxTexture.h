#ifndef _DX_TEXTURE_2D
#define _DX_TEXTURE_2D

#include "DxLibraryDef.h"
#include <d3d9.h>

class DxTexture
{
	//constructor and destructor
	public:
		DxTexture(void);
		DxTexture( LPDIRECT3DTEXTURE9 tex);
		DxTexture(LPCSTR fileName);
		~DxTexture(void);

	//operators
	public:
		bool		operator == (const DxTexture& rhs);
		DxTexture&	operator =  (const DxTexture& rhs);

	//Loading methods
	protected:
		bool Load		(LPCSTR fileName);

	// Accessors
	public:
		int  GetWidth	(void) const;
		int  GetHeight	(void) const;

		const LPDIRECT3DTEXTURE9 GetTexture(void) const;
		LPDIRECT3DTEXTURE9		 GetTexture(void) { return _texture; }

		void SetTexture(LPDIRECT3DTEXTURE9 tex);

	//private members
	private:
		LPDIRECT3DTEXTURE9 _texture;
		int _width, _height;
};

#endif