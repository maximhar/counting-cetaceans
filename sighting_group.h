#include "sighting.h"
#include "sighting_funs.h"
#include "arraydefs.h"

#ifndef SIGHTING_GROUP_H
#define	SIGHTING_GROUP_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct sighting_group {
    sighting parent;
    array_sighting children;
} sighting_group;


#ifdef	__cplusplus
}
#endif

#endif	/* SIGHTING_GROUP_H */

