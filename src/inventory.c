#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#include "inventory.h"

//Init Reference Array for Items
extern referenceTable* loadReferenceItems() {
    referenceTable* reference= NULL;
    reference = malloc(sizeof(referenceTable));
    SlotInventory *temp;
    reference->table = calloc(1,sizeof(SlotInventory));

    SlotInventory tempStock;
    tempStock.next = NULL;
    tempStock.prev = NULL;
    tempStock.quantity = -1;
    tempStock.characteristics = malloc(sizeof(stats_entity));

    int i = 0;
    FILE* dataFile;
    dataFile = fopen("src/data/items/items.data","r");
    if(dataFile == NULL) {
        printf("Error while opening items file");
        return NULL;
    }
    while(fscanf(dataFile,"%d: '%23[^']' '%98[^']' PRICE=%d TYPE=%c H=%d D=%d S=%d A=%d\n",&(tempStock.id),tempStock.name,tempStock.description,&(tempStock.price), &(tempStock.type), &(tempStock.characteristics->health), &(tempStock.characteristics->damage),&(tempStock.characteristics->speed),&(tempStock.characteristics->agility)) != EOF) {
        //Resizing the array
        temp = reference->table;
        reference->table = realloc(reference->table, sizeof(SlotInventory) * (i+1));
        if(reference->table == NULL) {
            free(temp);
            return NULL;
        }

        reference->table[i] = tempStock;
        reference->table[i].characteristics = malloc(sizeof(stats_entity));
        *(reference->table[i].characteristics) = *(tempStock.characteristics);

        i++;
    }

    reference->sizeItems = i;
    fclose(dataFile);
    return reference;
}

extern void freeReference(referenceTable** refTable) {
    for(int i = 0; i < (*refTable)->sizeItems; i++) {
        free((*refTable)->table[i].characteristics);
        (*refTable)->table[i].characteristics = NULL;
    }
    free((*refTable)->table);
    (*refTable)->table = NULL;
    free(refTable);
    *refTable = 0;
}

//Init shop inventory
extern SlotInventory* init_ShopInventory(referenceTable *referenceItems, int* size) {
    SlotInventory *shop_inv = NULL;
    int quantity, id;
    FILE * file;
    file = fopen("src/data/shop/shop.data","r");
    if(file) {
        while(fscanf(file,"%d;%d\n",&id,&quantity) != EOF && *size < 20) {
            add_SlotInventory(&shop_inv, create_SlotInventory(id,quantity,referenceItems), size);
        }
    }
    fclose(file);
    return shop_inv;
}

//Free an item
extern void freeOne_SlotInventory(SlotInventory** item) {
    free(*item);
    *item = NULL;

}

//Free a list of items
extern void freeAll_SlotInventory(SlotInventory** item) {
    if(*item != NULL) {
        freeAll_SlotInventory(&((*item)->next));
        freeOne_SlotInventory(item);
    }
}

//Create an item and return its address
extern SlotInventory* create_SlotInventory(int id, int quantity, referenceTable* referenceItems) {
    SlotInventory* new_item;
    new_item = malloc(sizeof(SlotInventory));
    if(new_item == NULL) {
        return NULL;
    }
    new_item->characteristics = malloc(sizeof(stats_entity));

    if(new_item->characteristics == NULL) {
        return NULL;
    }

    copyItems(new_item,referenceItems->table[id]);

    new_item->quantity = quantity;
    return new_item;
}

//Add an existing item to the beginning of a list
extern void add_SlotInventory(SlotInventory** list, SlotInventory* item, int* size) {
    if(*list == NULL)
    {
        *list = item;
        (*size)++;
    } else if (*size < 20) {
        item->next = *list;
        (*list)->prev = item;
        *list = item;
        (*size)++;
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
                //Important case: if we empty the list
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
    //Even if it is not supposed to have more than 20 elements, we check
    int i = 0;
    while(current != NULL && i < 20) {
        if(current->id == id) {
            return current;
        } else {
            i++;
            current = current->next;
        }
    }
    return NULL;
}

extern void copyItems(SlotInventory* receiver, SlotInventory original) {
    strcpy(receiver->name, original.name);
    strcpy(receiver->description, original.description);
    receiver->price = original.price;
    receiver->type = original.type;
    receiver->id = original.id;
    receiver->quantity = original.quantity;

    receiver->characteristics->health = original.characteristics->health;
    receiver->characteristics->damage = original.characteristics->damage;
    receiver->characteristics->agility = original.characteristics->agility;
    receiver->characteristics->speed = original.characteristics->speed;
}