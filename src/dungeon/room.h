#ifndef FREE_PROJECT_DUNGEONS_ROOM_H
#define FREE_PROJECT_DUNGEONS_ROOM_H

#include <stdlib.h>

#include "condition.h"
#include "../utils/coord.h"
#include "edge.h"

typedef struct Room {
    Condition* preCondition;
    Coord* coord;
    Symbol* item;
    Edge* edges[4];
    double difficulty;
    size_t childrenLength;
    struct Room* parent;
    struct Room* children[];
} Room;

extern Room* init_Room(Coord* coord, Room* parent, Symbol* item, Condition* preCondition);
extern void clean_Room(Room** myRoom);
extern double getDifficulty_Room(Room* myRoom);
extern void setDifficulty_Room(Room* myRoom, double difficulty);
extern Symbol* getItem_Room(Room* myRoom);
extern void setItem_Room(Room* myRoom, Symbol* item);
extern Edge** getEdges_Room(Room* myRoom);
extern Edge* getEdge_Room(Room* myRoom, Direction* direction);
/**
extern int linkAmount_Room(Room* myRoom);

extern bool isStart_Room(Room* myRoom);
extern bool isGoal_Room(Room* myRoom);
extern bool isBoss_Room(Room* myRoom);

extern Condition* getPrecondition_Room(Room* myRoom);
extern void setPrecondition_Room(Room* myRoom, Condition* preCondition);

extern Room* getParent_Room(Room* myRoom);
extern void setParent_Room(Room* myRoom, Room* parent);
extern Room** getChildren_Room(Room* myRoom);
extern void addChild_Room(Room* myRoom, Room* child);

extern void printf_Room(Room* myRoom);

#endif //FREE_PROJECT_DUNGEONS_ROOM_H
