#include <stdlib.h>

#include "main.h"
#include "moth.h"
#include "worm.h"
#include "tree.h"
#include "boss.h"
#include "arm.h"
#include "projectile.h"

#include "../movement.h"
#include "../combat.h"

static void preprocesDamage_Entities(struct Data* data, int type);

extern EntityList* init_EntityNode(int type, float difficulty) {
    EntityList * node=NULL;
    node=malloc(sizeof(EntityList));

    Entity* result=NULL;
    result = malloc(1 * sizeof(Entity));

    if (result == NULL || node==NULL) {
        exit(EXIT_FAILURE);
    }

    result->damageIndicatorQueue = initQueue_DamageIndicator();

    switch(type) {
        case MOTH: {
            result->type = MOTH;
            result->entity = NULL;

            result->health = 3 * difficulty;
            result->damage = 1 * difficulty;
            result->speed = 1;

            result->movement = init_Movement();

            result->movement->animationStep=0;
            result->movement->position->x=0;
            result->movement->position->y=0;
            result->movement->velocity->x=0;
            result->movement->velocity->y=0;
            result->movement->spriteBox->h=96;
            result->movement->spriteBox->w=128;

            result->movement->hitBox->h=96;
            result->movement->hitBox->w=32;
            result->movement->spriteBox->x=0;
            result->movement->spriteBox->y=0;
            result->attackTimer=init_Timer();
            start_Timer(result->attackTimer);
            result->shootTimer=init_Timer();

            break;
        }
        case WORM: {
            result->type = WORM;
            result->entity = NULL;

            result->health = 2 * difficulty;
            result->damage = 1 * difficulty;
            result->speed = 0;

            result->movement = init_Movement();


            result->movement->animationStep=0;
            result->movement->position->x=608;
            result->movement->position->y=350;
            result->movement->velocity->x=0;
            result->movement->velocity->y=0;
            result->movement->spriteBox->h=112;
            result->movement->spriteBox->w=96;
            result->movement->hitBox->h=112;
            result->movement->hitBox->w=80;
            result->movement->spriteBox->x=0;
            result->movement->spriteBox->y=0;
            result->attackTimer=init_Timer();
            start_Timer(result->attackTimer);
            result->shootTimer=init_Timer();

            break;
        }
        case TREE: {
            result->type = TREE;
            result->entity = NULL;

            result->health = 2 * difficulty;
            result->damage = 1 * difficulty;
            result->speed = 1;

            result->movement = init_Movement();

            result->movement->animationStep = 0;
            result->movement->position->x = 0;
            result->movement->position->y = 0;
            result->movement->velocity->x = 0;
            result->movement->velocity->y = 0;
            result->movement->spriteBox->h = 96;
            result->movement->spriteBox->w = 64;

            result->movement->hitBox->h = 64;
            result->movement->hitBox->w = 64;
            result->movement->spriteBox->x = 0;
            result->movement->spriteBox->y = 0;
            result->attackTimer = init_Timer();
            start_Timer(result->attackTimer);
            result->shootTimer = init_Timer();

            break;
        }
        case PROJECTILE:
        {
            result->type = PROJECTILE;
            result->entity = NULL;

            result->health = 1 * difficulty;
            result->damage = 1;
            result->speed = 0;

            result->movement = init_Movement();

            result->movement->spriteBox->x=0;
            result->movement->spriteBox->y=0;
            result->movement->spriteBox->h=16;
            result->movement->spriteBox->w=16;


            result->movement->animationStep=0;
            result->movement->position->x=0;
            result->movement->position->y=0;

            result->movement->velocity->x=0;
            result->movement->velocity->y=0;

            result->movement->hitBox->x=0;
            result->movement->hitBox->y=0;
            result->movement->hitBox->h=16;
            result->movement->hitBox->w=16;

            result->attackTimer=init_Timer();
            result->shootTimer=init_Timer();
            break;
        }
        case BOSSBOD: {
            result->type = BOSSBOD;


            result->health = (int) (10 * difficulty);
            result->maxHealth = result->health * 2;
            result->entity = init_EBoss(result->health / 2, difficulty);

            result->damage = 2 * difficulty;
            result->speed = 1;

            result->movement = init_Movement();

            result->movement->animationStep=0;
            result->movement->position->x=448;
            result->movement->position->y=30;
            result->movement->velocity->x=0;
            result->movement->velocity->y=0;

            result->movement->spriteBox->x=0;
            result->movement->spriteBox->y=0;
            result->movement->spriteBox->h=288;
            result->movement->spriteBox->w=384;

            result->movement->hitBox->h=260;
            result->movement->hitBox->w=192;

            result->attackTimer=init_Timer();
            start_Timer(result->attackTimer);
            result->shootTimer=init_Timer();
            start_Timer(result->shootTimer);

            break;
        }
        case ARM: {
            result->type = ARM;
            result->entity = NULL;

            result->health = 5;
            result->damage = 2 * difficulty;
            result->speed = 5;

            result->movement = init_Movement();

            result->movement->animationStep=0;
            result->movement->position->x=0;
            result->movement->position->y=0;
            result->movement->velocity->x=0;
            result->movement->velocity->y=0;

            result->movement->spriteBox->x=0;
            result->movement->spriteBox->y=0;
            result->movement->spriteBox->h=224;
            result->movement->spriteBox->w=128;

            result->movement->hitBox->h=130;
            result->movement->hitBox->w=96;

            result->attackTimer=init_Timer();
            start_Timer(result->attackTimer);
            result->shootTimer=init_Timer();

            break;
        }
        default: {
            free(node);
            free(result);
            return NULL;

            break;
        }
    }
    node->data=result;
    node->next=NULL;
    return node;
}

extern void append_EntityNode(EntityList * node , EntityList ** dest)
{
    node->next=(*dest);
    (*dest)=node;
}

/* this just creates a list with an empty element and is bad
extern EntityList* initList_Entity() {
    EntityList* result = NULL;
    result = malloc(1 * sizeof(EntityList));

    if (result == NULL) {
        exit(EXIT_FAILURE);
    }

    result->data = NULL;
    result->next = NULL;

    return result;
}
*/

extern void clean_Entity(Entity** p) {
    if ((*p) != NULL) {
        clean_Timer(&((*p)->attackTimer));
        clean_Movement(&((*p)->movement));
        cleanQueue_DamageIndicator(&((*p)->damageIndicatorQueue));
        if ((*p)->type == BOSSBOD)
        {
            clean_EBoss((E_Boss**) &((*p)->entity));
        }

        free((*p));
        (*p) = NULL;
    }
}

extern void cleanList_Entity(EntityList** p) {
    if ((*p) != NULL) {
        if ((*p)->next != NULL) {
            cleanList_Entity(&((*p)->next));
        }

        clean_Entity(&((*p)->data));
        free((*p));
        (*p) = NULL;
    }
}


extern DamageIndicator* init_DamageIndicator() {
    DamageIndicator* result = NULL;
    result = malloc(1 * sizeof(DamageIndicator));

    if (result == NULL) {
        printf("An error occured while initializing a DamageIndicator object\n");
        exit(EXIT_FAILURE);
    }

    result->amount = 0;
    result->position = NULL;
    result->timer = init_Timer();

    result->position = malloc(1 * sizeof(SDL_Rect));

    if (result->position == NULL) {
        printf("An error occured while initializing a SDL_Rect for a DamageIndicator object\n");
        exit(EXIT_FAILURE);
    }

    return result;
}

extern DamageIndicatorQueue* initQueue_DamageIndicator() {
    DamageIndicatorQueue* result = NULL;
    result = malloc(1 * sizeof(DamageIndicatorQueue));

    if (result == NULL) {
        printf("An error occured while initializing a DamageIndicatorQueue object\n");
        exit(EXIT_FAILURE);
    }

    result->front = NULL;
    result->rear = NULL;

    return result;
}

extern void clean_DamageIndicator(DamageIndicator** p) {
    if ((*p) != NULL) {
        clean_Timer(&((*p)->timer));
        free((*p)->position);

        free((*p));
        (*p) = NULL;
    }
}

extern void cleanQueue_DamageIndicator(DamageIndicatorQueue** p) {
    if ((*p) != NULL) {
        if ((*p)->rear == NULL) {
            free(*p);
            (*p) = NULL;
        } else {
            DamageIndicatorQueueNode* temp = NULL;
            while ((*p)->rear != NULL) {
                temp = (*p)->front;
                (*p)->front = (*p)->front->next;

                clean_DamageIndicator(&(temp->data));
                free(temp);

                if ((*p)->front == NULL) {
                    (*p)->rear = NULL;
                }
            }

            free((*p));
            (*p) = NULL;
        }
    }
}

extern void enQueue_DamageIndictator(DamageIndicatorQueue* q, DamageIndicator* p) {
    DamageIndicatorQueueNode* temp = NULL;
    temp = malloc(1 * sizeof(DamageIndicatorQueueNode));

    if (temp == NULL) {
        printf("An error occured while initializing a DamaheIndicatorQueueNode object\n");
        exit(EXIT_FAILURE);
    }

    temp->data = p;
    temp->next = NULL;

    if (q->rear == NULL) {
        q->front = temp;
        q->rear = temp;

        return;
    }

    q->rear->next = temp;
    q->rear = temp;
}

extern DamageIndicatorQueueNode* deQueue_DamageIndicator(DamageIndicatorQueue* q) {
    if (q->front == NULL) {
        return NULL;
    }

    return q->front;
}

extern void popQueue_DamageIndicator(DamageIndicatorQueue* q) {
    if (q->front == NULL) {
        return;
    }

    DamageIndicatorQueueNode* temp = q->front;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    clean_DamageIndicator(&(temp->data));
    free(temp);
}

extern bool isEmptyQueue_DamageIndicator(DamageIndicatorQueue* q) {
    if (q->rear == NULL) {
        return true;
    } else {
        return false;
    }
}


extern void process_Entity(EntityList** list, struct Data* data) {
    // We kill (aka free) all dead monsters
    (*list) = killList_Entity(data, (*list), &(data->dyingEntities));
    process_Dying(&(data->dyingEntities),data);

    // We go through the whole list of monsters and apply actions depending of the type of monsters
    EntityList* temp = (*list);

    while(temp) {
        switch(temp->data->type) {
            case MOTH: {
                ai_EMoth(temp->data, data);

                break;
            }
            case WORM: {
                ai_EWorm(temp->data, data);

                break;
            }
            case TREE: {
                ai_ETree(temp->data, data);

                break;
            }
            case BOSSBOD: {
                ai_EBoss(temp->data, data);

                break;
            }
            case PROJECTILE: {
                ai_EProjectile(temp->data,data);

                break;
            }

            default: {
                break;
            }
        }

        // Clear the expired DamageIndicator
        DamageIndicatorQueueNode* tempNode = deQueue_DamageIndicator(temp->data->damageIndicatorQueue);
        while (tempNode != NULL) {
            DamageIndicatorQueueNode* next = tempNode->next;

            if (getTime_Timer(tempNode->data->timer) > 0.25) {
                popQueue_DamageIndicator(temp->data->damageIndicatorQueue);
            } else {
                break;
            }

            tempNode = next;
        }

        if (temp->data->type == BOSSBOD) {
            E_Boss* eBoss = (E_Boss*) temp->data->entity;

            if (eBoss->leftarm != NULL) {
                DamageIndicatorQueueNode* tempNode2 = deQueue_DamageIndicator(eBoss->leftarm->damageIndicatorQueue);
                while (tempNode2 != NULL) {
                    DamageIndicatorQueueNode* next = tempNode2->next;

                    if (getTime_Timer(tempNode2->data->timer) > 0.25) {
                        popQueue_DamageIndicator(eBoss->leftarm->damageIndicatorQueue);
                    } else {
                        break;
                    }

                    tempNode2 = next;
                }
            }

            if (eBoss->rightarm != NULL) {
                DamageIndicatorQueueNode* tempNode2 = deQueue_DamageIndicator(eBoss->rightarm->damageIndicatorQueue);
                while (tempNode2 != NULL) {
                    DamageIndicatorQueueNode* next = tempNode2->next;

                    if (getTime_Timer(tempNode2->data->timer) > 0.25) {
                        popQueue_DamageIndicator(eBoss->rightarm->damageIndicatorQueue);
                    } else {
                        break;
                    }

                    tempNode2 = next;
                }
            }
        }

        temp = temp->next;
    }
}


extern void process_Dying(EntityList** list, struct Data* data)
{
    (*list) = cloudList_Entity((*list));

    EntityList* temp = (*list);

    while(temp) {
        temp->data->movement->animationStep+=lap_Timer(temp->data->movement->timeSince);

        // Clear the expired DamageIndicator
        DamageIndicatorQueueNode* tempNode = deQueue_DamageIndicator(temp->data->damageIndicatorQueue);
        while (tempNode != NULL) {
            DamageIndicatorQueueNode* next = tempNode->next;

            if (getTime_Timer(tempNode->data->timer) > 0.25) {
                popQueue_DamageIndicator(temp->data->damageIndicatorQueue);
            } else {
                break;
            }

            tempNode = next;
        }

        temp = temp->next;
    }
}

extern EntityList* killList_Entity(Data* data, EntityList* list, EntityList** dying) {
    if (list == NULL) {
        return NULL;
    } else if (list->data->health <= 0) {
        EntityList* temp = list->next;
        list->data->movement->animationStep=0;
        if(list->data->type != PROJECTILE && list->data->type != BOSSBOD) {
            data->dungeonScene->sound->deathMob = 1;
        } else if (list->data->type == BOSSBOD) {
            data->dungeonScene->sound->bossJustDefeated = 1;
        }
        append_EntityNode(list,dying);
        return temp;
    }

    list->next = killList_Entity(data, list->next, dying);

    return list;
}

extern EntityList* cloudList_Entity(EntityList* list){
    if (list == NULL) {
        return NULL;
    }
    else if (list->data->movement->animationStep >= 3000 && list->data->type==BOSSBOD) {
        EntityList* temp = list->next;
        clean_Entity(&(list->data));
        list=NULL;
        return temp;
    }
    else if ((list->data->movement->animationStep >= 1000 || list->data->type==PROJECTILE) && list->data->type!=BOSSBOD) {
        EntityList* temp = list->next;
        clean_Entity(&(list->data));
        free(list);
        list=NULL;
        return temp;
    }

    list->next = cloudList_Entity(list->next);

    return list;
}

extern void damage_Entity(Entity* e, struct Data* data, double x, double y) {
    if (BoxCollision(e->movement->hitBox, data->Isaac->movement->hitBox)) {
        if(e->type==PROJECTILE)
        {
            e->health=0;
        }
        else
        {
            knockBack_Entity(e, data, -1, x, y,NULL);
        }

        if (data->Isaac->invulnerabilityTimer->started == false) {
            start_Timer(data->Isaac->invulnerabilityTimer);
            alterHealth_Player(data->Isaac, - e->damage, 'c');
            data->Isaac->combat->damageJustTaken = 1;
        }
    }

    if (BoxCollision(e->movement->hitBox, data->Isaac->combat->weaponHitBox) && !e->attackTimer->started && e->type!=PROJECTILE) {
        float damage=data->Isaac->stats->current->damage * data->Isaac->weapons[data->Isaac->equipped].damage;
        e->health -= damage ;
        preprocesDamage_Entities(data, e->type);
        knockBack_Entity(e, data, data->Isaac->combat->direction, 0, 0,e->attackTimer);
        DamageIndicator* damageIndicator = init_DamageIndicator();
        damageIndicator->amount = damage;
        damageIndicator->position->x = (Sint16) (e->movement->position->x + (e->movement->spriteBox->w / 2));
        damageIndicator->position->y = (Sint16) (e->movement->position->y - 10);
        start_Timer(damageIndicator->timer);
        enQueue_DamageIndictator(e->damageIndicatorQueue, damageIndicator);
    }
}

extern void knockBack_Entity(Entity* e, struct Data* data, int direction, int x, int y,Timer * timer) {

    if (timer != NULL) {
        start_Timer(timer);
    }

    if (direction == -1) {
        e->movement->velocity->x -= x * 10;
        e->movement->velocity->y -= y * 10;
    } else {
        switch(direction) {
            case 0: {
                e->movement->velocity->y = 10;
                break;
            }

            case 1: {
                e->movement->velocity->y = -10;
                break;
            }

            case 2: {
                e->movement->velocity->x = 10;
                break;
            }

            case 3: {
                e->movement->velocity->x = -10;
                break;
            }

            default: {
                break;
            }
        }
    }
}

extern struct entities_bool* initEntitiesBool() {
    entities_bool* temp = malloc(sizeof(entities_bool));
    if(!temp) {
        exit(EXIT_FAILURE);
    }

    resetEntitiesBool(temp);

    return temp;
}

extern void freeEntitiesBool(struct entities_bool** e) {
    if(e && *e) {
        free(*e);
        *e = NULL;
    }
}

extern void resetEntitiesBool(struct entities_bool* e) {
    e->tree = 0;
    e->moth = 0;
    e->worm = 0;
    e->bossBod = 0;
    e->arm = 0;
}

static void preprocesDamage_Entities(struct Data* data, int type) {
    switch (type) {
        case MOTH: {
            if (data->dungeonScene->sound->mobsDamaged->moth == 0) {
                data->dungeonScene->sound->mobsDamaged->moth = 1;
            }
            break;
        }
        case WORM: {
            if (data->dungeonScene->sound->mobsDamaged->worm == 0) {
                data->dungeonScene->sound->mobsDamaged->worm = 1;
            }
            break;
        }
        case TREE: {
            if (data->dungeonScene->sound->mobsDamaged->tree == 0) {
                data->dungeonScene->sound->mobsDamaged->tree = 1;
            }
            break;
        }
        case ARM: {
            if (data->dungeonScene->sound->mobsDamaged->arm == 0) {
                data->dungeonScene->sound->mobsDamaged->arm = 1;
            }
            break;
        }
        case BOSSBOD: {
            if (data->dungeonScene->sound->mobsDamaged->bossBod == 0) {
                data->dungeonScene->sound->mobsDamaged->bossBod = 1;
            }
            break;
        }
        default:
            break;
    }
}

extern void pauseTimer_entities(EntityList* list) {
    EntityList* temp = list;
    while(temp) {
        pause_Timer(temp->data->shootTimer);
        pause_Timer(temp->data->attackTimer);
        temp = temp->next;
    }
}

extern void unpauseTimer_entities(EntityList* list) {
    EntityList* temp = list;
    while(temp) {
        unpause_Timer(temp->data->attackTimer);
        unpause_Timer(temp->data->shootTimer);
        temp = temp->next;
    }
}