#ifndef MONSTERS_H_INCLUDED
#define MONSTERS_H_INCLUDED

//#include "../data.h"

typedef struct Monster
{
    MovementValues * movement;
    int type;
    float MaxHealth;
    float Health;
    float Damage;
    float Speed;
    int AttackTimer;
}Monster;

typedef struct MonsterNode
{
    Monster * monster;
    struct MonsterNode * next;
}MonsterNode;

typedef MonsterNode * MonsterLList;


extern void ProcessMonsters(Player * Isaac,MonsterLList * monsters);

extern void MothAI(Monster * moth, Player * Isaac);
extern void MothAnimate(MovementValues * movement,double Xdistance,int time);

extern MonsterLList KillMonsters(MonsterLList monsters);
extern void freemonster(MonsterLList monster);
extern void Damage(Monster * mob,Player * Isaac);

#endif // MONSTERS_H_INCLUDED
