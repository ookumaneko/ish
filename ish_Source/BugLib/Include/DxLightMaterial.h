#ifndef _DX_LIGHT_AND_MATERIAL_
#define _DX_LIGHT_AND_MATERIAL_

#include "DxLibraryDef.h"
#include "D3D9.h"

class DxColour;
class DxVector3;

class DxLight
{
	// light type enum
	public:
		static enum LightType
		{
			POINT = 1,
			SPOT,
			DIRECTIONAL,
		};

	// constructor and destructor
	public:
		DxLight(LightType type);
		~DxLight(void);

	// Accessor methods
	public:
		void SetDiffuse	( float r, float g, float b );
		void SetDiffuse	( DxColour& col );
		void SetAmbient	( float r, float g, float b );
		void SetAmbient	( DxColour& col );
		void SetSpecular( float r, float g, float b );   

		void SetPosition( float x, float y, float z );
		void SetPosition( DxVector3& pos );
 
		void SetDirection		( float x, float y, float z );
		void SetDirection		( DxVector3& dir );
		
		const DxVector3& GetDirection(void) const;

		void SetRange			(float range)	{ _light.Range = range; }
		void SetFalloff			(float falloff) { _light.Falloff = falloff; }
		
		void SetAttenuation0	(float att)		{ _light.Attenuation0 = att; }
		void SetAttenuation1	(float att)		{ _light.Attenuation1 = att; }
		void SetAttenuation2	(float att)		{ _light.Attenuation2 = att; }
		void SetTheta			(float theta)	{ _light.Theta = theta; }
		void SetPhi				(float phi)		{ _light.Phi = phi; }

		// Sets everything to zero
		void Clear(void); 
		const D3DLIGHT9& GetLight(void) const { return _light; }

		// Normalize the light direction
		void Normalize(void);

	protected:
		D3DLIGHT9	_light;

};

class DxMaterial
{
	// constructor and destructor
	public:
		DxMaterial( void );

	// Accessors
	public:
		const D3DMATERIAL9& GetMaterial(void) const { return _mtr; }

	// material Settings
	public:	
		void SetDiffuse( float r, float g, float b );	
		void SetDiffuse( DxColour& col );

		void SetAmbient( float r, float g, float b );
		void SetAmbient( DxColour& col );

		void SetSpecular( float r, float g, float b );
		void SetSpecular( DxColour& col );

		void SetEmissive( float r, float g, float b );    
		void SetEmissive( DxColour& col );

		void SetPower( float power );

		void Clear( void );

	// member variables
	protected:
		D3DMATERIAL9 _mtr;
};

#endif