#ifndef _DX_PARTICLE_SYSTEM_
#define _DX_PARTICLE_SYSTEM_

#include <list>
#include <d3d9.h>
#include <d3dx9.h>
#include "DxVector3.h"
#include "DxShape.h"
#include "DxColour.h"

class DxTexture;

// abstruct class for particle emitter 
class DxParticleSystem
{
	// constructor and destructor
	public:
		DxParticleSystem(void);
		virtual ~DxParticleSystem(void);

	private:
		// particle data for rendering
		struct Particle
		{
			D3DXVECTOR3 _position;
			D3DCOLOR    _color;
			static const DWORD FVF;
		};

	protected:
		// attricutes for particles used for calculations
		struct Attribute
		{
			Attribute()
			{
				_lifeTime = 0.0f;
				_age      = 0.0f;
				_isAlive  = true;
			}

			DxVector3	_position;     
			DxVector3	_velocity;     
			DxVector3	_acceleration; 
			float       _lifeTime;     
			float       _age;      
			DxColour	_color;        
			DxColour	_colorFade; 
			bool        _isAlive;   
		};

	// Accessor
	public:
		void SetPosition(DxVector3& pos) { _origin = pos; }

	// Particle Controlling Methods
	public:
		virtual bool Initialize			(DxTexture* texture);
		virtual void Reset				(void);
		virtual void InitializeParticle	(Attribute& attribute) = 0;
		virtual void AddParticle		(void);

	// update and draw methods
	public:
		virtual void Update		(float delta) = 0;
		virtual void PreRender	(void);
		virtual void Render		(void);
		virtual void PostRender	(void);

		bool IsEmpty(void);
		bool IsDead	(void);

	// particle control method
	protected:
		virtual void RemoveDeadParticle(void);
		
	// member variables
	protected:
		DxVector3					_origin;	
		DxAABB						_boundingBox;
		float						_emitRate;  
		float						_size;      
		DxTexture*					_tex;
		IDirect3DVertexBuffer9*		_vb;
		std::list<Attribute>		_particles;
		int							_maxParticles; 
		DWORD						_vbSize;      // size of vb
		DWORD						_vbOffset;    // offset in vb to lock   
		DWORD						_vbBatchSize; // number of vertices to lock starting at _vbOffset
		bool						_hadLight;
};

#endif