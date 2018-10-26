#ifndef FREE_PROJECT_INVENTORY_H
#define FREE_PROJECT_INVENTORY_H

//Functions relative to the inventory and the shop

typedef struct slot_inventory {
    char name_item[20];
    char description [100];
    int quantity;
    struct slot_inventory * next;
} slot_inventory;

slot_inventory * create_item(char * name_item, int quantity, char * description);
void add_item_list(slot_inventory ** items_list, slot_inventory * new_item);
slot_inventory * remove_item_list(slot_inventory ** items_list, char * name);
void free_item(slot_inventory * item);

#endif //FREE_PROJECT_INVENTORY_H
