#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "save.h"

//Init of the game and the save
extern void initGame(char* saveName, Data* data) {
    strcpy(data->Isaac->save_name,saveName);

    loadPlayer(data);
    readSave(data);

    //TODO: LITTLE GARDEN

    copyStats(data->Isaac->basic_stats,data->Isaac->current_stats);
}

//Write important data inside the file
extern void writeSave(Data* data) {
    FILE * save_file;
    Player * Isaac = data->Isaac;
    SlotInventory * current = Isaac->inventory;
    char temp[50];

    //We create or reset the save file
    sprintf(temp,"saves/%s",data->Isaac->save_name);
    save_file = fopen(temp, "w+");
    if(save_file == NULL) {
        printf("Error while creating or opening file during saving.\n");
        exit(EXIT_FAILURE);
    } else {
        //Writing save_name and money
        fprintf(save_file,"%s\nDAY=%d\nMONEY=%d\n",Isaac->save_name,++(Isaac->day),Isaac->money);
        //Writing stats
        fprintf(save_file,"STATS: H=%f D=%f S=%f A=%f\n",Isaac->basic_stats->health,Isaac->basic_stats->damage,Isaac->basic_stats->speed,Isaac->basic_stats->agility);
        //Writing weapons
        for(int i = 0; i < 4; i++) {
            fprintf(save_file,"WEAPON: '%s' '%s' D=%f A=%f\n",Isaac->weapons[i].name,Isaac->weapons[i].description,Isaac->weapons[i].damage,Isaac->weapons[i].agility);
        }
        int i = 0;
        while(current != NULL && i < 16) {
            fprintf(save_file,"ID=%d QUANT=%d\n",current->id,current->quantity);
            current = current->next;
            i++;
        }
        fclose(save_file);
    }
}

//Read the values inside one of the file
extern void readSave(Data* data) {
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
        exit(EXIT_FAILURE);
    } else {
        //Reading all values
        fscanf(save_file,"%s\n",temp);
        fscanf(save_file,"DAY=%d\n",&(data->Isaac->day));
        fscanf(save_file,"MONEY=%d\n",&(data->Isaac->money));
        fscanf(save_file,"STATS: H=%f D=%f S=%f A=%f\n",&(data->Isaac->basic_stats->health),&(data->Isaac->basic_stats->damage),&(data->Isaac->basic_stats->speed),&(data->Isaac->basic_stats->agility));
        for(int i = 0; i < 4; i++) {
            fscanf(save_file,"WEAPON: '%18[^']' '%98[^']' D=%f S=%f\n",data->Isaac->weapons[i].name,data->Isaac->weapons[i].description,&(data->Isaac->weapons[i].damage),&(data->Isaac->weapons[i].agility));
        }
        int i = 0;
        while(fscanf(save_file,"ID=%d QUANT=%d\n",&(id),&(quantity)) != EOF && i < 16) {
            add_SlotInventory(&(data->Isaac->inventory), create_SlotInventory(id,quantity,data->referenceItems), &i);
        }
        data->Isaac->size_inventory = i;
    }
    fclose(save_file);
}

static void loadPlayer(Data* data) {
    FILE* playerFile;

    playerFile = fopen("src/data/player/player.data","r");
    if(!playerFile) {
        printf("Error while opening player.data");
        exit(EXIT_FAILURE);
    }
    fscanf(playerFile,"MH=%f MS=%f MA=%f MD=%f\n",&(data->Isaac->maxStats->health),&(data->Isaac->maxStats->speed),&(data->Isaac->maxStats->agility),&(data->Isaac->maxStats->damage));
    fclose(playerFile);
}