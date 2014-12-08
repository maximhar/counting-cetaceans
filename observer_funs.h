#ifndef OBSERVER_FUNS
#define OBSERVER_FUNS
#include "observer.h"
#include "arraydefs.h"
array_observer read_observers(char* path);
observer* find_observer(char* id, array_observer* arr);
#endif