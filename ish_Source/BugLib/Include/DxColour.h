#ifndef _DX_COLOUR_
#define _DX_COLOUR_

#include "DxLibraryDef.h"
#include <D3dx9math.h>

class DxColour
{
	//constructors and destructor
	public:
		DxColour(void);
		DxColour(int r, int g, int b);
		DxColour(int r, int g, int b, int a);
		DxColour(float r, float g, float b, float a);
		DxColour(DWORD colour);
		DxColour(const D3DXCOLOR& col);
		DxColour(const DxColour& col);
		~DxColour(void);

	// const colour values
	public:		
		static enum Colours
		{
			Black			= 0xff000000,
			White			= 0xffffffff,
			Red				= 0xFFFF0000,
			Green			= 0xff00ff00,
			Blue			= 0xff0000ff,
			Yellow			= 0xffffff00,
			YellowGreen		= 0xff9ACD32,
			Cyan			= 0xff00ffff,
			Crimson			= 0xffDC143C,
			CadetBlue		= 0xff5F9EA0,
			CornflowerBlue	= 0xff6495ED,
			Gold			= 0xffFFD700,
			Magneta			= 0xffff00ff,
			LightBlue		= 0xffADD8FF,
			LightCoral		= 0xffF08080,
			LightCyan		= 0xffE0FFFF,
			LightGoldenrodYellow = 0xffFAFAD2,
			LightGray		= 0xFFD3D3D3,
			LightGreen		= 0xFF90EE90,
			LightPink		= 0xFFFFB6C1,
			LightSkyBlue	= 0xFF87CEFA,
			LightYellow		= 0xFFFFFFE0,
			LightYellowGreen = 0xFF7CC576,
			LimeGreen		= 0xFF32CD32,
			Orange			= 0xFFFFA500,
			OrangeRed		= 0xFFFF4500,
			Purple			= 0xFF800080,
			Silver			= 0xFFC0C0C0,
			Violet			= 0xFFEE82EE,
			DarkBlue		= 0xFF00008B,
			DarkCyan		= 0xFF008B8B,
			DarkGray		= 0xFFA9A9A9,
			DarkGreen		= 0xFF006400,
			DarkYellowGreen = 0xFF197B30,
			Gray			= 0xFF808080,
			Brown			= 0xFFA52A2A,
			DarkBrown		= 0xFF736457,
			LightBrown		= 0xFFC69C6D,
			BeachSand		= 0xFFFFF99D,
			DesertSand		= 0xFFFACD87,
			TransparentBlack = 0x00000000,
		};

		// operators
		DxColour& operator =	(const DxColour& rhs);
		bool	  operator ==	(const DxColour& rhs);
		bool	  operator !=	(const DxColour& rhs);
		DxColour  operator+		(const DxColour& rhs) const;
		DxColour  operator-		(const DxColour& rhs) const;
		//DxColour  operator*		(const DxColour& rhs) const;
		//DxColour  operator/		(const DxColour& rhs) const;
		DxColour& operator+=	(const DxColour& rhs);
		DxColour& operator-=	(const DxColour& rhs);
		DxColour& operator*=	(const DxColour& rhs);
		DxColour& operator/=	(const DxColour& rhs);

	// Accessors
	public:
		D3DXCOLOR& GetColour(void) { return _col; }
		const D3DXCOLOR& GetColour(void) const { return _col; } 

	// member variable
	private:
		D3DXCOLOR _col;
};

#endif