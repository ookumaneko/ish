#ifndef _DX_RECT_
#define _DX_RECT_
#include "DxLibraryDef.h"

class DxRect
{
	// Contructors and destructor
	public:
		DxRect(void);
		DxRect(const DxRect& rect);
		DxRect(int x, int y, int width, int height);
		~DxRect(void);

	// Accessors
	public:
		int GetTop		(void) const { return Y; }
		int GetBottom	(void) const { return Y + Height; }
		int GetLeft		(void) const { return X; }
		int GetRight	(void) const { return X + Width; }

	// Operators
	public:
		DxRect& operator=  (const DxRect& rhs);
		bool	operator== (const DxRect& rhs) const;
		bool	operator!= (const DxRect& rhs) const;

	// Intersection & Collision methods
	public:
		bool Intersect	(const DxRect& other);

	// public Members
	public:
		int X, Y, Width, Height;


};

#endif