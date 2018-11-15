#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "layout.h"

extern Layout* loadSingleLayout(char* environment, char* name) {
    FILE* file;
    char path[50];
    Coords* coords;
    Layout* room;
    if(strcmp(environment,"lobby") == 0) {
        sprintf(path,"src/data/lobby/%s.loli",name);
    }
    else if(strcmp(environment,"dungeons") == 0) {
        //TODO: Add dungeons
    }

    file = fopen(path,"r");
    if(file == NULL) {
        printf("File doesn't exist");
        return NULL;
    }

    room = malloc(sizeof(Layout));

    fscanf(file, "%48s\n", room->name);
    fscanf(file, "COLUMNS=%d,LINES=%d\n", &(room->columns), &(room->lines));
    room->map = malloc(sizeof(Tiles*) * room->lines);
    if(room->map == NULL) {
        return NULL;
    }

    for(int i=0; i < room->lines; i++) {
        room->map[i] = malloc(sizeof(Tiles) * room->columns);
        if(room->map[i] == NULL) {
            return NULL;
        }
    }
    fscanf(file, "SET_MOB=%48s\n", room->setMobs);

    room->Spawnable = malloc(sizeof(Coords));
    for(int unsigned i = 0; i < strlen(room->name); i++) {
        coords = realloc(room->Spawnable, i+1);
        if(room->Spawnable == NULL) {
            free(coords);
        }
        fscanf(file, "SPAWN %29[^:]: %d-%d\n", room->Spawnable[i].type, &(room->Spawnable[i].x), &(room->Spawnable[i].y));
    }
    for(int i=0; i < room->lines; i++) {
        for(int j=0; j < room->columns; j++) {
            room->map[j]->type = fgetc(file);
        }
        fseek(file,1,SEEK_CUR);
    }

    return room;
}