#include "ParticleEmitter.h"
#include "DxSprite.h"
#include "DxTexture.h"
#include "DxResourceManager.h"

//--------------------------------------//
//-----------Particle Class-------------//
//--------------------------------------//


//---Constructor and Destructors---//

Particle::Particle(DxTexture *tex, const DxVector2 &pos, const DxVector2 &speed, float angle, 
				   float alphaDecrease, float scale, float shrinkRate, float duration, 
				   float depth, const DxColour &col, const DxVector2& origin)
{
	_origin				= origin;
	_depth				= depth;
	_texture			= tex;
	_position			= pos;
	_speed				= speed;
	_scale				= scale;
	_shrinkRate			= shrinkRate;
	_isActive			= true;
	_alphaDecrease		= alphaDecrease;
	_duration			= duration;
	_colour				= col;
	_velocity			= DxVector2( DxMaths::ToRadian( cosf( angle ) ) * speed.X(), DxMaths::ToRadian( sinf( angle ) ) * speed.Y() );
}

Particle::Particle(const Particle &rhs)
{
	_origin				= rhs._origin;
	_depth				= rhs._depth;
	_texture			= rhs._texture;
	_position			= rhs._position;
	_speed				= rhs._speed;
	_scale				= rhs._scale;
	_shrinkRate			= rhs._shrinkRate;
	_isActive			= rhs._isActive;
	_alphaDecrease		= rhs._alphaDecrease;
	_duration			= rhs._duration;
	_colour				= rhs._colour;
	_velocity			= rhs._velocity;
}


Particle::~Particle()
{
}

//------Operator Overload-------//

Particle& Particle::operator =(const Particle &rhs)
{	
	_origin				= rhs._origin;
	_depth				= rhs._depth;
	_texture			= rhs._texture;
	_position			= rhs._position;
	_speed				= rhs._speed;
	_scale				= rhs._scale;
	_shrinkRate			= rhs._shrinkRate;
	_isActive			= rhs._isActive;
	_alphaDecrease		= rhs._alphaDecrease;
	_duration			= rhs._duration;
	_colour				= rhs._colour;
	_velocity			= rhs._velocity;
	return *this;
}

//-------Routine Methods-------//

void Particle::Update(float delta)
{
	// move
    _position += _velocity * delta;

	// shurink
    _scale -= _shrinkRate * delta;

	// decrease life time
    _duration -= delta;

	// decrease alpha value
	//_colour._col.a -= _alphaDecrease * delta;

	// kill particle if its transparent, too small or lived its life span
    if ( _scale <= 0 || _duration <= 0.0f ) //_colour._col.a <= 0.0f || 
    {
        _isActive = false;
    }
}

void Particle::Draw(DxSprite* sp)
{
	sp->Draw( _texture, _position, _colour, _origin, _scale, 0.0f, _depth ); 
}

//--------------------------------------//
//--------Particle Emitter Class--------//
//--------------------------------------//


//--Constructor and Destructor--//

ParticleEmitter::ParticleEmitter(void)
{
}

ParticleEmitter::~ParticleEmitter(void)
{
	_particles.clear();
}


//-----Management Methods---//

void ParticleEmitter::Clear()
{
	_particles.clear();
}

void ParticleEmitter::Emit(ParticleType type, DxTexture *tex, const DxVector2 &pos, int angleRange,
						   float scale, float shrinkRate, float duration, float alphaDecrease, 
						   int amount, int maxSpeed, float depth, const DxColour &colour, const DxVector2& origin)
{
	float angle = 0;
	DxVector2 sp;

	for ( int i = 0; i < amount; i++ )
	{
		// calculate random angle
		angle = DxMaths::RandFloat( 0, angleRange );
		
		// calculate its velocity
		if ( type == PT_CIRCLE )
		{
			sp = DxVector2( maxSpeed, maxSpeed );
		}
		else if ( type == PT_SPREAD )
		{
			sp = DxVector2( DxMaths::RandFloat( -maxSpeed, maxSpeed ), DxMaths::RandFloat( -maxSpeed, maxSpeed ) );
		}

		// add particle
		_particles.push_back( Particle( tex, pos, sp, angle, alphaDecrease, scale, shrinkRate, duration, depth, colour, origin ) );
	}
}


//-----Routine Methods----//

void ParticleEmitter::Update(float delta)
{
	std::vector<Particle>::iterator i = _particles.begin();

	// update particles
	while ( i != _particles.end() )
	{
		(*i).Update( delta );

		// remove this particle if its dead
		if ( !(*i)._isActive )
		{
			// remove this particle
			i = _particles.erase( i );
			if ( _particles.size() == 0 || i == _particles.end() )
			{
				break;
			}
		}

		++i;
	}
}

void ParticleEmitter::Draw(DxSprite *sp)
{
	int size = _particles.size();
	for ( int i = 0; i < size; ++i )
	{
		_particles[i].Draw( sp );
	}
}
