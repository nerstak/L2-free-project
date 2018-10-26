#include <stdlib.h>
#include <string.h>

#include "inventory.h"

//Create an item and return its adress
slot_inventory * create_item(char * name_item, int quantity, char * description) {
    if(strlen(name_item) < 20 && quantity > 0 && description < 100) {
        slot_inventory * new_item;
        new_item = malloc(sizeof(slot_inventory));
        strcpy(new_item->name_item,name_item);
        strcpy(new_item->description,description);
        new_item->quantity = quantity;
        new_item->next = NULL;
        return new_item;
    }
    return NULL;
}

//Add an existing item to the beginning of a list
void add_item_list(slot_inventory ** items_list, slot_inventory * new_item) {
    if(*items_list == NULL)
    {
        *items_list = new_item;
    } else {
        new_item->next = *items_list;
        *items_list = new_item;
    }
}

//Remove an item of a list and return its adress
slot_inventory * remove_item_list(slot_inventory ** items_list, char * name) {
    slot_inventory *temp2, * temp = * items_list;
    if(strcmp(temp->name_item, name) == 0) {
        *items_list = temp->next;
        return temp;
    } else {
        while(temp->next != NULL) {
            if(strcmp(temp->next->name_item, name) == 0) {
                temp2 = temp->next;
                temp->next = temp->next->next;
                return temp2;
            }
            temp = temp->next;
        }
        return NULL;
    }
}

//Free an item
void free_item(slot_inventory * item) {
    free(item);
}