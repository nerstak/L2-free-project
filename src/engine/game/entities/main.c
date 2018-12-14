#include <stdlib.h>

#include "main.h"
#include "moth.h"
#include "worm.h"
#include "tree.h"
#include "projectile.h"

#include "../movement.h"
#include "../combat.h"

extern EntityList* init_EntityNode(int type) {
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
            result->entity = init_EMoth();

            result->health = 3;
            result->damage = 1;
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
            result->entity = init_EWorm();

            result->health = 2;
            result->damage = 1;
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

            result->health = 2;
            result->damage = 1;
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
            result->entity = init_EProjectile();

            result->health = 1;
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
        // TODO: printf error
        exit(EXIT_FAILURE);
    }

    result->amount = 0;
    result->position = NULL;
    result->timer = init_Timer();

    result->position = malloc(1 * sizeof(SDL_Rect));

    if (result->position == NULL) {
        // TODO: printf error
        exit(EXIT_FAILURE);
    }

    return result;
}

extern DamageIndicatorQueue* initQueue_DamageIndicator() {
    DamageIndicatorQueue* result = NULL;
    result = malloc(1 * sizeof(DamageIndicatorQueue));

    if (result == NULL) {
        // TODO: printf error
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
        // TODO: Printf error
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
    (*list) = killList_Entity((*list),&(data->dyingEntities));
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

extern EntityList* killList_Entity(EntityList* list, EntityList** dying) {
    if (list == NULL) {
        return NULL;
    } else if (list->data->health <= 0) {
        EntityList* temp = list->next;
        //TODO free if its a projectile
        list->data->movement->animationStep=0;
        append_EntityNode(list,dying);
        return temp;
    }

    list->next = killList_Entity(list->next,dying);

    return list;
}

extern EntityList* cloudList_Entity(EntityList* list){
    if (list == NULL) {
        return NULL;
    } else if (list->data->movement->animationStep >= 1000 || list->data->type==5) {
        EntityList* temp = list->next;
        //TODO free here
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
        }
    }

    if (BoxCollision(e->movement->hitBox, data->Isaac->combat->weaponHitBox) && !e->attackTimer->started && e->type!=PROJECTILE) {
        e->health -= 10;//data->Isaac->stats->current->damage * data->Isaac->weapons->damage;
        knockBack_Entity(e, data, data->Isaac->combat->direction, 0, 0,e->attackTimer);
        DamageIndicator* damageIndicator = init_DamageIndicator();
        damageIndicator->amount = 1;
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