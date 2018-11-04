#ifndef FREE_PROJECT_INVENTORY_H
#define FREE_PROJECT_INVENTORY_H


//Functions relative to the inventory and the shop


typedef struct slot_inventory {
    char name_item[25];
    char description [100];
    int quantity;
    int price;
    struct slot_inventory * prev;
    struct slot_inventory * next;
} slot_inventory;

slot_inventory * create_item(char * name_item, int quantity, int price, char * description);
void add_item_list(slot_inventory ** items_list, slot_inventory * new_item, int * size);
slot_inventory * remove_item_list(slot_inventory ** items_list, char * name, int * size);
slot_inventory * search_item_list(slot_inventory * items_list, char * name);
void free_item(slot_inventory * item);

slot_inventory * init_shop();
#endif //FREE_PROJECT_INVENTORY_H
