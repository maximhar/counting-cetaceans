#include "navigation.h"
#ifndef OBSERVER
#define OBSERVER
typedef struct {
    short day;
    short month;
    short year;
    short hour;
    short minute;
    short second;
} datetime;

typedef struct {
    char id[20];
    location loc;
} observer;

#endif
