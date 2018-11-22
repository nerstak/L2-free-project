#include <stdlib.h>
#include <stdio.h>

#include "room.h"

#include "../utils/coord.h"

extern Room* init_Room(Coord* coord, Room* parent, Symbol* item, Condition* preCondition) {
    // Initialization of a Room pointer
    Room* myRoom = NULL;
    myRoom = malloc(1 * sizeof(Room));

    // If we failed to allocate, exit the program
    if (myRoom == NULL) {
        printf("An error occured while initializing a Room object");
        exit(EXIT_FAILURE);
    }

    myRoom->coord = coord;
    myRoom->item = item;

    for (int i = 0; i < 4; i += 1) {
        myRoom->edges[i] = initEmpty_Edge();
    }

    myRoom->preCondition = preCondition;
    myRoom->difficulty = 0.0;
    myRoom->parent = parent;

    for (int i = 0; i < 3; i += 1) {
        myRoom->children[i] = NULL;
    }

    myRoom->childrenLength = 0;

    return myRoom;
}

extern void clean_Room(Room** myRoom) {
    // TODO: clean process
}

extern double getDifficulty_Room(Room* myRoom) {
    return myRoom->difficulty;
}

extern void setDifficulty_Room(Room* myRoom, double difficulty) {
    myRoom->difficulty = difficulty;
}

extern Symbol* getItem_Room(Room* myRoom) {
    return myRoom->item;
}

extern void setItem_Room(Room* myRoom, Symbol* item) {
    myRoom->item = item;
}

extern Edge** getEdges_Room(Room* myRoom) {
    return myRoom->edges;
}

extern Edge* getEdge_Room(Room* myRoom, Direction* direction) {
    return myRoom->edges[direction->code];
}

extern int linkAmount(Room* myRoom) {
    int amount = 0;

    for (int i = 0; i < 4; i += 1) {
        if (myRoom->edges[i] != NULL) {
            amount += 1;
        }
    }

    return amount;
}

extern bool isStart_Room(Room* myRoom) {
    return myRoom->item != NULL && isStart_Symbol(myRoom->item);
}

extern bool isGoal_Room(Room* myRoom) {
    return myRoom->item != NULL && isGoal_Symbol(myRoom->item);
}

extern bool isBoss_Room(Room* myRoom) {
    return myRoom->item != NULL && isBoss_Symbol(myRoom->item);
}

extern Condition* getPrecondition_Room(Room* myRoom) {
    return myRoom->preCondition;
}

extern void setPrecondition_Room(Room* myRoom, Condition* preCondition) {
    myRoom->preCondition = preCondition;
}

extern Room* getParent_Room(Room* myRoom) {
    return myRoom->parent;
}

extern void setParent_Room(Room* myRoom, Room* parent) {
    myRoom->parent = parent;
}

extern Room** getChildren_Room(Room* myRoom) {
    return myRoom->children;
}

extern void addChild_Room(Room* myRoom, Room* child) {
    int i;

    for (i = 0; i < 4; i += 1) {
        if (myRoom->children[i] == NULL) {
            break;
        }
    }

    myRoom->children[i] = child;
    myRoom->childrenLength += 1;
}

extern void printf_Room(Room* myRoom) {
    printf("Room: ");
    printf_Coord(myRoom->coord);
}