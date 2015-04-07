#ifndef _DX_GAME_STATE
#define _DX_GAME_STATE

#include "DxState.h"
#include "DxRenderer.h"
#include "DxSprite.h"
#include "DxTexture.h"
#include "DxVector2.h"

class DxGrid;

template <class T>
class DxGameState : public DxState<T>
{
	// Constructor and destructor
	public:
		DxGameState<T>				(void);
		DxGameState<T>				(T type);
		virtual ~DxGameState<T>		(void);

	// state methods
	public:
		virtual bool	OnBegin	(void);									// Called when the state begins
		virtual T		Update	(float delta)	{ return _type; }		// Called every update
		virtual T		Draw	(float delta)	{ return _type; }		// Called every Draw
		virtual bool	OnEnd	(void)			{ return true; }		// Called when the state ends

	// member variable
	protected:
		DxRenderer*			_renderer;
		DxSprite*			_sprite;
		IDirect3DDevice9*	_graphics;
};

#include "DxGameState.inl"

#endif