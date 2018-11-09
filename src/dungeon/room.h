#ifndef FREE_PROJECT_TEST_ROOM_H
#define FREE_PROJECT_TEST_ROOM_H

#include "condition.h"
#include "../utils/coord.h"
#include "edge.h"

typedef struct Room {
    Condition* preCondition;
    Coord* coord;
    Symbol* item;
    Edge* edges[4];
    double difficulty;
    struct Room* parent;
    struct Room* children[];
} Room;

extern Room* init_Room(Coord* coord, Room* parent, Symbol* item, Condition* preCondition);
extern double getDifficulty_Room(Room* myRoom);
extern void setDifficulty_Room(Room* myRoom, double difficulty);
extern Symbol* getItem_Room(Room* myRoom);
extern void setItem_Room(Room* myRoom, Symbol* item);
extern Edge** getEdges_Room(Room* myRoom);
extern Edge* getEdge(Room* myRoom, Direction* direction);
extern int linkAmount(Room* myRoom);

extern bool isStart_Room(Room* myRoom);
extern bool isGoal_Room(Room* myRoom);
extern bool isBoss_Room(Room* myRoom);

extern Condition* getPrecondition_Room(Room* myRoom);
extern void setPrecondition_Room(Room* myRoom, Condition* preCondition);

extern Room* getParent_Room(Room* myRoom);
extern Room* setParent_Room(Room* myRoom, Room* parent);
extern Room** getChildren_Room(Room* myRoom);
extern void addChild_Room(Room* myRoom, Room* child);

extern void printf_Room(Room* myRoom);

#endif //FREE_PROJECT_TEST_ROOM_H
