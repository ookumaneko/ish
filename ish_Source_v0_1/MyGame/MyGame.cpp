#include "MyGame.h"
#include <DxColour.h>
#include <DxResourceManager.h>
#include <ISH.h>
using namespace ish;

MyGame::MyGame(void) : DxGame(), _position( 300.0f, 300.0f ), _lastInput( "Last Input = Nothing" )
{
}

MyGame::~MyGame(void)
{
	ISH::Shutdown();
}

void MyGame::Initialize(HINSTANCE hInstance)
{
	// set screen resolution
	_screenWidth  = 800;
	_screenHeight = 600;
	
	// initialize base class
	LimitFPS( false, 60.0f );
	DxGame::Initialize( hInstance, "ISH Test" );

	// load textures
	_playerTex = DxResourceManager::LoadTexture( "Images/Player.png", "player" );
	_particleTex = DxResourceManager::LoadTexture( "Images/particle.png", "particle" );

	_font = DxResourceManager::LoadFont( "Arial", "arial" );

	// get directory for another key config file
	GetCurrentDirectoryA( MAX_PATH, _kinslayerFile );
	lstrcatA( _kinslayerFile, "\\kinslayer.ini" );

	// initialize input system and load key config data
	// from current directory
	//bool success = ISH::Initialize( _kinslayerFile, PlayerOne );
	bool success = ISH::Initialize( );
}

void MyGame::Update(float delta)
{
	float speed = 120.0f;

	// update input system, this must be called once per frame
	ISH::Update();
	
	// if Z key and X key is pressed or escape key is pressed, exit the app
	//-- current problem: you can't have AND and OR in a single group--// 
	if ( ISH::GetInputValue( "Exit" ) || ISH::GetInputValue( "Quit", PlayerOne ) )
	{
		this->Exit();
	}

	// move player
	float dx = ISH::GetInputValue( "MoveX", PlayerOne );
	float dy = ISH::GetInputValue( "MoveY", PlayerOne );
	dx *= speed * delta;
	dy *= speed * delta;
	_position += DxVector2( dx, dy );

	// emit particles
	if ( ISH::GetInputValue( "Particle" ) )
	{
		_emitter.Emit( PT_SPREAD, _particleTex, _position, 360, 0.5f, 0.2f, 4.0f, 0.0f, 100, 8000, 1.0f, DxColour::Gold, DxVector2::ZERO );
	}

	// load new key config setting
	if ( ISH::GetInputValue( "Reload" ) )
	{
		// (you should be able to emit particles with A on 360 pad or Enter key when loaded succesfully)
		if ( ISH::LoadKeyData( _kinslayerFile, PlayerOne ) )
		{
			_emitter.Emit( PT_SPREAD, _particleTex, _position, 360, 0.5f, 0.2f, 4.0f, 0.0f, 100, 8000, 1.0f, DxColour::Purple, DxVector2::ZERO );
		}
		else
		{
			_emitter.Emit( PT_SPREAD, _particleTex, _position, 360, 0.5f, 0.2f, 4.0f, 0.0f, 100, 8000, 1.0f, DxColour::Cyan, DxVector2::ZERO );
		}
	}

	// check for latest input, this method is mainly to be used to set key mapping at runtime. 
	std::string input = ISH::SetInput( _kinslayerFile, "InTest", IsDown, PlayerOne, true, SaveAdd );
	if ( input != "" )
	{
		_lastInput = "Last Input = " + input;
	}

	// update particles
	_emitter.Update( delta );
	
	// update base
	DxGame::Update( delta );
}

void MyGame::Draw(float delta)
{
	_renderer->Clear( DxColour::Black );
	_renderer->Begin();
	_sprite->Begin( _sprite->AlphaBlend );

	// draw textures
	_sprite->Draw( _playerTex, _position, DxColour::White );
	_emitter.Draw( _sprite );

	// draw text
	_sprite->DrawText( _font, _lastInput.c_str(), 10, 10, DxColour::White );
	
	_sprite->End();
	_renderer->End();
}
