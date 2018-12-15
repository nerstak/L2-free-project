#ifndef FREE_PROJECT_ENGINE_GAME_ENTITIES_MAIN_H
#define FREE_PROJECT_ENGINE_GAME_ENTITIES_MAIN_H

#include "../player.h"

typedef enum EntityType { MOTH = 0 , WORM = 1 , PROJECTILE = 5 , TREE = 2 } EntityType;

typedef struct Entity {
    int type;
    void* entity;

    float health;
    float damage;
    float speed;

    MovementValues* movement;
    Timer* attackTimer;
    Timer* shootTimer;

    struct DamageIndicatorQueue* damageIndicatorQueue;
} Entity;

typedef struct EntityList {
    Entity* data;
    struct EntityList* next;
} EntityList;

typedef struct DamageIndicator {
    float amount;

    SDL_Rect* position;
    Timer* timer;
} DamageIndicator;

typedef struct DamageIndicatorQueueNode {
    struct DamageIndicator* data;
    struct DamageIndicatorQueueNode* next;
} DamageIndicatorQueueNode;

typedef struct DamageIndicatorQueue {
    DamageIndicatorQueueNode* front;
    DamageIndicatorQueueNode* rear;
} DamageIndicatorQueue;

struct Data;

extern EntityList* init_EntityNode(int type);
extern void append_EntityNode(EntityList * node , EntityList ** dest);
//extern EntityList* initList_Entity();
extern void clean_Entity(Entity** p);
extern void cleanList_Entity(EntityList** p);

extern DamageIndicator* init_DamageIndicator();
extern DamageIndicatorQueue* initQueue_DamageIndicator();
extern void clean_DamageIndicator(DamageIndicator** p);
extern void cleanQueue_DamageIndicator(DamageIndicatorQueue** p);
extern void enQueue_DamageIndictator(DamageIndicatorQueue* q, DamageIndicator* p);
extern DamageIndicatorQueueNode* deQueue_DamageIndicator(DamageIndicatorQueue* q);
extern void popQueue_DamageIndicator(DamageIndicatorQueue* q);
extern bool isEmptyQueue_DamageIndicator(DamageIndicatorQueue* q);

extern void process_Entity(EntityList** list, struct Data* data);
extern EntityList* killList_Entity(struct Data* data, EntityList* list, EntityList** dying);
extern void damage_Entity(Entity* e, struct Data* data, double x, double y);
extern void knockBack_Entity(Entity* e, struct Data* data, int direction, int x, int y,Timer *timer);

extern void process_Dying(EntityList** list, struct Data* data);
extern EntityList* cloudList_Entity(EntityList* list);

extern struct entities_bool* initEntitiesBool();
extern void freeEntitiesBool(struct entities_bool** e);
extern void resetEntitiesBool(struct entities_bool* e);

#endif //FREE_PROJECT_ENGINE_GAME_ENTITIES_MAIN_H
