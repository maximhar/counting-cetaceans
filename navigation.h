/* 
 * File:   navigation.h
 * Author: dap
 *
 * Created on 11 November 2011, 10:21
 */

#define MINLAT 52.0
#define MAXLAT 52.833
#define MAXLNG -4.0
#define MINLNG -5.5

#ifndef NAVIGATION_H
#define	NAVIGATION_H
/* 
 * This structure is used to represent a location.
 * The two members are doubles representing the latitude and longitude
 * of the location in degrees.
 */
typedef struct {
    double lat;
    double lng;
} location;

/* The great_circle function takes two struct parameters
 * and returns a double.
 * The first struct parameter represents one location.
 * The second struct parameter represents a second location.
 * The great_circle function returns the number of nautical miles
 * between two locations as a double.
 */
/*add up two locations*/
location sum (location a, location b);
double great_circle(location location_1, location location_2);
/*produce a location from a location, a bearing and a range*/
location offset_location(location origin, double bearing, double range);
/*determine whether the location is within the area we are interested in*/
int check_bounds(location loc);
/*determine if the locations are within the specified range of each other*/
int is_near(location loc1, location loc2, double range);
#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* NAVIGATION_H */

