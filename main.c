/* 
 * File:   main.c
 * Author: msh4
 *
 * Created on 14 November 2014, 16:32
 */
#define DEFINE_ARR
#include <stdio.h>
#include <stdlib.h>
#include "navigation.h"
#include "observer.h"
#include "sighting.h"
#include "sighting_funs.h"
#include "sighting_group.h"
#include "observer_funs.h"
#include "arraydefs.h"

#define MAMMAL_RANGE 0.02
#define POD_RANGE 0.1

int sighting_comp(sighting* s1, sighting* s2){
    return s1->id == s2->id && s1->type == s2->type &&
            s1->loc.lat == s2->loc.lat && s1->loc.lng == s2->loc.lng;
}

int id_obs_comp(void* id, observer* obs){
    return (!strcmp(id, obs->id));
}

void purge_outsiders(array_sighting* arr){
    int i;
    for(i = 0; i < arr->count; i++){
        if(!check_bounds(arr->at(arr, i)->loc)){
            arr->remove(arr, i);
            i--;
        }
    }
}

void mission1(array_observer* arr_o, array_sighting* arr_s) {
    int i = 0;
    for(i = 0; i < arr_s->count; i++) {
        sighting *c_sig = arr_s->at(arr_s,i);
        observer *obs = arr_o->find(arr_o, c_sig->id, &id_obs_comp);
        if(obs == NULL) continue;
        c_sig->loc = offset_location(obs->loc, 
                c_sig->bearing, c_sig->range);
    }
    purge_outsiders(arr_s);
    printf("\nMISSION 1\n");
    print_sightings(arr_s);
}

array_sighting_group mission2(array_sighting* arr){

    int i = 0, j = 0;
    array_sighting arr2 = arr->copy(arr);
    array_sighting_group grps = new_array_sighting_group();
    location avg;
    for(i = 0; i < arr->count; i++) {
        sighting *c_sig = arr->at(arr,i);
        sighting_group c_grp = { *c_sig, new_array_sighting() };
        avg.lat = avg.lng = 0;
        int avg_c = 0;
        for(j = 0; j < arr2.count; j++){
            sighting *o_sig = arr2.at(&arr2,j);
            if(is_near(c_sig->loc, o_sig->loc, MAMMAL_RANGE) 
                    && c_sig->type == o_sig->type){
                add(&avg, &o_sig->loc);
                c_grp.children.add(&c_grp.children, *o_sig);
                arr2.remove(&arr2, j);
                avg_c++;
                j--;
            }
        }
        c_grp.parent.loc.lat = avg.lat / (double)avg_c;
        c_grp.parent.loc.lng = avg.lng / (double)avg_c;
        if(c_grp.children.count > 0)
            grps.add(&grps, c_grp);
    }
    
    printf("\nMISSION 2\n");
    print_sightings_2(&grps);
    return grps;
}

void mission3(array_sighting_group* arr){
    
    int i = 0, j = 0;
    array_sighting_group arr2 = arr->copy(arr);
    array_pod pods = new_array_pod();
    for(i = 0; i < arr->count; i++) {
        sighting c_sig = arr->at(arr,i)->parent;
        pod c_pod = new_array_sighting();
        for(j = 0; j < arr2.count; j++){
            sighting o_sig = arr2.at(&arr2,j)->parent;
            if(is_near(c_sig.loc, o_sig.loc, POD_RANGE)){
                if(!c_pod.contains(&c_pod, &o_sig, &sighting_comp)) {
                    c_pod.add(&c_pod, o_sig);
                    arr2.remove(&arr2, j);
                    j--;
                }
            }
        }
        if(c_pod.count > 0) 
            pods.add(&pods, c_pod);
    }
    
    printf("\nMISSION 3\n");
    print_pods(&pods);
}

void wait_enter(){
    char c = 0;
    while(c != 'c')
    {
        scanf(" %c", &c);
    }
}

int main(int argc, char** argv) {
    
    char observer_path[256], sighting_path[256];
    printf("Observers file?: ");
    scanf("%255s", observer_path);
    printf("Sightings file?: ");
    scanf("%255s", sighting_path);
    
    array_observer observers = read_observers(observer_path);
    array_sighting sightings = read_sightings(sighting_path);
    
    if(observers.count < 0 || sightings.count < 0) {
        fprintf(stderr, 
                "Something went wrong with reading the files.\nAborting.\n");
        return (EXIT_FAILURE);
    }
    
    mission1(&observers, &sightings);
    printf("Press c to continue...");
    wait_enter();
    array_sighting_group grps = mission2(&sightings);
    printf("Press c to continue...");
    wait_enter();
    mission3(&grps);
    printf("Press c to continue...");
    wait_enter();
    printf("\nThe end.\n");
    fflush(stdout);
    return (EXIT_SUCCESS);
}

