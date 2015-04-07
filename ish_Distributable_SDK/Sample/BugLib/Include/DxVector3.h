#ifndef _DX_VECTOR_3_
#define _DX_VECTOR_3_

#include "DxLibraryDef.h"
#include <math.h>
#include <D3dx9math.h>

class DxMatrix;

class DxVector3
{
	//constructors
	public:
		DxVector3(void);
		DxVector3(float x, float y, float z);
		DxVector3(const D3DXVECTOR3& rhs);
		DxVector3(const DxVector3& lhs);
		~DxVector3(void);

	// operators
	public:
		DxVector3& operator=	(const DxVector3& rhs);
		DxVector3  operator+	(const DxVector3& rhs) const;
		DxVector3  operator-	(const DxVector3& rhs) const;
		DxVector3  operator*	(const float scalar) const;
		DxVector3& operator+=	(const DxVector3& rhs);
		DxVector3& operator-=	(const DxVector3& rhs);
		DxVector3& operator*=	(const float scalar);
		bool	 operator==	(const DxVector3& rhs);	
		bool	 operator!=	(const DxVector3& rhs);

	//Accessors
	public:
		float X			(void)		const;
		float Y			(void)		const;
		float Z			(void)		const;
		float& X		(void);	
		float& Y		(void);
		float& Z		(void);
		float GetX		(void)		const;
		float GetY		(void)		const;
		float GetZ		(void)		const;
		void  SetX		(float x);
		void  SetY		(float y);
		void  SetZ		(float z);
		void  SetValues	(float x, float y, float z);
		void  SetValues	(const D3DXVECTOR3& lhs);
		
		D3DXVECTOR3& GetVector(void);
		const D3DXVECTOR3& GetVector(void) const { return _vec; }

	//Arthemetic method
	public:
		void		Add				(const DxVector3& rhs);
		void		Add				(float scalar);
		void		Subtract		(const DxVector3& rhs);
		void		Subtract		(float scalar);
		void		Multiply		(const DxVector3& rhs);
		void		Multiply		(float scalar);
		void		Divide			(const DxVector3& rhs);
		void		Divide			(float scalar);
		float		DotProduct		(const DxVector3& rhs);
		DxVector3	CrossProduct	(const DxVector3& rhs, const DxVector3& rhs2);
		void		Normalize		(void);
		float		Magnitude		(void);
		void		TransformCoord	(const DxMatrix& m);
		void		Scale			(const float scalar);
		DxVector3	Transform		(const DxMatrix& mat);

	//static arthemetic methods
	public:
		static void Add				(const DxVector3& vec1, const DxVector3& vec2, DxVector3& out);
		static void Add				(float scalar, DxVector3& out);
		static void Subtract		(const DxVector3& vec1, const DxVector3& vec2, DxVector3& out);
		static void Subtract		(float scalar, DxVector3& out);
		static void Multiply		(const DxVector3& vec1, const DxVector3& vec2, DxVector3& out);
		static void Multiply		(float scalar, DxVector3& out);
		static void Divide			(const DxVector3& vec1, const DxVector3& vec2, DxVector3& out);
		static void Divide			(float scalar, DxVector3& out);
		static float DotProduct		(const DxVector3& vec1, const DxVector3& vec2);
		static void CrossProduct	(const DxVector3& vec1, const DxVector3& vec2, DxVector3& out);
		static void Normalize		(const DxVector3& in, DxVector3& out);
		static float Magnitude		(const DxVector3& rhs);
		static DxVector3 Zero		(void);
		static void Zero			(DxVector3& out);

		static DxVector3 Lerp		(DxVector3& start, DxVector3& end, float amount);
		static void Lerp			(DxVector3& start, DxVector3& end, float amount, DxVector3& out);

		static void Transform		(const DxMatrix& m, DxVector3& v, DxVector3& out);

		static DxVector3 Min		(const DxVector3& v1, const DxVector3& v2);
		static DxVector3 Max		(const DxVector3& v1, const DxVector3& v2);

		static const DxVector3 ZERO;
		static const DxVector3 ONE;

	//private members
	private:
		D3DXVECTOR3 _vec;
};

//#include "DxVector3.inl"

#endif