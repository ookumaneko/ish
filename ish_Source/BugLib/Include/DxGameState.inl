template <class T>
DxGameState<T>::DxGameState(void) : DxState<T>()
{
}

template <class T>
DxGameState<T>::DxGameState(T type) : DxState<T>(type)
{
	_renderer = DxRenderer::GetInstance();
	_graphics = _renderer->GetDevice();
}

template <class T>
DxGameState<T>::~DxGameState(void)
{
}

template <class T>
bool DxGameState<T>::OnBegin()
{
	DxState<T>::OnBegin();
	return true;
}
