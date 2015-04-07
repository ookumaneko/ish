#pragma once
#include "DxVector2.h"
#include "DxColour.h"
#include <vector>

class DxTexture;
class DxSprite;

enum ParticleType
{
	PT_SPREAD = 0,
	PT_CIRCLE,
};

// a class that represents a single particle
class Particle
{
	private:

		//--Constructor and Destructor--//
		Particle(void){};
		
	public:
		Particle(DxTexture* tex, const DxVector2& pos, const DxVector2& speed, float angle, 
				 float alphaDecrease, float scale, float shrinkRate, float duration, 
				 float depth, const DxColour& col, const DxVector2& origin);
		Particle(const Particle& rhs);
		~Particle();

		//---Operator Overload--//
		Particle& operator =(const Particle& rhs);

		//---Routine Methods---//
		void Update	(float delta);
		void Draw	(DxSprite* sp);

		//---Member VAriables---//
		DxTexture*	_texture;
        DxColour	_colour;
		DxVector2	_position;
		DxVector2	_velocity;
		DxVector2	_speed;
		DxVector2	_origin;
		float		_duration;
        float		_scale;
        float		_shrinkRate;
        float		_alphaDecrease;
		float		_depth;
        bool		_isActive;
};

class ParticleEmitter
{
	public:
		
		//--Constructor and Destructor--//
		ParticleEmitter(void);
		virtual ~ParticleEmitter(void);

		//---Routine Methods---//
		virtual void Update	(float delta);
		virtual void Draw	(DxSprite* sp);

		//---Management Methods--//
		void Clear	(void);
		void Emit	(ParticleType type, DxTexture* tex, const DxVector2& pos, int angleRange, 
					 float scale, float shrinkRate, float duration, float alphaDecrease, 
					 int amount, int maxSpeed, float depth, const DxColour& colour, const DxVector2& origin);

		//---Member Variables---//
		std::vector<Particle>	_particles;
};
