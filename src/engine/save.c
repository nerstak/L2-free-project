#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "save.h"

/**
 * Check if a save exist
 * @param saveName a string refering to the save to look for
 * @param data a pointer to a Data Object
 * @return an int attesting the presence or not of the save
 */
static int isSavePresent(char* saveName, Data* data);

/**
 * Read the common value of the Player Object
 * @param data Pointer of Data Object
 */
static void loadPlayer(Data* data);

/**
 * Write inside the save file the save name, the day and money
 * @param saveFile a pointer to a FILE
 * @param Isaac a pointer to a Player Object
 */
static void writePlayer(FILE* saveFile,Player* Isaac);
/**
 * Write the statistics of the game
 * @param saveFile a pointer to a FILE
 * @param Isaac a pointer to a Player Object
 */
static void writeGameStats(FILE* saveFile, Player* Isaac);
/**
 * Write the characteristics fo the player
 * @param saveFile a pointer to a FILE
 * @param Isaac a pointer to a Player Object
 */
static void writeStats(FILE* saveFile,Player* Isaac);
/**
 * Write the list of weapon of the Player
 * @param saveFile a pointer to a FILE
 * @param Isaac a pointer to a Player Object
 */
static void writeWeapons(FILE* saveFile, Player* Isaac);
/**
 * Write the content of the garden
 * @param saveFile a pointer to a FILE
 * @param field a pointer to a field_t Object
 */
static void writeGarden(FILE* saveFile,field_t* field);
/**
 * Write the inventory
 * @param saveFile a pointer to a FILE
 * @param Isaac a pointer to a Player Object
 */
static void writeInventory(FILE* saveFile, Player* Isaac);

/**
 * Read the save for money and day
 * @param saveFile a pointer to a FILE
 * @param data a pointer to a Data Object
 * @param fileName a string for the saveName
 */
static void readPlayer(FILE* saveFile, Data* data, char* fileName);
/**
 * Read the statistics of the game
 * @param saveFile a pointer to a FILE
 * @param data a pointer to a Data Object
 */
static void readGameStats(FILE* saveFile, Data* data);
/**
 * Read the characteristics of the Player
 * @param saveFile a pointer to a FILE
 * @param data a pointer to a Data Object
 */
static void readStats(FILE* saveFile, Data* data);
/**
 * Read the weapons of the Player
 * @param saveFile a pointer to a FILE
 * @param data a pointer to a Data Object
 */
static void readWeapons(FILE* saveFile, Data* data);
/**
 * Read the content of the Garden
 * @param saveFile a pointer to a FILE
 * @param data a pointer to a Data Object
 */
static void readGarden(FILE* saveFile, Data* data);
/**
 * Read the content of the inventory
 * @param saveFile a pointer to a FILE
 * @param data a pointer to a Data Object
 */
static void readInventory(FILE* saveFile, Data* data);

//Init of the game and the save
extern int initGame(char* saveName, Data* data) {
    if(isSavePresent(saveName, data) == 1) {
        //Loading of the reference
        data->referenceItems = loadReferenceItems();

        //Loading player
        data->Isaac = init_Player();

        strcpy(data->Isaac->saveName,saveName);

        loadPlayer(data);
        data->field = initField();
        readSave(data);
        return 1;
    }

    return 0;
}

static int isSavePresent(char* saveName, Data* data) {
    FILE* saveFile = NULL;
    char temp[50];

    //Chose the right file to open
    if(strcmp(saveName,"") == 0) {
        saveFile = fopen("src/data/player/basic.save","r");
    } else {
        sprintf(temp,"saves/%s",saveName);
        saveFile = fopen(temp, "r");
    }

    if(saveFile) {
        fclose(saveFile);
        return 1;
    } else {
        return 0;
    }
}

//Write important data inside the file
extern void writeSave(Data* data) {
    FILE * saveFile;
    char temp[50];

    //We create or reset the save file
    sprintf(temp,"saves/%s",data->Isaac->saveName);
    saveFile = fopen(temp, "w+");
    if(saveFile == NULL) {
        printf("Error while creating or opening file during saving.\n");
        exit(EXIT_FAILURE);
    }

    writePlayer(saveFile, data->Isaac);
    writeGameStats(saveFile, data->Isaac);
    writeStats(saveFile, data->Isaac);
    writeWeapons(saveFile, data->Isaac);
    writeGarden(saveFile, data->field);
    writeInventory(saveFile, data->Isaac);

    data->Isaac->gameStats->dungeonDay = 0;
    resetStats(data->Isaac);

    fclose(saveFile);
}

//Read the values inside one of the file
extern void readSave(Data* data) {
    FILE * saveFile;
    char temp[50];

    //Chose the right file to open
    if(strcmp(data->Isaac->saveName,"") == 0) {
        saveFile = fopen("src/data/player/basic.save","r");
        strcpy(data->Isaac->saveName,"save1.save");
    } else {
        sprintf(temp,"saves/%s",data->Isaac->saveName);
        saveFile = fopen(temp, "r");
    }

    if(saveFile == NULL) {
        printf("Error while reading save");
        exit(EXIT_FAILURE);
    }

    readPlayer(saveFile, data, temp);
    readGameStats(saveFile, data);
    readStats(saveFile, data);
    readWeapons(saveFile, data);
    readGarden(saveFile, data);
    readInventory(saveFile, data);

    fclose(saveFile);
}

static void loadPlayer(Data* data) {
    FILE* playerFile;

    playerFile = fopen("src/data/player/player.data","r");
    if(!playerFile) {
        printf("Error while opening player.data");
        exit(EXIT_FAILURE);
    }
    fscanf(playerFile,"MH=%f MS=%f MA=%f MD=%f\n",&(data->Isaac->stats->max->health),&(data->Isaac->stats->max->speed),&(data->Isaac->stats->max->agility),&(data->Isaac->stats->max->damage));
    fclose(playerFile);
}


static void writePlayer(FILE* saveFile,Player* Isaac) {
    fprintf(saveFile,"%s\nDAY=%d\nMONEY=%d\n",Isaac->saveName,++(Isaac->day),Isaac->money);
}

static void writeGameStats(FILE* saveFile, Player* Isaac) {
    fprintf(saveFile,"%d %d %d\n",Isaac->gameStats->death, Isaac->gameStats->dungeons, Isaac->gameStats->kills);
}

static void writeStats(FILE* saveFile,Player* Isaac) {
    fprintf(saveFile,"STATS: H=%f D=%f S=%f A=%f\n",Isaac->stats->basic->health,Isaac->stats->basic->damage,Isaac->stats->basic->speed,Isaac->stats->basic->agility);
}

static void writeWeapons(FILE* saveFile, Player* Isaac) {
    for(int i = 0; i < 4; i++) {
        fprintf(saveFile,"WEAPON: '%s' '%s' D=%f A=%f\n",Isaac->weapons[i].name,Isaac->weapons[i].description,Isaac->weapons[i].damage,Isaac->weapons[i].agility);
    }
}

static void writeGarden(FILE* saveFile,field_t* field) {
    Plant* tempPlant;
    for(int i = 0; i < 4; i++) {
        tempPlant = assignPlant(i, field);
        if(tempPlant) {
            fprintf(saveFile, "PLANT: %d %d\n", tempPlant->idVegetable, tempPlant->dayLeft);
        } else {
            fprintf(saveFile, "PLANT: -1 0\n");
        }
    }
}

static void writeInventory(FILE* saveFile, Player* Isaac) {
    SlotInventory * current = Isaac->inventory;
    int i = 0;
    while(current != NULL && i < 16) {
        fprintf(saveFile,"ID=%d QUANT=%d\n",current->id,current->quantity);
        current = current->next;
        i++;
    }
}

static void readPlayer(FILE* saveFile, Data* data, char* fileName) {
    fscanf(saveFile,"%s\nDAY=%d\nMONEY=%d\n",fileName,&(data->Isaac->day),&(data->Isaac->money));
    data->Isaac->gameStats->dungeonDay = 0;
}

static void readGameStats(FILE* saveFile, Data* data) {
    fscanf(saveFile,"%d %d %d\n",&(data->Isaac->gameStats->death), &(data->Isaac->gameStats->dungeons), &(data->Isaac->gameStats->kills));
}

static void readStats(FILE* saveFile, Data* data) {
    fscanf(saveFile,"STATS: H=%f D=%f S=%f A=%f\n",&(data->Isaac->stats->basic->health),&(data->Isaac->stats->basic->damage),&(data->Isaac->stats->basic->speed),&(data->Isaac->stats->basic->agility));
    //Checking that the value are not to high
    alterDamage_Player(data->Isaac, 0, 'b');
    alterSpeed_Player(data->Isaac, 0, 'b');
    alterAgility_Player(data->Isaac, 0, 'b');
    alterHealth_Player(data->Isaac, 0, 'b');

    copyStats(data->Isaac->stats->current,data->Isaac->stats->basic);
}

static void readWeapons(FILE* saveFile, Data* data) {
    for(int i = 0; i < 4; i++) {
        fscanf(saveFile,"WEAPON: '%18[^']' '%98[^']' D=%f A=%f\n",data->Isaac->weapons[i].name,data->Isaac->weapons[i].description,&(data->Isaac->weapons[i].damage),&(data->Isaac->weapons[i].agility));
    }
}

static void readGarden(FILE* saveFile, Data* data) {
    for(int i = 0; i < 4; i++) {
        Plant* tempPlant = assignPlant(i, data->field);
        fscanf(saveFile,"PLANT: %d %d\n",&(tempPlant->idVegetable),&(tempPlant->dayLeft));
    }
}

static void readInventory(FILE* saveFile, Data* data) {
    int id, quantity, i = 0;
    while(fscanf(saveFile,"ID=%d QUANT=%d\n",&(id),&(quantity)) != EOF && i < 16) {
        add_SlotInventory(&(data->Isaac->inventory), create_SlotInventory(id,quantity,data->referenceItems), &i);
    }
    data->Isaac->sizeInventory = i;
}