#ifndef SIGHTING_FUNS
#define SIGHTING_FUNS
#include "sighting.h"
#include "arraydefs.h"
#include "sighting_group.h"

array_sighting read_sightings(char* path);
void print_sightings(array_sighting *arr);
void print_sightings_2(array_sighting_group *arr);
void print_pods(array_pod *arr);
void mammal_str(char mammal, char* dest);
#endif