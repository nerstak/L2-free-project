#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "layout.h"

extern Layout* loadSingleLayout(char* environment, char* name) {
    FILE* file;
    char path[50], line[60];
    Coords* coords;
    Layout* room;
    char* temp;

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
    if(room == NULL) {
        printf("An error occured while initializing a room object\n");
        exit(EXIT_FAILURE);
    }

    room->name = malloc(sizeof(char)*25);

    //Reading name and size
    fscanf(file, "%24[^,],\n", room->name);
    temp = room->name;
    room->name = realloc(room->name,strlen(room->name)+1);
    if(room->name == NULL) {
        free(temp);
        return NULL;
    }
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
    room->setMobs = malloc(sizeof(char)*25);
    strcpy(room->setMobs,"");
    fscanf(file, "SET_MOB=%15[^,],\n", room->setMobs);
    temp = room->setMobs;
    room->setMobs = realloc(room->setMobs,strlen(room->setMobs)+1);
    if(room->setMobs == NULL) {
        free(temp);
        return NULL;
    }

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
        i++;
        printf("\n");
    }
    fclose(file);
    return room;
}

extern void freeSingleLayout(Layout** room) {
    //Free spawnable list
    free((*room)->Spawnable);
    (*room)->Spawnable = NULL;

    for(int i = 0; i < (*room)->lines; i++) {
        free((*room)->map[i]);
        (*room)->map[i] = NULL;
    }
    free((*room)->map);
    (*room)->map = NULL;

    free((*room)->name);
    (*room)->name = NULL;

    free((*room)->setMobs);
    (*room)->setMobs = NULL;

    free(*room);
    *room = NULL;
}