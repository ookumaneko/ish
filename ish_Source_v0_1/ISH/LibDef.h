#ifndef _LIB_DEF_H
#define _LIB_DEF_H

#ifndef DECLSPEC

	#ifdef ISH_EXPORTS
		#define DECLSPEC __declspec(dllexport)  
	#else  
		#define DECLSPEC __declspec(dllimport)  
	#endif  //end ofISH

#endif //DECLSPEC

#pragma warning(disable:4251)  

#endif