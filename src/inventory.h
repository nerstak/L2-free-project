#ifndef FREE_PROJECT_INVENTORY_H
#define FREE_PROJECT_INVENTORY_H

//Functions relative to the inventory and the shop

typedef struct SlotInventory {
    char name[25];
    char description[100];
    int quantity;
    int price;
    struct SlotInventory* prev;
    struct SlotInventory* next;
} SlotInventory;

extern SlotInventory* init_SlotInventory();
// TODO: Make a true free function of the whole DLL
extern void freeOne_SlotInventory(SlotInventory* item); // TODO: Fix it
extern SlotInventory* create_SlotInventory(char* name, int quantity, int price, char* description);

extern void add_SlotInventory(SlotInventory** list, SlotInventory* item, int* size);
extern SlotInventory* remove_SlotInventory(SlotInventory** list, char* name, int* size);
extern SlotInventory* search_SlotInventory(SlotInventory* list, char* name);

#endif //FREE_PROJECT_INVENTORY_H
