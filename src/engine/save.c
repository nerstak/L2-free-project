#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "save.h"

extern void init_Save(char* saveName, Data* data) {
    data->Isaac = malloc(sizeof(Player));
    //First, initialisation of easy variables
    strcpy(data->Isaac->save_name,saveName);
    data->Isaac->money = 0;
    data->Isaac->inventory = NULL;

    //Initialisation of coordinates
    //Those coordinates will have to correspond to the one of the lobby
    data->Isaac->pos = malloc(sizeof(coordinates_entity));
    data->Isaac->pos->x = 0;
    data->Isaac->pos->y = 0;


    //Initialisation of stats
    data->Isaac->current_stats = malloc(sizeof(stats_entity));
    data->Isaac->basic_stats = malloc(sizeof(stats_entity));

    data->Isaac->weapons = malloc(sizeof(Weapon )* 4);

    read_Save(data);

    //TO ADD
    //LITTLE GARDEN
    //

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
        fprintf(save_file,"%s\nMONEY=%d\n",Isaac->save_name,Isaac->money);
        //Writing stats
        fprintf(save_file,"STATS: H=%d D=%d S=%d A=%d\n",Isaac->basic_stats->health,Isaac->basic_stats->damage,Isaac->basic_stats->speed,Isaac->basic_stats->ability);
        //Writing weapons
        for(int i = 0; i < 4; i++) {
            fprintf(save_file,"WEAPON: '%s' '%s' D=%d S=%d\n",Isaac->weapons[i].name,Isaac->weapons[i].description,Isaac->weapons[i].damage,Isaac->weapons[i].swing_speed);
        }
        int i = 0;
        while(current != NULL && i < 20) {
            fprintf(save_file,"'%s' '%s' QUANT=%d PRICE=%d\n",current->name,current->description,current->quantity,current->price);
            current = current->next;
            i++;
        }
        fclose(save_file);
    }
}

int read_Save(Data* data) {
    FILE * save_file;
    char temp[50];
    SlotInventory * current;
    current = malloc(sizeof(SlotInventory));

    if(strcmp(data->Isaac->save_name,"") == 0) {
        save_file = fopen("src/datas/save/basic.save","r");
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
        fscanf(save_file,"MONEY=%d\n",&(data->Isaac->money));
        fscanf(save_file,"STATS: H=%d D=%d S=%d A=%d\n",&(data->Isaac->basic_stats->health),&(data->Isaac->basic_stats->damage),&(data->Isaac->basic_stats->speed),&(data->Isaac->basic_stats->ability));
        for(int i = 0; i < 4; i++) {
            fscanf(save_file,"WEAPON: '%18[^']' '%98[^']' D=%d S=%d\n",data->Isaac->weapons[i].name,data->Isaac->weapons[i].description,&(data->Isaac->weapons[i].damage),&(data->Isaac->weapons[i].swing_speed));
        }
        int i = 0;
        while(!feof(save_file) && i < 20) {
            fscanf(save_file,"'%23[^']' '%98[^']' QUANT=%d PRICE=%d\n",current->name,current->description,&(current->quantity),&(current->price));
            add_SlotInventory(&(data->Isaac->inventory), current, &i);
        }
        data->Isaac->size_inventory = i;
    }
    fclose(save_file);
    return 1;
}
