
#ifndef SIGHTINGS
#define SIGHTINGS
#include "navigation.h"

typedef struct {
    char id[20];
    char type;
    double bearing;
    double range;
    /* this is only set after mission1 does its job, initially undefined*/
    location loc;
} sighting;
   
#endif