#ifndef PRINTING_H
#define	PRINTING_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "sighting.h"
#include "arraydefs.h"
#include "sighting_group.h"

/* print an array of sightings in a format appropriate for mission 1*/
void print_sightings(array_sighting *arr);
/* print an array of sighting groups in a format appropriate for mission 2*/
void print_sightings_2(array_sighting_group *arr);
/* print an array of pods in a format appropriate for mission 3*/
void print_pods(array_pod *arr);
/* convert a mammal type char to a descriptive string */
void mammal_str(char mammal, char* dest);
#ifdef	__cplusplus
}
#endif

#endif	/* PRINTING_H */

