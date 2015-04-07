#ifndef _DX_SHAPE_
#define _DX_SHAPE_

#include "DxUtil.h"
#include "DxVector3.h"
struct ID3DXMesh;
class DxMesh;
class DxMatrix;

 // Generic shape base class
class DxShape
{
	friend class DxViewFrustum;

	public:

		// bounding shape type for collision chack
		enum ShapeType
		{
			None = 0,
			Box,
			Sphere,
		};


	protected:

		// vertex structure to copute bounding shapes
		struct TEXTURED_VERTEX
		{
			D3DXVECTOR3 position; // The position
			D3DXVECTOR3 normal;	  // The normal
			D3DXVECTOR2 texUV;    // The color
		};

	// constructor and destructor
	public:
		DxShape() { _mesh = 0; _type = None; }
		virtual ~DxShape() {}
	
	public:

		// initialization
		virtual void				Initialize	(DxMesh* mesh) = 0;
		virtual bool				Create		(DxMesh* mesh) = 0;

		// Intersection testing
		virtual bool				IsIntersecting	(const DxShape* pShape) = 0;
		
		// common accessor routines for all shapes
		virtual DxVector3&			GetCenter	(void)	= 0;
		virtual void				GetCenter	(DxVector3& center)	= 0;
		virtual ShapeType			GetType		(void) const = 0;

		//framework methods
		virtual void				Update		(const DxMatrix& world) = 0;
		virtual void				Draw		(void) = 0;

	// memhbes
	protected:
		ID3DXMesh*	_mesh;
		ShapeType	_type;
};

// Sphere shape
class DxShapeSphere : public DxShape
{
	// constructor and destructor
	public:
		DxShapeSphere(void);
		DxShapeSphere(float radius);
		DxShapeSphere(const DxVector3& center, float radius);
		virtual ~DxShapeSphere(void);
		
		// initialization of the sphere
		void			Initialize	(DxMesh* mesh);
		bool			Create		(DxMesh* mesh);

		// Intersection testing
		bool			IsIntersecting	(const DxShape* pShape);

		// common accessor routines for all shapes
		inline DxVector3&		GetCenter		(void)				{ return _center; }
		inline const DxVector3&	GetCenter		(void) const		{ return _center; }		
		inline void				GetCenter		(DxVector3& center) { center = _center; }
		inline DxVector3&		GetWorldCenter	(void)				{ return _centerWorld; }
		inline const DxVector3&	GetWorldCenter	(void) const		{ return _centerWorld; }
		inline void				GetWorldCenter	(DxVector3& center)	{ center = _centerWorld; }

		inline void				SetCenter		(const DxVector3& center) { _center = center; _centerWorld = center; }
		inline void				SetWorldCenter	(const DxVector3& center) { _centerWorld = center; }

		inline float			GetRadius		(void) const	{ return _radius; }
		inline float&			GetRadius		(void)			{ return _radius; }
		inline void				SetRadius		(float radius)	{ _radius = radius; }

		inline ShapeType		GetType			(void) const	{ return Sphere; }

		// framework methods
		virtual void			Update	(const DxMatrix& world);
		virtual void			Draw	(void);

	// member variables
	private:
		DxVector3	_centerWorld;	// Center of the sphere after world transform
		DxVector3	_center;		// Center of the sphere
		float		_radius;		// Sphere radius
};



// Axis-Aligned Bounding Box shape
class DxAABB : public DxShape
{
	// constructor and destructor
	public:
		DxAABB(void);
		DxAABB(const DxVector3& minPos, const DxVector3& maxPos );
		virtual ~DxAABB();
		
		// initialization methods
		virtual void			Initialize			(DxMesh* mesh);
		virtual bool			Create				(DxMesh* mesh);

		// Intersection testing
		virtual bool			IsIntersecting		(const DxShape* pShape);
		virtual bool			IsPointInside		(const DxVector3& point);
		virtual bool			IsPointInsideWorld	(const DxVector3& point);
		virtual bool			Contains			(const DxAABB* pShape);

		// accessor methods
		inline DxVector3&		GetCenter			(void) { return ( _min + _max ) * 0.5f; }
		inline void				GetCenter			(DxVector3& center) { center = ( _min + _max ) * 0.5f; }

		inline void				GetMin	(DxVector3& out) { out = _min; }
		inline void				GetMax	(DxVector3& out) { out = _max; }
		inline DxVector3&		GetMin	(void)			 { return _min; }
		inline DxVector3&		GetMax	(void)			 { return _max; }
		inline const DxVector3&	GetMin	(void) const	 { return _min; }
		inline const DxVector3&	GetMax	(void) const	 { return _max; }

		inline void				GetWMin	(DxVector3& out) { out = _min; }
		inline void				GetWMax	(DxVector3& out) { out = _max; }
		inline DxVector3&		GetWMin	(void)			 { return _min; }
		inline DxVector3&		GetWMax	(void)			 { return _max; }
		inline const DxVector3&	GetWMin	(void) const	 { return _min; }
		inline const DxVector3&	GetWMax	(void) const	 { return _max; }

		inline float			GetWidth (void) const	{ return _width; }
		inline float&			GetWidth (void)			{ return _width; }
		inline float			GetHeight(void) const	{ return _height; }
		inline float&			GetHeight(void)			{ return _height; }
		inline float			GetDepth (void) const	{ return _depth; }
		inline float&			GetDepth (void)			{ return _depth; }

		inline ShapeType		GetType		(void) const { return Box; }
		float					GetPerimeter(void) const;

		inline bool				ZeroSize	 (void) { return ( _min == DxVector3::ZERO ); }
		inline bool				ZeroWorldSize(void) { return ( _wMin == DxVector3::ZERO ); }

		// framework methods
		virtual void			Update	(const DxMatrix& world);
		virtual void			Draw	(void);

		virtual void			Combine	(const DxAABB* other);
		virtual void			Combine	(const DxAABB* s1, const DxAABB* s2);
		virtual void			WorldCombine(const DxAABB* other);
		virtual void			WorldCombine(const DxAABB* s1, const DxAABB* s2);


	public:
		DxAABB& operator =(const DxAABB& rhs);

	// member variables
	protected:
		DxVector3 _min;
		DxVector3 _max;
		DxVector3 _wMin;
		DxVector3 _wMax;

		float _width;
		float _height;
		float _depth;
};




#endif