// This class is based on Scott Bilas' singleton class from
// Game Programming Gems (2000), chapter 1.3, Automatic Single Utility

#ifndef _SINGLETON_H
#define _SINGLETON_H

#include <cassert>

namespace ish
{

template <typename T> class Singleton
{

	public:

		Singleton( void )
		{
			assert( !_singleton );
			int offset = (int)(T*)1 - (int)( Singleton <T>* )(T*)1;
			_singleton = (T*)( (int)this + offset );
		}

	   virtual ~Singleton( void ) {  assert( _singleton );  _singleton = 0;  }

		// Accessors
		static T& GetInstance	( void ) {  assert( _singleton );  return ( *_singleton );  }

		static T* GetInstancePtr( void ) 
		{  
			assert( _singleton ); 
			return ( _singleton );  
		}

	private:
		static T* _singleton;

};

template <typename T> T* Singleton <T>::_singleton = 0;

} // end of namespace ish

#endif // end of _SINGLETON_H