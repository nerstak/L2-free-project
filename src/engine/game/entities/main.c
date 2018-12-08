#include <stdlib.h>

#include "main.h"
#include "moth.h"
#include "../movement.h"
#include "../combat.h"

extern Entity* init_Entity(int type) {
    Entity* result  = NULL;
    result = malloc(1 * sizeof(Entity));

    if (result == NULL) {
        exit(EXIT_FAILURE);
    }

    result->damageIndicatorQueue = initQueue_DamageIndicator();

    switch(type) {
        case MOTH: {
            result->type = MOTH;
            result->entity = init_EMoth();

            result->health = 5;
            result->damage = 0;
            result->speed = 1;

            result->movement = init_Movement();

            result->movement->animationStep=0;
            result->type=0;
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

            break;
        }

        default: {
            free(result);
            return NULL;

            break;
        }
    }

    return result;
}

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
    if ((*p)->rear == NULL) {
        free(*p);
        (*p) = NULL;
    } else {
        DamageIndicatorQueueNode* temp = NULL;
        while ((*p)->rear != NULL) {
            temp = (*p)->front;
            (*p)->front = (*p)->front->next;

            free(temp);

            if ((*p)->front == NULL) {
                (*p)->rear = NULL;
            }
        }

        free((*p));
        (*p) = NULL;
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
    (*list) = killList_Entity((*list));

    // We go through the whole list of monsters and apply actions depending of the type of monsters
    EntityList* temp = (*list);

    while(temp) {
        switch(temp->data->type) {
            case MOTH: {
                ai_EMoth(temp->data, data);

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

extern EntityList* killList_Entity(EntityList* list) {
    if (list == NULL) {
        return NULL;
    } else if (list->data->health <= 0) {
        EntityList* temp = list->next;

        return temp;
    }

    list->next = killList_Entity(list->next);

    return list;
}

extern void damage_Entity(Entity* e, struct Data* data, double x, double y) {
    if (BoxCollision(e->movement->hitBox, data->Isaac->movement->hitBox)) {
        knockBack_Entity(e, data, -1, x, y);

        if (data->Isaac->invulnerabilityTimer->started == false) {
            start_Timer(data->Isaac->invulnerabilityTimer);
            alterHealth_Player(data->Isaac, e->damage, 'c');
        }
    }

    if (BoxCollision(e->movement->hitBox, data->Isaac->combat->weaponHitBox) && !e->attackTimer->started) {
        e->health -= 1;

        DamageIndicator* damageIndicator = init_DamageIndicator();
        damageIndicator->amount = 1;
        damageIndicator->position->x = (Sint16) (e->movement->position->x + (e->movement->spriteBox->w / 2));
        damageIndicator->position->y = (Sint16) (e->movement->position->y - 10);
        start_Timer(damageIndicator->timer);
        enQueue_DamageIndictator(e->damageIndicatorQueue, damageIndicator);

        knockBack_Entity(e, data, data->Isaac->combat->direction, 0, 0);
    }
}

extern void knockBack_Entity(Entity* e, struct Data* data, int direction, int x, int y) {

    if (e->attackTimer != NULL) {
        start_Timer(e->attackTimer);
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