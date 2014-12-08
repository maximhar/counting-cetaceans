#include "navigation.h"
#include <math.h>

location offset_location(location origin, double bearing, double distance) {
    double bearing_r = bearing * M_PI / 180.0;
    double o_lat_r = origin.lat * M_PI / 180.0;
    double lat = origin.lat + (distance * cos(bearing_r)) / 60.0;
    double lng = origin.lng + (distance * sin(bearing_r) / cos(o_lat_r)) / 60.0;
    location loc = { lat, lng };
    return loc;
}

int check_bounds(location loc){
    return ((loc.lat >= MINLAT) && (loc.lat <= MAXLAT) && (loc.lng <= MAXLNG) && (loc.lng >= MINLNG));
}

int is_near(location loc1, location loc2, double range) {
    return great_circle(loc1, loc2) <= range;
}

location* add (location *a, location *b){
    a->lat += b->lat;
    a->lng += b->lng;
    return a;
}