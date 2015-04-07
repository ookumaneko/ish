#ifndef _MATHS_HEAD
#define _MATHS_HEAD

#include <D3dx9math.h>
#include "DxVector3.h"

namespace DxMaths
{
	const float INFINITY = FLT_MAX;
	const float EPSILON	 = 0.001f;
	const float PI		 = D3DX_PI;
	const float PI_OVER2 = PI / 2;
	const float PI_OVER4 = PI / 4;

	//---clamping methods---//
	int		Clamp	(int x, int min, int max);
	float	Clamp	(float x, float min, float max);

	inline bool Equals(float lhs, float rhs)
	{
		return fabs( lhs - rhs ) < EPSILON ? true : false;
	}

	inline float ToDegree(float radian)
	{
		return D3DXToDegree( radian );
	}

	inline float ToRadian(float degree)  
	{  
		return D3DXToRadian( degree ); //( degree / 180.0f * D3DX_PI );  
	}

	inline float Lerp(float start, float end, float amount)
	{
		return ( ( start * (1 - amount) ) + (end * amount) );
	}
	

	//-----------------------------------------------//
	//----------------Random  functions--------------//
	//-----------------------------------------------//


	inline DWORD FloatToDWORD(float in)
	{
		return *( (DWORD*)&in );
	}

	inline float RandFloat(float min, float max)
	{
		return min + (max - min) * ( (float)rand()) / ((float)RAND_MAX );
	}

	inline D3DXVECTOR3 GetRandomVector(D3DXVECTOR3& min, D3DXVECTOR3& max)
	{
		return D3DXVECTOR3( DxMaths::RandFloat( min.x, max.x ), DxMaths::RandFloat( min.y, max.y ), DxMaths::RandFloat( min.z, max.z ) );
	}

	inline void GetRandomVector(D3DXVECTOR3& min, D3DXVECTOR3& max, D3DXVECTOR3& out)
	{
		out.x = DxMaths::RandFloat( min.x, max.x );
		out.y = DxMaths::RandFloat( min.y, max.y );
		out.z = DxMaths::RandFloat( min.z, max.z );
	}

	inline DxVector3 GetRandomVector(DxVector3& min, DxVector3& max)
	{
		return DxVector3( DxMaths::RandFloat( min.X(), max.X() ), DxMaths::RandFloat( min.Y(), max.Y() ), DxMaths::RandFloat( min.Z(), max.Z() ) );
	}

	inline void GetRandomVector(DxVector3& min, DxVector3& max, DxVector3& out)
	{
		out.SetValues( DxMaths::RandFloat( min.X(), max.X() ), DxMaths::RandFloat( min.Y(), max.Y() ), DxMaths::RandFloat( min.Z(), max.Z() ) );
	}
}

#endif
