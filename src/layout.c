#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "layout.h"

extern Layout* loadSingleLayout(char* environment, char* name) {
    FILE* file;
    char path[50], line[60];
    Coords* coords;
    Layout* room;

    //Opening file
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

    //Reading name and size
    fscanf(file, "%24[^,],\n", room->name);
    fscanf(file, "COLUMNS=%d,LINES=%d,\n", &(room->columns), &(room->lines));
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

    //Reading set of mob
    fscanf(file, "SET_MOB=%15[^,],\n", room->setMobs);

    room->Spawnable = calloc(sizeof(Coords),1);
    for(int unsigned i = 0; i < strlen(room->setMobs); i++) {
        coords = realloc(room->Spawnable, i+1);
        if(room->Spawnable == NULL) {
            free(coords);
        }
        fscanf(file, "SPAWN %14[^:]: %d-%d,\n", room->Spawnable[i].type, &(room->Spawnable[i].x), &(room->Spawnable[i].y));
    }

    //Reading metadata of the map
    int i= 0;
    while(fgets(line,60,file) && i < room->lines)
    {
        for(int j = 0; j < room->columns; j++) {
            room->map[i][j].type = line[j];
            printf("%c",room->map[i][j].type);
        }
        printf("\n");
    }
    return room;
}