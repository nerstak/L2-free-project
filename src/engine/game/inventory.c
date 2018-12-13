#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#include "inventory.h"

//Init Reference Array for Items
extern referenceTable* loadReferenceItems() {
    //Creating referenceTable
    referenceTable* reference= NULL;
    reference = malloc(sizeof(referenceTable));
    SlotInventory *temp;
    reference->table = calloc(1,sizeof(SlotInventory));

    //Init the temp Slot
    SlotInventory tempStock;
    tempStock.next = NULL;
    tempStock.prev = NULL;
    tempStock.quantity = -1;
    tempStock.characteristics = malloc(sizeof(stats_entity));

    //Opening file
    int i = 0;
    FILE* dataFile;
    dataFile = fopen("src/data/items/items.data","r");
    if(dataFile == NULL) {
        printf("Error while opening items file");
        return NULL;
    }
    //Scanning line by line
    while(fscanf(dataFile,"%d: '%23[^']' '%98[^']' '%98[^']' PRICE=%d TYPE=%c H=%f D=%f S=%f A=%f\n",&(tempStock.id),tempStock.name,tempStock.description,tempStock.useMessage,&(tempStock.price), &(tempStock.type), &(tempStock.characteristics->health), &(tempStock.characteristics->damage),&(tempStock.characteristics->speed),&(tempStock.characteristics->agility)) != EOF) {
        //Resizing the array
        temp = reference->table;
        reference->table = realloc(reference->table, sizeof(SlotInventory) * (i + 1));
        if (reference->table == NULL) {
            free(temp);
            return NULL;
        }

        reference->table[i].characteristics = malloc(sizeof(stats_entity));
        copyItems(&(reference->table[i]), tempStock);

        i++;
    }
    reference->sizeItems = i;
    fclose(dataFile);
    return reference;
}

//Free a referenceTable
extern void freeReference(referenceTable** refTable) {
    for(int i = 0; i < (*refTable)->sizeItems; i++) {
        free((*refTable)->table[i].characteristics);
        (*refTable)->table[i].characteristics = NULL;
    }
    free((*refTable)->table);
    (*refTable)->table = NULL;
    free(*refTable);
    *refTable = NULL;
}

//Init shop inventory
extern SlotInventory* init_ShopInventory(referenceTable *referenceItems, int* size) {
    SlotInventory *shop_inv = NULL;
    int quantity, id;
    FILE * file;
    file = fopen("src/data/items/shop.data","r");
    if(file) {
        while(fscanf(file,"%d;%d\n",&id,&quantity) != EOF && *size < 16) {
            add_SlotInventory(&shop_inv, create_SlotInventory(id,quantity,referenceItems), size);
        }
    }
    fclose(file);
    reverseInventory(&shop_inv);
    return shop_inv;
}

//Free an item
extern void freeOne_SlotInventory(SlotInventory** item) {
    if(item) {
        free(*item);
        *item = NULL;
    }
}

//Free a list of items
extern void freeAll_SlotInventory(SlotInventory** item) {
    if(!item) {
        return;
    }else if(*item != NULL) {
        freeAll_SlotInventory(&((*item)->next));
        freeOne_SlotInventory(item);
    }
}

//Create an item and return its address
extern SlotInventory* create_SlotInventory(int id, int quantity, referenceTable* referenceItems) {
    //Init the item
    SlotInventory* new_item;
    new_item = malloc(sizeof(SlotInventory));
    if(new_item == NULL) {
        return NULL;
    }
    new_item->characteristics = malloc(sizeof(stats_entity));
    if(new_item->characteristics == NULL) {
        return NULL;
    }

    //Set values of data
    copyItems(new_item,referenceItems->table[id]);
    new_item->quantity = quantity;
    new_item->next = NULL;
    new_item->prev = NULL;
    return new_item;
}

//Add an existing item to the beginning of a list
extern void add_SlotInventory(SlotInventory** list, SlotInventory* item, int* size) {
    if(list && item) {
        if(*list == NULL) {
            *list = item;
            (*size)++;
        } else if (*size < 16) {
            item->next = *list;
            (*list)->prev = item;
            *list = item;
            (*size)++;
        }
    }
}

//Remove an item of a list and return its adress
extern SlotInventory* remove_SlotInventory(SlotInventory** list, int id, int* size) {
    SlotInventory *temp_return, *temp = *list;
    while(temp != NULL) {
        if(temp->id == id) {
            temp_return = temp;
            if(temp->next != NULL) {
                temp->next->prev = temp->prev;
            }
            if(temp->prev != NULL) {
                temp->prev->next = temp->next;
            }
            if(temp->prev == NULL) {
                //Important case: if we remove the first element
                *list = temp->next;
            }
            (*size)--;
            return temp_return;
        }
        temp = temp->next;
    }
    return NULL;
}

//Search an item in a list and return its adress
extern SlotInventory* search_SlotInventory(SlotInventory* list, int id) {
    SlotInventory * current = list;
    //Even if it is not supposed to have more than 16 elements, we check
    int i = 0;
    while(current != NULL && i < 16) {
        if(current->id == id) {
            return current;
        } else {
            i++;
            current = current->next;
        }
    }
    return NULL;
}

//Copy the stats
extern void copyStats(stats_entity* receiver, stats_entity* original) {
    receiver->health = original->health;
    receiver->damage = original->damage;
    receiver->agility = original->agility;
    receiver->speed = original->speed;
}

//Copy the characteristics of an item
extern void copyItems(SlotInventory* receiver, SlotInventory original) {
    strcpy(receiver->name, original.name);
    strcpy(receiver->description, original.description);
    strcpy(receiver->useMessage, original.useMessage);
    receiver->price = original.price;
    receiver->type = original.type;
    receiver->id = original.id;
    receiver->quantity = original.quantity;

    copyStats(receiver->characteristics,original.characteristics);
}

extern void reverseInventory(SlotInventory** inventory) {
    SlotInventory* temp = NULL;
    SlotInventory* current = *inventory;

    while(current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }

    if(temp != NULL) {
        *inventory = temp->prev;
    }
}

extern void resetUsedPotions(generalStats* stats) {
    for(int i = 0; i < 6; i++) {
        stats->potionsUsed[i] = 0;
    }

}