#ifndef _I_DEVICE_H
#define _I_DEVICE_H

#include "Singleton.h"
#include "LibDef.h"

namespace ish
{

// type is the derived class type, input is the type used to check input
template <class Type, class Input>
class DECLSPEC IDevice : public Singleton<Type>
{	
	public:
		IDevice() : Singleton(){};

		virtual void Initialize	(void) = 0;
		virtual void Update		(void) = 0;
		virtual void Shutdown	(void) = 0;

		virtual float IsDown	(Input ) = 0;
		virtual float IsUp		(Input ) = 0;
		virtual float IsPressed	(Input ) = 0;
		virtual float IsReleased(Input ) = 0;
};

} // end of namespace ish

#endif // end of _I_DEVICE_H