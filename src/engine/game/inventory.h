#ifndef FREE_PROJECT_ENGINE_GAME_INVENTORY_H
#define FREE_PROJECT_ENGINE_GAME_INVENTORY_H

//Statistics, also used for the player
typedef struct stats_entity {
    float health;
    float damage;
    float speed;
    float agility;
} stats_entity;

typedef struct generalStats {
    stats_entity* current;
    stats_entity* basic;
    stats_entity* max;
    int* potionsUsed;
} generalStats;

//Functions relative to the inventory and the shop
typedef struct SlotInventory {
    char description[100];
    char name[25];
    char useMessage[100];
    char type;
    int id;
    int price;
    int quantity;
    stats_entity* characteristics;
    struct SlotInventory* prev;
    struct SlotInventory* next;
} SlotInventory;

typedef struct referenceTable {
    int sizeItems;
    SlotInventory* table;
}referenceTable;

/**
 * Load the table of reference of items
 * @return a referenceTable object
 */
extern referenceTable* loadReferenceItems();

/**
 * Free a referenceTable of object
 */
extern void freeReference(referenceTable** refTable);

/**
 * Initialise the inventory of the shop
 * @param referenceItems a table of reference for items
 * @param size a pointer of int that keep in memory the size
 * @return a SlotInventory object
 */
extern SlotInventory* init_ShopInventory(referenceTable *referenceItems, int* size);

/**
 * Free only one slot of inventory
 * @param item a double pointer of the SlotInventory
 */
extern void freeOne_SlotInventory(SlotInventory** item);

/**
 * Free the whole inventory
 * @param item a double pointer of the first SlotInventory
 */
extern void freeAll_SlotInventory(SlotInventory** item);


/**
 * Initialise and fill a SlotInventory
 * @param id the int corresponding to the item to create
 * @param quantity the number of items
 * @param referenceItems the referenceTable of items
 * @return a pointer to SlotInventory
 */
extern SlotInventory* create_SlotInventory(int id, int quantity, referenceTable* referenceItems);

/**
 * Expands the list of sorted items
 * @param list double pointer of SlotInventory to the list we expand
 * @param item pointer of SlotInventory of the item to add
 * @param size pointer of integer referring to the size of the list
 * @return int attesting the integrity of the operation
 */
extern int add_SlotInventory(SlotInventory** list, SlotInventory* item, int* size);

/**
 * Remove of SlotInventory from a list of SlotInventory
 * @param list double pointer of SlotInventory of the list
 * @param id int corresponding to the item we want to remove
 * @param size pointer of integer referring to the size of the list
 * @return pointer of SlotInventory that was removed
 */
extern SlotInventory* remove_SlotInventory(SlotInventory** list, int id, int* size);

/**
 * Search an item with the ID
 * @param list pointer of SlotInventory of the list
 * @param id integer used to search item
 * @return pointer of SlotInventory of the item if found
 */
extern SlotInventory* search_SlotInventory(SlotInventory* list, int id);


/**
 * Copy the stats
 * @param receiver pointer of stats_entity where the stats are paste
 * @param original pointer of stats_entity from where the stats are copied
 */
extern void copyStats(stats_entity* receiver, stats_entity* original);

/**
 * Copy the information of an item excluding Next and Previous object
 * @param receiver pointer of SlotInventory where the information are paste
 * @param original SlotInventory object from where the information are copied
 */
extern void copyItems(SlotInventory* receiver, SlotInventory original);

/**
 * Reverse the order of the inventory
 * @param inventory double pointer of SlotInventory
 */
extern void reverseInventory(SlotInventory** inventory);

/**
 * Reset the potions used
 * @param stats a pointer to a generalStats Object
 */
extern void resetUsedPotions(generalStats* stats);

#endif //FREE_PROJECT_ENGINE_GAME_INVENTORY_H
