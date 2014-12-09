#ifndef SIGHTING_FUNS
#define SIGHTING_FUNS
#include "sighting.h"
#include "arraydefs.h"
#include "sighting_group.h"

/* read an array of sightings from a file */
array_sighting read_sightings(char* path);
/* print an array of sightings in a format appropriate for mission 1*/
void print_sightings(array_sighting *arr);
/* print an array of sighting groups in a format appropriate for mission 2*/
void print_sightings_2(array_sighting_group *arr);
/* print an array of pods in a format appropriate for mission 3*/
void print_pods(array_pod *arr);
/* convert a mammal type char to a descriptive string */
void mammal_str(char mammal, char* dest);
#endif