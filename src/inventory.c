#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#include "inventory.h"


extern SlotInventory* loadReferenceItems() {
    SlotInventory *referenceTable, *temp;
    referenceTable = calloc(1,sizeof(SlotInventory));
    SlotInventory tempStock;
    tempStock.next = NULL;
    tempStock.prev = NULL;
    tempStock.quantity = -1;

    int i = 0;
    FILE* dataFile;
    dataFile = fopen("src/datas/items/items.data","r");
    if(dataFile == NULL) {
        printf("Error while opening items file");
        return NULL;
    }
    while(fscanf(dataFile,"%d: '%23[^']' '%98[^']' PRICE=%d\n",&(tempStock.id),tempStock.name,tempStock.description,&(tempStock.price)) != EOF) {
        temp = referenceTable;
        referenceTable = realloc(referenceTable, sizeof(SlotInventory) * (i+1));
        if(referenceTable == NULL) {
            free(temp);
            return NULL;
        }
        referenceTable[i] = tempStock;
        i++;
    }
    fclose(dataFile);
    return referenceTable;

}

//Init shop inventory
extern SlotInventory* init_SlotInventory() {
    SlotInventory *shop_inv = NULL;
    char name[25], description[100];
    int quantity, price, i=0;
    FILE * file;
    file = fopen("src/datas/shop/shop.data","r");
    if(file) {
        while(fscanf(file,"%20[^;];%98[^;];%d;%d\n",name,description,&quantity,&price) != EOF && i < 20) {
            add_SlotInventory(&shop_inv, create_SlotInventory(name, quantity, price, description), &i);
        }
    }
    fclose(file);
    return shop_inv;
}

//Free an item // TODO: Fix here see comment in header
extern void freeOne_SlotInventory(SlotInventory* item) {
    item = NULL;
    free(item);
}

//Create an item and return its address
extern SlotInventory* create_SlotInventory(char* name, int quantity, int price, char* description) {
    if(strlen(name) < 20 && quantity > 0 && strlen(description) < 98) {
        SlotInventory * new_item;
        new_item = malloc(sizeof(SlotInventory));
        strcpy(new_item->name,name);
        strcpy(new_item->description,description);
        new_item->quantity = quantity;
        new_item->price = price;
        new_item->prev = NULL;
        new_item->next = NULL;
        return new_item;
    }
    return NULL;
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
extern SlotInventory* remove_SlotInventory(SlotInventory** list, char* name, int* size) {
    SlotInventory *temp_return, * temp = * list;
    while(temp!= NULL) {
        if(strcmp(temp->name, name) == 0) {
            temp_return = temp;
            if(temp->next != NULL) {
                temp->next->prev = temp->prev;
            }
            if(temp->prev != NULL) {
                temp->prev->next = temp->next;
            }
            if(temp->prev == NULL && temp->next == NULL) {
                //Important case: if we empty the list
                *list = NULL;
            }
            (*size)--;
            return temp_return;
        }
        temp = temp->next;
    }
    return NULL;
}

//Search an item in a list and return its adress
extern SlotInventory* search_SlotInventory(SlotInventory* list, char* name) {
    SlotInventory * current = list;
    //Even if it is not supposed to have more than 20 elements, we check
    int i = 0;
    while(current != NULL && i < 20) {
        if(strcmp(current->name,name) == 0) {
            return current;
        } else {
            i++;
            current = current->next;
        }
    }
    return NULL;
}