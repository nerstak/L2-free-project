#include <stdlib.h>
#include <string.h>

#include "player.h"

extern Weapon* init_Weapon() {
    Weapon* result = NULL;
    result = malloc(4 * sizeof(Weapon));

    if (result == NULL) {
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 4; i += 1) {
        result[i].damage = 0;
        result[i].agility = 0;

        result[i].name[0] = 0;
        result[i].description[0] = 0;
    }

    return result;
}

extern void clean_Weapon(Weapon** p) {
    if ((*p) != NULL) {
        free((*p));
        (*p) = NULL;
    }
}

extern CombatValues* init_Combat() {
    CombatValues* result = NULL;
    result = malloc(1 * sizeof(CombatValues));

    if (result == NULL) {
        exit(EXIT_FAILURE);
    }

    result->animationStep = 0;
    result->direction = 0;

    result->spriteBox = malloc(1 * sizeof(SDL_Rect));
    result->weaponHitBox = malloc(1 * sizeof(SDL_Rect));

    if (result->spriteBox == NULL || result->weaponHitBox == NULL) {
        exit(EXIT_FAILURE);
    }

    result->timeSince = init_Timer();

    return result;
}

extern void clean_Combat(CombatValues** p) {
    if ((*p) != NULL) {
        free((*p)->spriteBox);
        free((*p)->weaponHitBox);
        clean_Timer(&((*p)->timeSince));

        free((*p));
        (*p) = NULL;
    }
}


extern Player* init_Player() {
    Player* Isaac = malloc(sizeof(Player));
    if(!Isaac) {
        printf("Fail to init player.");
        exit(EXIT_FAILURE);
    }

    // Initialize all pointers to NULL (either way it's junk memory)
    Isaac->stats = NULL;
    Isaac->weapons = NULL;
    Isaac->gameStats = NULL;
    Isaac->invulnerabilityTimer = NULL;
    Isaac->movement = NULL;
    Isaac->combat = NULL;
    Isaac->inventory = NULL;


    //Initialisation of stats
    Isaac->stats = malloc(sizeof(generalStats));
    if(!Isaac->stats) {
        printf("Fail to init general stats of the player.");
        exit(EXIT_FAILURE);
    }


    // Initialize all pointers to NULL (either way it's junk memory)
    Isaac->stats->current = NULL;
    Isaac->stats->basic = NULL;
    Isaac->stats->max = NULL;
    Isaac->stats->potionsUsed = NULL;

    Isaac->stats->current = malloc(sizeof(stats_entity));
    Isaac->stats->basic = malloc(sizeof(stats_entity));
    Isaac->stats->max = malloc(sizeof(stats_entity));
    Isaac->stats->potionsUsed = calloc(6, sizeof(int));

    if(!Isaac->stats->max || !Isaac->stats->basic || !Isaac->stats->current || !Isaac->stats->potionsUsed) {
        printf("Fail to init stats of the player.");
        exit(EXIT_FAILURE);
    }

    Isaac->weapons = init_Weapon();
    if(!Isaac->weapons) {
        printf("Fail to init Player weapons'.");
        exit(EXIT_FAILURE);
    }

    Isaac->gameStats = malloc(sizeof(GameStats));
    if(!Isaac->gameStats) {
        printf("Fail to init GameStats'.");
        exit(EXIT_FAILURE);
    }

    Isaac->invulnerabilityTimer = init_Timer();
    if(!Isaac->invulnerabilityTimer) {
        printf("Fail to init Invulnity frames'.");
        exit(EXIT_FAILURE);
    }

    //Initialisation of coordinates and movement
    //Those coordinates will have to correspond to the one of the lobby
    Isaac->movement = init_Movement();
    if(!Isaac->movement) {
        printf("Fail to init movement of player.");
        exit(EXIT_FAILURE);
    }

    Isaac->movement->position->x = 640;
    Isaac->movement->position->y = 400;

    Isaac->movement->velocity->x = 0;
    Isaac->movement->velocity->y = 0;

    Isaac->movement->spriteBox->x = 0;
    Isaac->movement->spriteBox->y = 0;
    Isaac->movement->spriteBox->h = 128;
    Isaac->movement->spriteBox->w = 64;

    Isaac->movement->hitBox->h = 64;
    Isaac->movement->hitBox->w = 64;

    Isaac->movement->animationStep = 0;
    Isaac->movement->direction = 0;
    Isaac->movement->stepChannel = -1;

    Isaac->combat = init_Combat();
    Isaac->combat->direction=-1;
    Isaac->combat->animationStep=0;
    Isaac->combat->damageJustTaken = 0;

    return Isaac;
}

extern void free_Player(Player** Isaac) {
    if((*Isaac)->movement) {
        clean_Movement(&((*Isaac)->movement));
    }

    if((*Isaac)->weapons) {
        clean_Weapon(&((*Isaac)->weapons));
    }

    if ((*Isaac)->combat) {
        clean_Combat(&((*Isaac)->combat));
    }

    if((*Isaac)->stats) {
        if((*Isaac)->stats->max) {
            free((*Isaac)->stats->max);
            (*Isaac)->stats->max = NULL;
        }

        if((*Isaac)->stats->current) {
            free((*Isaac)->stats->current);
            (*Isaac)->stats->current = NULL;
        }

        if((*Isaac)->stats->basic) {
            free((*Isaac)->stats->basic);
            (*Isaac)->stats->basic = NULL;
        }

        if((*Isaac)->stats->potionsUsed) {
            free((*Isaac)->stats->potionsUsed);
            (*Isaac)->stats->potionsUsed = NULL;
        }

        free((*Isaac)->stats);
        (*Isaac)->stats = NULL;        
    }
    
    

    if((*Isaac)->gameStats) {
        free((*Isaac)->gameStats);
        (*Isaac)->gameStats = NULL;
    }

    freeAll_SlotInventory(&((*Isaac)->inventory));

    free(*Isaac);
    *Isaac = NULL;
}

//Change the balance of the wallet, IFF possible (return 1 if done)
extern int alterMoney_Player(Player* Isaac, int alterMoney) {
    if (Isaac->money + alterMoney >= 0 && Isaac->money + alterMoney <= 15000) {
        Isaac->money = Isaac->money + alterMoney;
        return 1;
    }
    return 0;
}

//Change the health of the Player. 'b' for definitif, 'c' for temp
extern void alterHealth_Player(Player* Isaac, float alterHealth, char type) {
    switch(type) {
        case 'c': {
            Isaac->stats->current->health = (alterHealth + Isaac->stats->current->health);

            if(Isaac->stats->current->health > Isaac->stats->basic->health) {
                Isaac->stats->current->health = Isaac->stats->basic->health;
            }
            if (Isaac->stats->current->health <= 0) {
                Isaac->stats->current->health = 0;
            }
            break;
        }
        case 'b': {
            Isaac->stats->basic->health = (alterHealth + Isaac->stats->basic->health);

            if(Isaac->stats->basic->health > Isaac->stats->max->health) {
                Isaac->stats->basic->health = Isaac->stats->max->health;
            }
            if (Isaac->stats->basic->health <= 0) {
                Isaac->stats->basic->health = 0;
            }
            Isaac->stats->current->health = Isaac->stats->basic->health;
            break;
        }
        default: break;
    }
}

//Change the speed of the Player. 'b' for definitif, 'c' for temp
extern void alterSpeed_Player(Player* Isaac, float alterSpeed, char type) {
    switch(type) {
        case 'c': {
            Isaac->stats->current->speed = (alterSpeed + Isaac->stats->current->speed);

            if(Isaac->stats->current->speed > Isaac->stats->max->speed) {
                Isaac->stats->current->speed = Isaac->stats->max->speed;
            }
            if (Isaac->stats->current->speed <= 0) {
                Isaac->stats->current->speed = 0;
            }
            break;
        }
        case 'b': {
            Isaac->stats->basic->speed = (alterSpeed + Isaac->stats->basic->speed);

            if(Isaac->stats->basic->speed > Isaac->stats->max->speed) {
                    Isaac->stats->basic->speed = Isaac->stats->max->speed;
            }
            if (Isaac->stats->basic->speed <= 0) {
                Isaac->stats->basic->speed = 0;
            }

            alterSpeed_Player(Isaac,Isaac->stats->basic->speed - Isaac->stats->current->speed, 'c');
            break;
        }
        default: break;
    }
}

//Change the agility of the Player. 'b' for definitif, 'c' for temp
extern void alterAgility_Player(Player* Isaac, float alterAgility, char type) {
    switch(type) {
        case 'c': {
            Isaac->stats->current->agility = (alterAgility + Isaac->stats->current->agility);

            if(Isaac->stats->current->agility > Isaac->stats->max->agility) {
                    Isaac->stats->current->agility = Isaac->stats->max->agility;
                }
            if (Isaac->stats->current->agility <= 0) {
                Isaac->stats->current->agility = 0;
            }
            break;
        }
        case 'b': {
            Isaac->stats->basic->agility = (alterAgility + Isaac->stats->basic->agility);

            if(Isaac->stats->basic->agility > Isaac->stats->max->agility) {
                Isaac->stats->basic->agility = Isaac->stats->max->agility;
            }
            if (Isaac->stats->basic->agility <= 0) {
                Isaac->stats->basic->agility = 0;
            }
            alterAgility_Player(Isaac,Isaac->stats->basic->agility - Isaac->stats->current->agility, 'c');
            break;
        }
        default: break;
    }
}

//Change the damage of the Player. 'b' for definitif, 'c' for temp
extern void alterDamage_Player(Player* Isaac, float alterDamage, char type) {
    switch(type) {
        case 'c': {
            Isaac->stats->current->damage = (alterDamage + Isaac->stats->current->damage);

            if(Isaac->stats->current->damage > Isaac->stats->max->damage) {
                Isaac->stats->current->damage = Isaac->stats->max->damage;
            }
            if (Isaac->stats->current->damage <= 0) {
                Isaac->stats->current->damage = 0;
            }
            break;
        }
        case 'b': {
            Isaac->stats->basic->damage = (alterDamage + Isaac->stats->basic->damage);

            if(Isaac->stats->basic->damage > Isaac->stats->max->damage) {
                Isaac->stats->basic->damage = Isaac->stats->max->damage;
            }
            if (Isaac->stats->basic->damage <= 0) {
                Isaac->stats->basic->damage = 0;
            }
            alterDamage_Player(Isaac,Isaac->stats->basic->damage - Isaac->stats->current->damage, 'c');
            break;
        }
        default: break;
    }
}

extern int isPlayerAlive(Player* Isaac) {
    if(Isaac->stats->current->health <= 0) {
        return 0;
    }
    return 1;
}

extern void resetStats(Player* Isaac) {
    resetUsedPotions(Isaac->stats);

    Isaac->stats->current->agility = Isaac->stats->basic->agility;
    Isaac->stats->current->damage = Isaac->stats->basic->damage;
    Isaac->stats->current->health = Isaac->stats->basic->health;
    Isaac->stats->current->speed = Isaac->stats->basic->speed;
}