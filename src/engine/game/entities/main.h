#ifndef FREE_PROJECT_ENGINE_GAME_ENTITIES_MAIN_H
#define FREE_PROJECT_ENGINE_GAME_ENTITIES_MAIN_H

#include "../player.h"

typedef enum EntityType { MOTH = 0 } EntityType;

typedef struct Entity {
    int type;
    void* entity;

    float health;
    float damage;
    float speed;

    MovementValues* movement;
    Timer* attackTimer;
} Entity;

typedef struct EntityList {
    Entity* data;
    struct EntityList* next;
} EntityList;

struct Data;

extern Entity* init_Entity(int type);
extern EntityList* initList_Entity();
extern void clean_Entity(Entity** p);
extern void cleanList_Entity(EntityList** p);

extern void process_Entity(EntityList** list, struct Data* data);
extern EntityList* killList_Entity(EntityList* list);
extern void damage_Entity(Entity* e, struct Data* data, double x, double y);
extern void knockBack_Entity(Entity* e, struct Data* data, int direction, int x, int y);

#endif //FREE_PROJECT_ENGINE_GAME_ENTITIES_MAIN_H
