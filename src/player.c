#include <stdlib.h>
#include <string.h>

#include "player.h"

//Change the balance of the wallet, IFF possible (return 1 if done)
int alterMoney(Player* Isaac, int money_change) {
    if (Isaac->money + money_change >= 0 && Isaac->money + money_change <= 15000) {
        Isaac->money = Isaac->money + money_change;
        return 1;
    }
    return 0;
}

//Change the health of the Player. 'b' for definitif, 'c' for temp
void alterHealth(Player* Isaac, float alterHealth, char type) {
    switch(type) {
        case 'c': {
            Isaac->current_stats->health = (alterHealth + Isaac->current_stats->health);

            if(Isaac->current_stats->health > Isaac->basic_stats->health) {
                Isaac->current_stats->health = Isaac->basic_stats->health;
            }
            if (Isaac->current_stats->health <= 0) {
                Isaac->current_stats->health = 0;
            }
            break;
        }
        case 'b': {
            Isaac->basic_stats->health = (alterHealth + Isaac->basic_stats->health);

            if(Isaac->basic_stats->health > Isaac->maxStats->health) {
                Isaac->basic_stats->health = Isaac->maxStats->health;
            }
            if (Isaac->basic_stats->health <= 0) {
                Isaac->basic_stats->health = 0;
            }
            break;
        }
        default: break;
    }
}

//Change the speed of the Player. 'b' for definitif, 'c' for temp
void alterSpeed(Player* Isaac, float alterSpeed, char type) {
    switch(type) {
        case 'c': {
            Isaac->current_stats->speed = (alterSpeed + Isaac->current_stats->speed);

            if(Isaac->current_stats->speed > Isaac->basic_stats->speed) {
                Isaac->current_stats->speed = Isaac->basic_stats->speed;
            }
            if (Isaac->current_stats->speed <= 0) {
                Isaac->current_stats->speed = 0;
            }
            break;
        }
        case 'b': {
            Isaac->basic_stats->speed = (alterSpeed + Isaac->basic_stats->speed);

            if(Isaac->basic_stats->speed > Isaac->maxStats->speed) {
                    Isaac->basic_stats->speed = Isaac->maxStats->speed;
            }
            if (Isaac->basic_stats->speed <= 0) {
                Isaac->basic_stats->speed = 0;
            }
            break;
        }
        default: break;
    }
}

//Change the agility of the Player. 'b' for definitif, 'c' for temp
void alterAgility(Player* Isaac, float alterAgility, char type) {
    switch(type) {
        case 'c': {
            Isaac->current_stats->agility = (alterAgility + Isaac->current_stats->agility);

            if(Isaac->current_stats->agility > Isaac->basic_stats->agility) {
                    Isaac->current_stats->agility = Isaac->basic_stats->agility;
                }
            if (Isaac->current_stats->agility <= 0) {
                Isaac->current_stats->agility = 0;
            }
            break;
        }
        case 'b': {
            Isaac->basic_stats->agility = (alterAgility + Isaac->basic_stats->agility);

            if(Isaac->basic_stats->agility > Isaac->maxStats->agility) {
                Isaac->basic_stats->agility = Isaac->maxStats->agility;
            }
            if (Isaac->basic_stats->agility <= 0) {
                Isaac->basic_stats->agility = 0;
            }
        }
        default: break;
    }
}

//Change the damage of the Player. 'b' for definitif, 'c' for temp
void alterDamage(Player* Isaac, float alterDamage, char type) {
    switch(type) {
        case 'c': {
            Isaac->current_stats->damage = (alterDamage + Isaac->current_stats->damage);

            if(Isaac->current_stats->damage > Isaac->basic_stats->damage) {
                Isaac->current_stats->damage = Isaac->basic_stats->damage;
            }
            if (Isaac->current_stats->damage <= 0) {
                Isaac->current_stats->damage = 0;
            }
            break;
        }
        case 'b': {
            Isaac->basic_stats->damage = (alterDamage + Isaac->basic_stats->damage);

            if(Isaac->basic_stats->damage > Isaac->maxStats->damage) {
                Isaac->basic_stats->damage = Isaac->maxStats->damage;
            }
            if (Isaac->basic_stats->damage <= 0) {
                Isaac->basic_stats->damage = 0;
            }
        }
        default: break;
    }
}