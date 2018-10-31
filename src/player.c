#include "player.h"

//Change the balance of the wallet, IFF possible (return 1 if done)
int alter_money(Player *Isaac, int money_change) {
    if (Isaac->money + money_change >= 0) {
        Isaac->money = Isaac->money + money_change;
        return 1;
    }
    return 0;
}

//Change the current health between the max and 0
void alter_health(Player *Isaac, int alter_health) {
    if(alter_health >= 0) {
        //Modulo max_health + 1 to be able to reach that max health
        Isaac->current_stats->health = (alter_health + Isaac->current_stats->health) % (Isaac->basic_stats->health + 1);
    } else {
        Isaac->current_stats->health = (alter_health + Isaac->current_stats->health);
        if(Isaac->current_stats->health <= 0) {
            Isaac->current_stats->health = 0;
        }
    }
}

//Put functions relative to the player

void player_logic_lobby(Data* data)
{

}
