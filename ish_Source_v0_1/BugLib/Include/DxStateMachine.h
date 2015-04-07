#ifndef _DX_STATE_MACHINE
#define _DX_STATE_MACHINE

#include "DxState.h"
#include "DxHashTable.h"

template <class T>
class DxStateMachine
{
	//constructor and destructor
	public:
		DxStateMachine<T>(void);
		virtual ~DxStateMachine<T>(void);

	//state methods
	public:
		bool AddState(T id, DxState<T>* state);
		bool SetState(T newState);
		void Clear(void);

		DxState<T>* GetState(T state);
		DxState<T>*	GetActiveState(void)		{ return _activeState; }
		const T&	GetCurrentState(void) const { return _currentState; }			

	// framework methods
	public:
		void Update	(float delta);
		void Draw	(float delta);

	//members
	protected:
		DxState<T>*						_activeState;
		DxHashTable<T, DxState<T>*>		_states;
		T								_currentState;
};

#include "DxStateMachine.inl"

#endif

