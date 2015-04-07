#ifndef _DX_SPRITE_
#define _DX_SPRITE_

#include "DxUtil.h"
#include "DxTexture.h"
#include "DxMaths.h"
#include "DxFont.h"
#include <string>

class DxMatrix;
class DxVector2;
class DxTexture;
class DxFont;
class DxColour;
class DxRect;
class string;

class DxSprite
{
	// enumulators
	public:

		enum BlendMode
		{
			AlphaBlend = D3DXSPRITE_ALPHABLEND,
			NoBlend = 0,
		};

		enum SortMode
		{
			NoSort = 0,
			BackToFront = D3DXSPRITE_SORT_DEPTH_BACKTOFRONT,
			FrontToBack = D3DXSPRITE_SORT_DEPTH_FRONTTOBACK,
		};

	// constructor and destructor
	public:
		DxSprite(void);
		~DxSprite(void);

	// Accessor
	public:
		static DxSprite* GetInstance(void);

	// Initialization and Shutdown
	public:
		void Initialize	(void);

	// Begin and End drawing methods
	public:
		void Begin	(DWORD flag = 0);
		void Begin	(DWORD blend, SortMode sort, const DxMatrix& transform);
		void End	(void);

	// Drawing methods
	public:
		//void Draw(const DxTexture& texture, float x, float y, const D3DXCOLOR& colour);
		void Draw(const DxTexture* texture, const DxVector2& position, const DxColour& colour);
		void Draw(const DxTexture* texture, const DxRect& destination, const DxColour& colour);
		void Draw(const DxTexture* texture, const DxRect& source, const DxRect& destination, const DxColour& colour);
		void Draw(const DxTexture* texture, const DxVector2& position, const DxColour& colour, const DxVector2& origin, float scale, float angle, float depth);
		void Draw(const DxTexture* texture, const DxRect& destination, const DxColour& colour, const DxVector2& origin, float scale, float angle, float depth);
		void Draw(const DxTexture* texture, const DxRect& source, const DxVector2& position, const DxColour& colour, const DxVector2& origin, float scale, float angle, float depth);
		void Draw(const DxTexture* texture, const DxRect& source, const DxRect& destination, const DxColour& colour, const DxVector2& origin, float scale, float angle, float depth);
		
		void DrawText(const DxFont* font, const LPCSTR text, int x, int y, const unsigned int& colour);
		void DrawText(const DxFont* font, const LPCSTR text, int x, int y, const DxColour& colour);
		void DrawText(const DxFont& font, const LPCSTR text, int x, int y, const unsigned int& colour);
		void DrawText(const DxFont& font, const LPCSTR text, int x, int y, const DxColour& colour);
		
		void DrawText(const DxFont* font, const std::string text, const DxVector2& pos, const DxColour& colour);

	// member variables
	private:
		static DxSprite*	_instance;
		static LPD3DXSPRITE _sprite;
		static RECT			_fontPos;
		
		static D3DXMATRIX	_transform;
		static bool			_isDrawing;
};

#endif