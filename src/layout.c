#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "layout.h"
#include "player.h"

extern Layout* loadSingleLayout(char* environment, char* name) {
    FILE* file;
    char path[50], line[60];
    Coords* coords;
    Layout* room;
    char* temp;

    //Opening file
    if(strcmp(environment,"lobby") == 0) {
        sprintf(path,"src/data/lobby/%s.map",name);
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
    for(int unsigned i = 0; i < strlen(room->setMobs)-1; i++) {
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

extern int checkTilesPlayer(Player* player, Layout* layout, char type, int radius, int deltaW, int deltaH, int* tileX, int* tileY) {
    int columns = layout->columns;
    int lines = layout->lines;
    float posX = player->movement->pos->x;
    float posY = player->movement->pos->y;
    int tempX, tempY;

    for(int i = -1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {
            //If i and j are different from 0, we divide them by two
            //We are recovering 9 values, and 8 of them are on a circle with a radius and a separation angle of 45°
            tempX = i * radius / ((i != 0 && j != 0)?2:1);
            tempY = j * radius / ((i != 0 && j != 0)?2:1);

            //Checking that the value is inside the bounds
            if((posX + tempX) > deltaW && (posX + tempX) < (columns * 64 + deltaW) && (posY + tempY) > deltaW && (posY + tempY) < (lines * 64 + deltaH)) {
                if(layout->map[(int) (posY + tempY + deltaH) / 64 + 2][(int) ((posX + tempX + deltaW) / 64 + .5)].type == type) {
                    if(tileX && tileY) {
                        //If we have to recover the coordinates of the tile
                        *tileX = (int) ((posX + tempX + deltaW) / 64 + .5);
                        *tileY = (int) (posY + tempY + deltaH) / 64 + 2;
                    }
                    return 1;
                }
            }
        }
    }

    return 0;
}