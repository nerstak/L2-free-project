#ifndef FREE_PROJECT_INVENTORY_H
#define FREE_PROJECT_INVENTORY_H

//Statistics, also used for the player
typedef struct stats_entity {
    int health;
    int damage;
    int speed;
    int agility;
} stats_entity;

//Functions relative to the inventory and the shop
typedef struct SlotInventory {
    char description[100];
    char name[25];
    char type;
    int id;
    int price;
    int quantity;
    stats_entity* characteristics;
    struct SlotInventory* prev;
    struct SlotInventory* next;
} SlotInventory;

extern SlotInventory* loadReferenceItems();

extern SlotInventory* init_ShopInventory(SlotInventory *referenceItems, int* size);
extern void freeOne_SlotInventory(SlotInventory** item);
extern void freeAll_SlotInventory(SlotInventory** item);
extern SlotInventory* create_SlotInventory(int id, int quantity, SlotInventory* referenceItems);

extern void add_SlotInventory(SlotInventory** list, SlotInventory* item, int* size);
extern SlotInventory* remove_SlotInventory(SlotInventory** list, int id, int* size);
extern SlotInventory* search_SlotInventory(SlotInventory* list, int id);

#endif //FREE_PROJECT_INVENTORY_H
