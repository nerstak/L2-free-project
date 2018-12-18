#include <stdlib.h>

#include "boss.h"
#include "arm.h"
#include "main.h"
#include "../../../utils/math.h"
#include "../movement.h"
#include "projectile.h"


extern E_Boss* init_EBoss(float maxhealth, float difficulty)
{
    E_Boss* result = NULL;
    result = malloc(1 * sizeof(E_Boss));

    if (result == NULL) {
        exit(EXIT_FAILURE);
    }

    EntityList * temp= init_EntityNode(ARM, difficulty);
    result->leftarm=temp->data;
    free(temp);



    temp= init_EntityNode(ARM, difficulty);
    result->rightarm=temp->data;
    free(temp);

    result->rightarm->movement->direction=0;
    result->leftarm->movement->direction=1;

    result->leftarm->movement->position->x=431;
    result->leftarm->movement->position->y=186;
    result->rightarm->movement->position->x=731;
    result->rightarm->movement->position->y=186;
    result->rightarm->health=maxhealth;
    result->leftarm->health=maxhealth;

    // Default value
    result->rightsprite=malloc(sizeof(SDL_Rect));
    result->leftsprite=malloc(sizeof(SDL_Rect));
    result->leftsprite->h=288;
    result->leftsprite->w=192;
    result->rightsprite->h=288;
    result->rightsprite->w=192;

    return result;
}
extern void clean_EBoss(E_Boss** p)
{
    free((*p)->rightsprite);
    free((*p)->leftsprite);
    clean_Entity(&((*p)->rightarm));
    clean_Entity(&((*p)->leftarm));
    free(*p);
    (*p)=NULL;
}


extern void ai_EBoss(Entity* e, Data* data) {
    int timeChange = lap_Timer(e->movement->timeSince);
    if (timeChange > 300 || timeChange < -300) {
        timeChange = 0;
    }

    E_Boss *arms = (E_Boss *) (e->entity);


    if (arms->rightarm != NULL) {
        ai_EArm(arms->rightarm, data, e->health / 2);
        if (arms->rightarm->health <= 0) {
            arms->rightarm = NULL;
        }
    }

    if (arms->leftarm != NULL) {
        ai_EArm(arms->leftarm, data, e->health / 2);
        if (arms->leftarm->health <= 0) {
            arms->leftarm = NULL;
        }
    }

    e->movement->hitBox->x = (Sint16) (e->movement->position->x + 100);
    e->movement->hitBox->y = (Sint16) (e->movement->position->y);

    if (e->attackTimer->started) {
        cap_Timer(e->attackTimer, 500);
    }

    if (arms->rightarm == NULL && arms->leftarm == NULL) {
        if (e->shootTimer->started && getTicks_Timer(e->shootTimer)>400) {
            cap_Timer(e->shootTimer, 1500);
        } else if(getTicks_Timer(e->shootTimer)<400){
            Coordinate *source = malloc(sizeof(Coordinate));
            source->x = e->movement->position->x + 181;
            source->y = e->movement->position->y + 220;

            shoot_Projectile(data, source, 5, e->damage, 1100, e->type);
            if(!e->shootTimer->started) {
                data->dungeonScene->sound->mobsAttack->bossBod = 1;
                lap_Timer(e->shootTimer);
            }
        }
    }
    else
    {
        if (e->shootTimer->started) {
            cap_Timer(e->shootTimer, 1200);
        }
        else{
            int choice=rand()%2;
            if(choice==0 || (arms->leftarm!=NULL && arms->rightarm==NULL )) {
                if (arms->leftarm!=NULL) {
                    punch(data, arms->leftarm, data->Isaac->movement->position, e->health / 2,
                          data->dungeonScene->currentRoom->layout->map);
                }
            }
            else {
                if (arms->rightarm!=NULL) {
                    punch(data, arms->rightarm, data->Isaac->movement->position, e->health / 2,
                          data->dungeonScene->currentRoom->layout->map);
                }
            }
            lap_Timer(e->shootTimer);
        }
    }

    animate_EBoss(e,timeChange,arms);

    float saved=e->health;

    damage_Entity(e, data, 0, 0);

    if(arms->rightarm != NULL || arms->leftarm != NULL)
    {
        e->health=saved;
    }


}



extern void animate_EBoss(Entity* e, int time,E_Boss * arms)
{
    e->movement->animationStep = (e->movement->animationStep + time) % 1000;
    int step=abs( (e->movement->animationStep / 250) - 2);
    if(arms->leftarm == NULL && arms->rightarm == NULL)
    {
        e->movement->spriteBox->x= 1152;
        e->movement->spriteBox->y= (Sint16) (288 * step);
    }
    else
    {
        int state=0;
        if(arms->leftarm!=NULL)
        {
            if(arms->leftarm->health <= e->health/4)
            {
                state=1;
            }
            arms->leftsprite->x= (Sint16) (384 * state);
        }
        else{
            arms->leftsprite->x= (Sint16) (768);
        }
        arms->leftsprite->y= (Sint16) (288 * step);


        state=0;
        if(arms->rightarm!=NULL)
        {
            if(arms->rightarm->health <= e->health/4)
            {
                state=1;
            }
            arms->rightsprite->x= (Sint16) ((384 * state)+192);
        }
        else{
            arms->rightsprite->x= (Sint16) (960);
        }
        arms->rightsprite->y= (Sint16) (288 * step);

    }





}


