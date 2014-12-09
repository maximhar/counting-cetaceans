
#ifndef SIGHTINGS
#define SIGHTINGS
#include "navigation.h"

typedef struct {
    char id[20];
    char type;
    double bearing;
    double range;
    location loc;
} sighting;
   
#endif