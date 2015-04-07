#ifndef _DX_MATRIX_
#define _DX_MATRIX_

#include "DxLibraryDef.h"
#include <D3dx9math.h>

class DxVector3;

class DxMatrix
{
	//constructors and destructor
	public:
		DxMatrix(void);
		DxMatrix(float m00, float m01, float m02, float m03, 
			   float m10, float m11, float m12, float m13, 
			   float m20, float m21, float m22, float m23,
			   float m30, float m31, float m32, float m33);

		DxMatrix(D3DXMATRIX& rhs);
		DxMatrix(const DxMatrix& rhs);
		~DxMatrix(void);

	//Accessors
	public:
		D3DXMATRIXA16& GetMatrix(void) { return _mat; }
		const D3DXMATRIXA16& GetMatrix(void) const { return _mat; }

	// Operators
	public:
		DxMatrix& operator=	(const DxMatrix& rhs);
		DxMatrix  operator+	(const DxMatrix& rhs) const;
		DxMatrix  operator-	(const DxMatrix& rhs) const;
		DxMatrix  operator*	(const float scalar) const;
		DxMatrix  operator*	(const DxMatrix& rhs) const;
		DxMatrix& operator+=	(const DxMatrix& rhs);
		DxMatrix& operator-=	(const DxMatrix& rhs);
		DxMatrix& operator*=	(const float scalar);
		DxMatrix& operator*=	(const DxMatrix& rhs);
		bool	 operator==	(const DxMatrix& rhs);	
		bool	 operator!=	(const DxMatrix& rhs);

		float&	operator ()	(unsigned int row, unsigned int col);
	// matrix calculation methods
	public:

		void Identity			(void);
		void Inverse			(void);

		void BuildPerspectiveFOV(float fov, float aspectRatio, float farZ, float nearZ);
		void BuildLookAt		(const DxVector3& eye, const DxVector3& lookAt, const DxVector3& up);

		void Multiply			(const DxMatrix& rhs);
		void MultiplyTranspose	(const DxMatrix& rhs);
		
		void RotationAxis		(DxVector3& axis, float angle);
		void RotateX			(float angle);
		void RotateY			(float angle);
		void RotateZ			(float angle);
		void RotateYawPitchRoll	(float yaw, float pitch, float roll);
		
		void Scale				(float sx, float sy, float sz);
		void Scale				(const DxVector3& scale);

		void Translate			(float tx, float ty, float tz);
		void Translate			(const DxVector3& trans);
		void SetTranslate		(const DxVector3& trans);

		void Transpose			(void);

	//static DxMatrix calculation methods
	public:

		static void Inverse					  (const DxMatrix& in, DxMatrix& out);
		static void Identity				  (DxMatrix& out);
		
		static void Multiply				  ( const DxMatrix& m1, const DxMatrix& m2, DxMatrix& out);
		static void MultiplyTranspose		  ( const DxMatrix& m1, const DxMatrix& m2, DxMatrix& out);

		static void BuildPerspectiveFOV		  ( float fov, float aspectRatio, float farZ, float nearZ, DxMatrix& out);
		static void BuildLookAt				  ( const DxVector3& eye, const DxVector3& lookAt, const DxVector3& up, DxMatrix& out);
		static void BuildRotationAxis		  ( DxVector3& axis, float angle, DxMatrix& out);
		static void BuildRotationX			  ( float angle, DxMatrix& out);
		static void BuildRotationY			  ( float angle, DxMatrix& out);
		static void BuildRotationZ			  ( float angle, DxMatrix& out);
		static void BuildRotationYawPitchRoll ( float yaw, float pitch, float roll, DxMatrix& out);
		static void BuildRotationYawPitchRoll ( DxVector3& rot, DxMatrix& out);

		static void BuildScale				  ( float sx, float sy, float sz, DxMatrix& out);
		static void BuildScale				  ( const DxVector3& scale, DxMatrix& out );

		static void BuildTranslate			  ( float tx, float ty, float tz, DxMatrix& out);
		static void BuildTranslate			  ( const DxVector3& trans, DxMatrix& out );
		static void Transpose				  ( DxMatrix& matrix);


	// static const matricies
	public:
		static const DxMatrix IDENTITY;
		static const DxMatrix ZERO;

	// member variables
	private:
		D3DXMATRIXA16 _mat;

};

#endif