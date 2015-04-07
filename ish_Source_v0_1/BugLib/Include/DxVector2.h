#ifndef _DX_VECTOR_2
#define _DX_VECTOR_2

#include "DxLibraryDef.h"
#include <math.h>
#include <D3dx9math.h>

class DxVector2
{
	public:

		//-----Constructor and Destructor----//
		DxVector2	(void);									
		DxVector2	(float x, float y);						
		DxVector2	(const D3DXVECTOR2& rhs);
		DxVector2	(const DxVector2& rhs);					
		~DxVector2	(void);	

		//------operators Overloads------//
		DxVector2& operator=	(const DxVector2& rhs);			
		DxVector2  operator+	(const DxVector2& rhs) const;
		DxVector2  operator-	(const DxVector2& rhs) const;
		DxVector2  operator*	(const DxVector2& rhs) const;
		DxVector2  operator/	(const DxVector2& rhs) const;
		DxVector2  operator*	(const float scalar) const;
		DxVector2  operator/	(const float scalar) const;
		DxVector2& operator+=	(const DxVector2& rhs);
		DxVector2& operator-=	(const DxVector2& rhs);
		DxVector2& operator*=	(const DxVector2& rhs);
		DxVector2& operator/=	(const DxVector2& rhs);
		DxVector2& operator*=	(const float scalar);
		DxVector2& operator/=	(const float scalar);
		bool	 operator==		(const DxVector2& rhs);	
		bool	 operator!=		(const DxVector2& rhs);

		//-------Accessors (Get)---------//
		inline const float X(void) const { return _vec.x; }
		inline const float Y(void) const { return _vec.y; }
		inline float& X		(void)		 { return _vec.x; }
		inline float& Y		(void)		 { return _vec.y; }
		inline float GetX	(void) const { return _vec.x; }
		inline float GetY	(void) const { return _vec.y; }
		inline const D3DXVECTOR2& GetVector(void) const { return _vec; }

		//-------Accessors (Set)--------//
		inline void  X			(float value) { _vec.x = value; }
		inline void  Y			(float value) { _vec.y = value; }
		inline void SetX		(float value) { _vec.x = value; }
		inline void SetY		(float value) { _vec.y = value; }

		inline void SetValues	(float x, float y)			{ _vec.x = x; _vec.y = y; }
		inline void SetValues	(const D3DXVECTOR2& value)	{ _vec = value; }

		//-----Arithmetic operations------//
		void Add			(const DxVector2 &rhs);
		void Subtract		(const DxVector2 &rhs);
		void Multiply		(float scalar);
		void Divide			(float scalar);

		//-----other Vector operations----//
		float	Magnitude	(void);
		void	Normalize	(void);
		bool	Equals		(const DxVector2 &v) const;

		//--------Static Methods-----//
		static DxVector2 Zero		(void);
		static DxVector2 Lerp		(const DxVector2 &start, const DxVector2 &end, float amount);
		static float	 Distance	(const DxVector2 &lhs, const DxVector2 &rhs);
		static float	 DistanceSq	(const DxVector2 &lhs, const DxVector2 &rhs);

		//---Global Const Vectors----//
		static const DxVector2 ZERO;
		static const DxVector2 ONE;

	private:

		//----Member variables------//
		D3DXVECTOR2 _vec;
};

#endif
