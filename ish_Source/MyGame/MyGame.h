#pragma once
#include <string>
#include <DxGame.h>
#include <DxVector2.h>
#include "ParticleEmitter.h"

class DxTexture;
class DxFont;

class MyGame : public DxGame
{
	public:
		MyGame(void);
		~MyGame(void);

		//--Overridden methods--//
		void Initialize	(HINSTANCE hInstance);
		void Update		(float delta);
		void Draw		(float delta);

	private:

		// members
		char			_kinslayerFile[MAX_PATH];

		DxTexture*		_playerTex;
		DxTexture*		_particleTex;
		DxVector2		_position;
		ParticleEmitter _emitter;

		std::string		_lastInput;
		DxFont*			_font;
};
