#ifndef _DX_CAMERA
#define _DX_CAMERA

#include "DxSceneNode.h"
#include "DxStateMachine.h"
#include "DxVector3.h"
#include "DxMatrix.h"
#include "DxViewFrustum.h"

// different camera type/states
enum CameraType
{
	FirstPerson,
	ThirdPerson,
	Free,
	//Scripted,
};

class DxCamera : public DxSceneNode
{
	//Contructor and destructor
	public:
		DxCamera(std::string name, float speed, int sencitivity);
		virtual ~DxCamera(void);

	// Operators
	public:
		DxCamera&	operator =  (const DxCamera& rhs);
		bool		operator == (const DxCamera& rhs);
		bool		operator !=	(const DxCamera& rhs);

	//Accessors
	public:
		void  SetView	(const DxMatrix& view)	{ _view = view; }
		void  SetLookAt	(const DxVector3& look) { _look = look; } 

		const DxMatrix& GetView				(void) const;
		const DxMatrix& GetProjection		(void) const;
		const DxMatrix& GetViewProjection	(void) const;

		const DxVector3& GetRight			(void) const;
		const DxVector3& GetUp				(void) const;
		const DxVector3& GetLookAt			(void) const;

		void		SetPosition				(const DxVector3& pos);
		DxVector3&	GetPosition				(void);

		float GetSpeed						(void) const;
		void  SetSpeed						(float speed);

		const DxViewFrustum& GetFrustum(void) const { return _frustum; }
		DxViewFrustum&		 GetFrustum(void)		{ return _frustum; }

		void SetNodeToAttach	(DxSceneNode* toAttach);
		
		CameraType	GetType			(void) { return _states.GetCurrentState(); }
		void		SetType			(CameraType type);

	//Camera Methods
	public:
		void AddStates			(void);
		void CreateLookAt		(const DxVector3& pos, const DxVector3& target, const DxVector3& up);
		void BuildProjection	(float fov, float ratio, float nearZ, float farZ);
		void BuildViewMatrix	(void);

	//framework method
	protected:
		virtual bool	Initialize	(void);
		virtual void	Update		(float delta);
		virtual void	Draw		(float delta) {};		
		virtual bool	Shutdown	(void);

	//Scene node Events
	protected:
		virtual void	OnAdded		(void);
		virtual void	OnRemoved	(void) { _states.Clear(); }

	//members
	protected:
		DxStateMachine<CameraType>	_states;
		DxMatrix					_view;
		DxMatrix					_projection;
		DxMatrix					_viewProjection;

		DxViewFrustum				_frustum;
		DxVector3					_position;	// current position of the camera
		DxVector3					_right;
		DxVector3					_up;
		DxVector3					_look;		// where you are facing

		float						_speed;
		int							_sencitivity;
};

#endif