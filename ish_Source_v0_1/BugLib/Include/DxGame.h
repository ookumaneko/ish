//=============================================================================
// DxGame.h by Frank Luna (C) 2005 All Rights Reserved.
//
// Contains the base Direct3D application class which provides the
// framework interface for the sample applications.  Clients are to derive 
// from DxGame, override the framework methods, and instantiate only a single
// instance of the derived DxGame class.  At the same time, the client should
// set the global application  pointer (gGame) to point to the one and only
// instance, e.g., gGame = new HelloGame(hInstance);
// 
//=============================================================================

#ifndef Game_H
#define Game_H

#include "DxUtil.h"
#include <string>
#include "DxRenderer.h"
#include "DxInput.h"
#include "DxStateMachine.h"
#include "DxState.h"
#include "DxGameState.h"
#include "DxMaths.h"
#include "DxSprite.h"
#include "DxTexture.h"

class DxRenderer;
class DxSprite;

class DxGame
{
	// constructor and destructor
	public:
		DxGame();
		DxGame(HINSTANCE hInstance, std::string winCaption);
	
	public:
		virtual ~DxGame();

	// Accessors
	public:
		static DxGame* GetInstance (void);
		
		HINSTANCE	 GetHInstance		(void);
		HWND		 GetHWnd			(void);
		int			 GetScreenHeight	(void) const;
		int			 GetScreenWidth		(void) const;
		const RECT&  GetBounds			(void) const { return _bounds; }

	// device checks
	public:
		virtual bool CheckDeviceCaps	(void)			{ return true; }
		virtual void OnLostDevice		(void)			{}
		virtual void OnResetDevice		(void)			{}
		bool IsDeviceLost				(void);

	// Framework Methods
	public:
		virtual void Update				(float delta);
		virtual void Draw				(float delta);
		virtual void Initialize			(HINSTANCE hInstance, std::string winCaption);
		virtual void ShutDown			(void);
		void		 Exit				(void);

	// Windows initialization and game loop method
	public:
		virtual void InitWindow			(void);
		virtual int	 Run				(void);
		virtual LRESULT msgProc			(UINT msg, WPARAM wParam, LPARAM lParam);

		void LimitFPS					(bool enable, float fps);
		
		virtual void Activate	(void){ _isPaused = false; }
		virtual void DeActivate	(void){ _isPaused = true; }

	// member variables
	protected:
		std::string				_title;
		static DxGame*			_instance;
		float					_fps;
		int						_screenWidth;
		int						_screenHeight;
		HINSTANCE				_hInstance;
		HWND					_hWnd;
		bool					_isPaused;
		bool					_isActive;
		bool					_isLimitFPS;
		RECT					_bounds;

		// graphic managers
		DxRenderer*				_renderer;
		IDirect3DDevice9*		_graphics;
		DxSprite*				_sprite;
};


#endif // Game_H