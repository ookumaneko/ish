///////////////////////////////////////////////////////////////////
//-------------------------Constructors--------------------------//
///////////////////////////////////////////////////////////////////

template <class T>
DxState<T>::DxState(void)
{
	_type = (T)0;
	_nextState = _type;
}

template <class T>
DxState<T>::DxState(T type)
{
	_type = type;
	_nextState = _type;
}

template <class T>
DxState<T>::~DxState(void)
{
}

template <class T>
bool DxState<T>::OnBegin()
{
	_nextState = _type;

	return true;
}
