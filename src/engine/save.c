#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "save.h"

//Init of the game and the save
extern void init_Save(char* saveName, Data* data) {
    data->referenceItems = loadReferenceItems();

    data->Isaac = malloc(sizeof(Player));
    if(!data->Isaac) {
        return;
    }
    //First, initialisation of easy variables
    strcpy(data->Isaac->save_name,saveName);
    data->Isaac->money = 0;
    data->Isaac->inventory = NULL;

    //Initialisation of coordinates and movement
    //Those coordinates will have to correspond to the one of the lobby
    data->Isaac->movement = malloc(sizeof(MovementValues));

    data->Isaac->movement->pos = malloc(sizeof(coordinates_entity));
    data->Isaac->movement->pos->x = 0;
    data->Isaac->movement->pos->y = 0;

    data->Isaac->movement->velocity = malloc(sizeof(coordinates_entity));
    data->Isaac->movement->velocity->x = 0;
    data->Isaac->movement->velocity->y = 0;

    data->Isaac->movement->SpriteBox = malloc(sizeof(SDL_Rect));
    data->Isaac->movement->SpriteBox->x = 0;
    data->Isaac->movement->SpriteBox->y = 0;
    data->Isaac->movement->SpriteBox->h = 128;
    data->Isaac->movement->SpriteBox->w = 64;

    data->Isaac->movement->step = 0;
    data->Isaac->movement->direction = 0;

    //Initialisation of stats
    data->Isaac->current_stats = malloc(sizeof(stats_entity));
    data->Isaac->basic_stats = malloc(sizeof(stats_entity));

    data->Isaac->weapons = malloc(sizeof(Weapon )* 4);

    if(data->Isaac->weapons && data->Isaac->current_stats && data->Isaac->basic_stats && data->Isaac->movement)
    {
        if(data->Isaac->movement->pos && data->Isaac->movement->velocity && data->Isaac->movement->SpriteBox)
            read_Save(data);
        else
            return;
    }
    else {
        return;
    }


    //TODO: LITTLE GARDEN

    data->Isaac->current_stats = data->Isaac->basic_stats;
}

extern void write_Save(Data* data) {
    FILE * save_file;
    Player * Isaac = data->Isaac;
    SlotInventory * current = Isaac->inventory;
    char temp[50];

    //We create or reset the save file
    sprintf(temp,"saves/%s",data->Isaac->save_name);
    save_file = fopen(temp, "w+");
    if(save_file == NULL) {
        printf("Error while creating or opening file during saving.\n");
    } else {
        //Writing save_name and money
        fprintf(save_file,"%s\nDAY=%d\nMONEY=%d\n",Isaac->save_name,++(Isaac->day),Isaac->money);
        //Writing stats
        fprintf(save_file,"STATS: H=%d D=%d S=%d A=%d\n",Isaac->basic_stats->health,Isaac->basic_stats->damage,Isaac->basic_stats->speed,Isaac->basic_stats->agility);
        //Writing weapons
        for(int i = 0; i < 4; i++) {
            fprintf(save_file,"WEAPON: '%s' '%s' D=%d A=%d\n",Isaac->weapons[i].name,Isaac->weapons[i].description,Isaac->weapons[i].damage,Isaac->weapons[i].agility);
        }
        int i = 0;
        while(current != NULL && i < 20) {
            fprintf(save_file,"ID=%d QUANT=%d\n",current->id,current->quantity);
            current = current->next;
            i++;
        }
        fclose(save_file);
    }
}

int read_Save(Data* data) {
    FILE * save_file;
    char temp[50];
    int id, quantity;

    //Chose the right file to open
    if(strcmp(data->Isaac->save_name,"") == 0) {
        save_file = fopen("src/data/save/basic.save","r");
        strcpy(data->Isaac->save_name,"save1.save");
    } else {
        sprintf(temp,"saves/%s",data->Isaac->save_name);
        save_file = fopen(temp, "r");
    }

    if(save_file == NULL) {
        printf("Error while reading save");
        return 0;
    } else {
        fscanf(save_file,"%s\n",temp);
        fscanf(save_file,"DAY=%d\n",&(data->Isaac->day));
        fscanf(save_file,"MONEY=%d\n",&(data->Isaac->money));
        fscanf(save_file,"STATS: H=%d D=%d S=%d A=%d\n",&(data->Isaac->basic_stats->health),&(data->Isaac->basic_stats->damage),&(data->Isaac->basic_stats->speed),&(data->Isaac->basic_stats->agility));
        for(int i = 0; i < 4; i++) {
            fscanf(save_file,"WEAPON: '%18[^']' '%98[^']' D=%d S=%d\n",data->Isaac->weapons[i].name,data->Isaac->weapons[i].description,&(data->Isaac->weapons[i].damage),&(data->Isaac->weapons[i].agility));
        }
        int i = 0;
        while(fscanf(save_file,"ID=%d QUANT=%d\n",&(id),&(quantity)) != EOF && i < 20) {
            add_SlotInventory(&(data->Isaac->inventory), create_SlotInventory(id,quantity,data->referenceItems), &i);
        }
        data->Isaac->size_inventory = i;
    }
    fclose(save_file);
    return 1;
}
