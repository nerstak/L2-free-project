#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "player.h"
#include "inventory.h"

//Create an item and return its adress
slot_inventory * create_item(char * name_item, int quantity, int price, char * description) {
    if(strlen(name_item) < 20 && quantity > 0 && strlen(description) < 98) {
        slot_inventory * new_item;
        new_item = malloc(sizeof(slot_inventory));
        strcpy(new_item->name_item,name_item);
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
void add_item_list(slot_inventory ** items_list, slot_inventory * new_item, int * size) {
    if(*items_list == NULL)
    {
        *items_list = new_item;
        *size++;
    } else if (*size < 20) {
        new_item->next = *items_list;
        (*items_list)->prev = new_item;
        *items_list = new_item;
        *size++;
    }
}

//Remove an item of a list and return its adress
slot_inventory * remove_item_list(slot_inventory ** items_list, char * name, int * size) {
    slot_inventory *temp_return, * temp = * items_list;
    while(temp!= NULL) {
        if(strcmp(temp->name_item, name) == 0) {
            temp_return = temp;
            if(temp->next != NULL) {
                temp->next->prev = temp->prev;
            }
            if(temp->prev != NULL) {
                temp->prev->next = temp->next;
            }
            if(temp->prev == NULL && temp->next == NULL) {
                //Important case: if we empty the list
                *items_list = NULL;
            }
            *size--;
            return temp_return;
        }
        temp = temp->next;
    }
    return NULL;
}

//Search an item in a list and return its adress
slot_inventory * search_item_list(slot_inventory * items_list, char * name) {
    slot_inventory * current = items_list;
    //Even if it is not supposed to have more than 20 elements, we check
    int i = 0;
    while(current != NULL && i < 20) {
        if(strcmp(current->name_item,name) == 0) {
            return current;
        } else {
            i++;
            current = current->next;
        }
    }
    return NULL;
}

//Free an item
void free_item(slot_inventory * item) {
    free(item);
    item = NULL;
}


//Functions specific to the shop
//Init shop inventory
slot_inventory * init_shop() {
    slot_inventory *shop_inv = NULL;
    char name[25], description[100];
    int quantity, price, i=0;
    FILE * file;
    file = fopen("src/datas/shop/shop.list","r");
    if(file) {
        while(fscanf(file,"%20[^;];%98[^;];%d;%d\n",name,description,&quantity,&price) != EOF && i < 20) {
            add_item_list(&shop_inv,create_item(name,quantity,price,description),&i);
        }
    }
    fclose(file);
    return shop_inv;
}