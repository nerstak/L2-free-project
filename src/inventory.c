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
void add_item_list(slot_inventory ** items_list, slot_inventory * new_item) {
    if(*items_list == NULL)
    {
        *items_list = new_item;
    } else {
        new_item->next = *items_list;
        (*items_list)->prev = new_item;
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


//Functions specific to the shop
//Init shop inventory
slot_inventory * init_shop() {
    slot_inventory *shop_inv = NULL;
    char name[25], description[100];
    int quantity, price;
    FILE * file;
    int errnum;
    file = fopen("../datas/shop/shop.list","r");
    if(file) {
        while(fscanf(file,"%20[^;];%98[^;];%d;%d\n",name,description,&quantity,&price) != EOF) {
            add_item_list(&shop_inv,create_item(name,quantity,price,description));
        }
    }
    fclose(file);
    return shop_inv;
}

//Cursor displacement (right: 1; left: -1; down: 10; up: 10)
void moveShopSelector(Data * data,slot_inventory * shop_list, slot_inventory * player_list) {
    int pos_to_go;
    switch(data->shop->ask_action) {
        //Case for right
        case 1:
            //First, case when we don't change of inventory, then if we have to (shop to player)s
            if(data->shop->selected->next != NULL) {
                data->shop->selected = data->shop->selected->next;
                data->shop->n_selected++;
            } else if (data->shop->n_selected < 20) {
                data->shop->selected = player_list;
                data->shop->n_selected = 20;
            }
        //Case for left
        case -1:
            //First, case when we don't change of inventory, then if we have to (player to shop)
            if(data->shop->selected->prev != NULL) {
                data->shop->selected = data->shop->selected->prev;
                data->shop->n_selected--;
            } else if (data->shop->n_selected > 20) {
                data->shop->selected = shop_list;
                data->shop->n_selected = 0;
                while(data->shop->selected->next != NULL) {
                    data->shop->selected = data->shop->selected->next;
                    (data->shop->n_selected)++;
                }
            }
        //Case for down
        case 10: ;
            if(data->shop->n_selected % 10 != 3) {
                pos_to_go = (data->shop->n_selected + 10) % 40;
                //If we change of inventory
                if (data->shop->n_selected % 10 == 1) {
                    data->shop->selected = player_list;
                }
                while (data->shop->selected->next != NULL && data->shop->n_selected != pos_to_go) {
                    data->shop->selected = data->shop->selected->next;
                    (data->shop->n_selected)++;
                }
            }
        //Case for up
        case -10: ;
            if(data->shop->n_selected % 10 != 0) {
                pos_to_go = (data->shop->n_selected + 10) % 40;
                //If we change of inventory
                if (data->shop->n_selected % 10 == 2) {
                    data->shop->selected = player_list;
                    while (data->shop->selected->next != NULL && data->shop->n_selected != pos_to_go) {
                        data->shop->selected = data->shop->selected->next;
                        (data->shop->n_selected)++;
                    }
                } else {
                    while (data->shop->selected->next != NULL && data->shop->n_selected != pos_to_go) {
                        data->shop->selected = data->shop->selected->prev;
                        (data->shop->n_selected)--;
                    }
                }
            }
    }
}