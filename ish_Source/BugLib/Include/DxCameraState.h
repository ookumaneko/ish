#ifndef _DX_CAMERA_STATE_
#define _DX_CAMERA_STATE_

#include "dxstate.h"
#include "DxMatrix.h"
#include "DxVector3.h"

enum CameraType;
class DxCamera;
class DxSceneNode;

// base camera state class
class DxCameraState : public DxState<CameraType>
{
	// constructor and destructor
	public:
		DxCameraState(DxCamera* camera, CameraType type);
		virtual ~DxCameraState(void) {};

	// Accessors
	public:
		const DxMatrix& GetView			(void) const			{ return _view; }
		void SetNode					(DxSceneNode* toAttach); // { _nodeAttached = toAttach; } 
		void SetPosition				(const DxVector3& pos)	{ _position = pos; }
		
		const DxVector3& GetPosition	(void) const { return _position; }
	
	// camera methods
	public:
		virtual void	BuildViewMatrix	(void);
		void CreateLookAt		(const DxVector3& pos, const DxVector3& target, const DxVector3& up);

	// framework method
	public:
		virtual CameraType Update (float delta);

	// member variables
	protected:
		DxCamera*	_camera;
		DxMatrix	_view;
		DxVector3	_position;	// current position of the camera
		DxVector3	_right;
		DxVector3	_up;
		DxVector3	_look;		// where you are facing
		DxSceneNode* _nodeAttached;
};

class DxFirstPersonCameraState : public DxCameraState
{
	// constructor
	public:
		DxFirstPersonCameraState	(DxCamera* camera, DxSceneNode* toAttach = 0);
		~DxFirstPersonCameraState	(void);

	// state methods
	public:
		bool		OnBegin	(void)			{ return true; }		// Called when the state begins
		CameraType	Update	(float delta);							// Called every update
		bool		OnEnd	(void)			{ return true; }		// Called when the state ends

	
	public:
		void BuildViewMatrix	(void) {};
};


class DxThirdPersonCameraState : public DxCameraState
{
	// constructor and destructor
	public:
		DxThirdPersonCameraState	(DxCamera* camera, DxSceneNode* toAttach = 0);
		~DxThirdPersonCameraState	(void);

	// state methods
	public:
		bool		OnBegin	(void)			{ return true; }		// Called when the state begins
		CameraType	Update	(float delta);							// Called every update
		bool		OnEnd	(void)			{ return true; }		// Called when the state ends

	
	// camera methods
	public:
		void BuildViewMatrix	(void) {};

	
	// member variables
	protected:
		float _angle;
		float _currentRadius;
		float _maxRadius;
		float _minRadius;
		float _elevation;

		// speeds
		float _rotateSpeed;
		float _zoomSpeed;
		float _elevateSpeed;
};


class DxFreeCameraState : public DxCameraState
{
	// constructor and destructor
	public:
		DxFreeCameraState	(DxCamera* camera, const DxVector3 &pos, const DxVector3 &target, const DxVector3 &up);
		~DxFreeCameraState	(void);

	// state methods
	public:
		bool		OnBegin	(void)			{ return true; }		// Called when the state begins
		CameraType	Update	(float delta);							// Called every update
		bool		OnEnd	(void)			{ return true; }		// Called when the state ends


	// member variables
	public:
		float	_speed;
		int		_sencitivity;
};

#endif