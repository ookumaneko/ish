#ifndef _DX_STATE
#define _DX_STATE
#include "DxUtil.h"

template <class T>
class DxState
{
	// constructor
	public:
		DxState<T>			(void);
		DxState<T>			(T type);
		virtual ~DxState<T>	(void);

	// state methods
	public:
		T				GetType	(void) const	{ return _type; }
		virtual bool	OnBegin	(void);									// Called when the state begins
		virtual T		Update	(float delta)	{ return _type; }		// Called every update
		virtual T		Draw	(float delta)	{ return _type; }		// Called every update
		virtual bool	OnEnd	(void)			{ return true; }		// Called when the state ends

		void			SetNextState(T type)	{ _nextState = type; }

	// member variables
	protected:
		T					_type;
		T					_nextState;
};

#include "DxState.inl"

#endif 