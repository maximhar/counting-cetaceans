#include "sighting.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arraydefs.h"
#include "sighting_funs.h"


array_sighting read_sightings(char* path) {
    array_sighting arr = new_array_sighting();
    sighting temp_cet;
    
    FILE* file = fopen(path, "r");
    if(file == NULL) {
        perror("Error opening sightings file");
        arr.count = -1;
        return arr;
    }
    
    while(fscanf(file, "%s %c %lf %lf", temp_cet.id, &temp_cet.type, 
            &temp_cet.bearing, &temp_cet.range) == 4) {
        arr.add(&arr, temp_cet);
    }
    fclose(file);
    return arr;
}


