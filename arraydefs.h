
#ifndef ARRAYDEF
#define	ARRAYDEF

#ifdef	__cplusplus
extern "C" {
#endif
    
    
#include "observer.h"
#include "sighting.h"
    
#define ARR_TYPE observer
#include "array.h"
#undef ARR_TYPE

#define ARR_TYPE sighting
#include "array.h"
#undef ARR_TYPE
    
typedef array_sighting pod;

#define ARR_TYPE pod 
#include "array.h"
#undef ARR_TYPE


#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

