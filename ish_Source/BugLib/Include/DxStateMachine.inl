///////////////////////////////////////////////////////////////////
//-------------------------Constructors--------------------------//
///////////////////////////////////////////////////////////////////

template <class T> 
DxStateMachine<T>::DxStateMachine(void)
{
	_activeState = 0;
}

template <class T> 
DxStateMachine<T>::~DxStateMachine(void)
{
	Clear();
}

///////////////////////////////////////////////////////////////////
//--------------------State Management Methods-------------------//
///////////////////////////////////////////////////////////////////

template <class T> 
DxState<T>* DxStateMachine<T>::GetState(T state)
{
	return _states.GetValue( state );
}

template <class T> 
void DxStateMachine<T>::Clear()
{
	if ( _states.GetSize() > 0 )
		_states.Clear( true );
}

template <class T> 
bool DxStateMachine<T>::AddState(T id, DxState<T> *state)
{
	int count = _states.GetSize();
	_states.Add( id, state );
	
	if ( count == _states.GetSize() )
	{
		//error, could not add state
		return false;
	}

	//if there is no other states, set this one to the current state
	if ( !_activeState )
	{
		_activeState = state;
		_activeState->OnBegin();
		_currentState = id;
	}

	return true;
}

template <class T> 
bool DxStateMachine<T>::SetState(T newState)
{
	//search for the sent state
	DxState<T>* pState = _states.GetValue( newState );

	if ( pState == 0 )
	{
		//not found
		return false;
	}

	//end current state
	if ( !_activeState->OnEnd() )
	{
		//error - could not end state
		return false;
	}

	//start new state
	if ( !pState->OnBegin() )
	{
		//error - could not start new state
		return false;
	}

	//set new state
	_activeState = pState;
	_currentState = newState;

	return true;
}	

///////////////////////////////////////////////////////////////////
//----------------------Framework Methods------------------------//
///////////////////////////////////////////////////////////////////

template <class T> 
void DxStateMachine<T>::Update(float delta)
{
	if ( _activeState )
	{
		T newState = _activeState->Update(delta);
		if ( newState != _activeState->GetType() )
		{
			_activeState->SetNextState( _activeState->GetType() );
			SetState( newState );
		}
	}
}

template <class T> 
void DxStateMachine<T>::Draw(float delta)
{
	if ( _activeState )
	{
		T newState = _activeState->Draw(delta);
		if ( newState != _activeState->GetType() )
		{
			_activeState->SetNextState( _activeState->GetType() );
			SetState( newState );
		}
	}
}