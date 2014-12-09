#include "observer.h"
#include "navigation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arraydefs.h"
#include "observer_funs.h"

array_observer read_observers(char* path) {
    array_observer arr = new_array_observer();
    observer temp_ob;
    datetime ts;
    
    FILE* file = fopen(path, "r");
    if(file == NULL) {
        perror("Error opening observers file");
        arr.count = -1;
        return arr;
    }
    int c_ts = fscanf(file, " %hd %hd %hd %hd %hd %hd", &ts.day, &ts.month, &ts.year, 
                &ts.hour, &ts.minute, &ts.second);
    if(c_ts != 6) {
        perror("Unexpected observers format");
        arr.count = -1;
        fclose(file);
        return arr;
    }
    while(fscanf(file, "%s %lf %lf", temp_ob.id, &temp_ob.loc.lat, &temp_ob.loc.lng) == 3) {
        arr.add(&arr, temp_ob);
    }
    fclose(file);
    return arr;
}
