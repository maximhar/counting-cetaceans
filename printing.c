#include "printing.h"
#include <stdio.h>
#include <string.h>

void print_sightings(array_sighting *col){
    int i;
    char type[12];
    printf("LATITUDE   LONGITUDE   TYPE        OBSERVER  \n");
    printf("---------------------------------------------\n");
    for(i = 0; i < col->count; i++){
        mammal_str(col->at(col, i)->type, type);
        printf("%7lf  %7lf   %-10s  %-8s\n", col->at(col, i)->loc.lat,
                col->at(col, i)->loc.lng, type, 
                col->at(col, i)->id);
    }   
}

void print_sightings_2(array_sighting_group *grps){
    int i, j, p_num = 0;
    char type[12];
    printf("TYPE        LATITUDE   LONGITUDE   CATEGORY   \n");
    printf("----------------------------------------------\n");
    for(i = 0; i < grps->count; i++){
        sighting_group *c_grp = grps->at(grps, i);
        sighting prnt = c_grp->parent;
        mammal_str(prnt.type, type);
        if(c_grp->children.count == 1) {
            printf("%-10s  %7lf  %7lf   SINGLE\n", type,
                    prnt.loc.lat, prnt.loc.lng);
        } else {
            printf("%-10s  %7lf  %7lf   MULTIPLE(%d)\n", type,
                    prnt.loc.lat, prnt.loc.lng, c_grp->children.count);
            for(j = 0; j < c_grp->children.count; j++){
                sighting *c_child = c_grp->children.at(&c_grp->children, j);
                 printf("            %7lf  %7lf\n", 
                         c_child->loc.lat, c_child->loc.lng);
            }
        }
    }  
}

void print_pods(array_pod *pods){
    int i, j, p_num = 0;
    char type[12];
    for(i = 0; i < pods->count; i++){
        pod *c_pod = pods->at(pods, i);
        if(c_pod->count < 2) continue;
        p_num++;
        printf("POD %-4d    %d MAMMAL(S)\n", p_num, c_pod->count);
        printf("TYPE        LATITUDE   LONGITUDE\n");
        printf("--------------------------------\n");
        for(j = 0; j < c_pod->count; j++){
            sighting *c_sig = c_pod->at(c_pod, j);
            mammal_str(c_sig->type, type);
            printf("%-10s  %7lf  %7lf\n", type,
                    c_sig->loc.lat, c_sig->loc.lng);
        }  
        printf("\n");
    }   
    if(p_num == 0) printf("NO PODS FOUND.\n");
}

void mammal_str(char mammal, char* dest) {
    switch(mammal) {
        case 'P': 
            strcpy(dest, "Porpoise");
            break;
        case 'D':
            strcpy(dest, "Dolphin");
            break;
        default:
            strcpy(dest, "UNKNOWN");
            break;
    }
}
