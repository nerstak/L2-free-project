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