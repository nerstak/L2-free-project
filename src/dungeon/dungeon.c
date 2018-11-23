#include <stdlib.h>
#include <stdio.h>

#include "dungeon.h"
#include "roomlist.h"

static void convertTreeToList(KeyLevelRoomMapping* keylevel, TreeMapNode* node);

extern Dungeon* init_Dungeon() {
    // Initialization of a Dungeon pointer
    Dungeon* p = NULL;
    p = malloc(1 * sizeof(Dungeon));

    // If we failed to allocate, exit the program
    if (p == NULL) {
        printf("An error occured while initializing a Dungeon object");
        exit(EXIT_FAILURE);
    }

    p->rooms = init_TreeMap();
    p->bounds = init_Bounds(0, 0, 0, 0);

    return p;
}

extern void clean_Dungeon(Dungeon** p) {
    // TODO: clean process
}

extern Bounds* getExtentBounds_Dungeon(Dungeon* p) {
    return p->bounds;
}

extern struct KeyLevelRoomMapping* getRooms_Dungeon(Dungeon* p) {
    KeyLevelRoomMapping* keylevel = init_KeyLevelRoomMapping();

    convertTreeToList(keylevel, p->rooms->root);

    return keylevel;
}

static void convertTreeToList(KeyLevelRoomMapping* keylevel, TreeMapNode* node) {
    if (node != NULL) {
        addRoom_KeyLevelRoomMapping(keylevel, 0, node->value);

        convertTreeToList(keylevel, node->link[0]);
        convertTreeToList(keylevel, node->link[1]);
    }
}

extern int roomCount_Dungeon(Dungeon* p) {
    return size_TreeMap(p->rooms->root);
}

extern Room* getByCoord_Dungeon(Dungeon* p, Coord* c) {
    TreeMapNode* result = get_TreeMap(p->rooms, c);

    if (result == NULL) {
        return NULL;
    }

    return result->value;
}

extern Room* getByCoordAlt_Dungeon(Dungeon* p, int x, int y) {
    Coord* temp = init_Coord(x, y);
    Room* result = getByCoord_Dungeon(p, temp);
    clean_Coord(&temp);

    return result;
}

extern void add_Dungeon(Dungeon* p, Room* r) {
    put_TreeMap(p->rooms, r);

    if (r->coord->x < p->bounds->left) {
        Bounds* temp = p->bounds;
        p->bounds = init_Bounds(r->coord->x, p->bounds->top, p->bounds->right, p->bounds->bottom);
        clean_Bounds(&temp);
    }

    if (r->coord->x > p->bounds->right) {
        Bounds* temp = p->bounds;
        p->bounds = init_Bounds(p->bounds->left, p->bounds->top, r->coord->x, p->bounds->bottom);
        clean_Bounds(&temp);
    }

    if (r->coord->y < p->bounds->top) {
        Bounds* temp = p->bounds;
        p->bounds = init_Bounds(p->bounds->left, r->coord->y, p->bounds->right, p->bounds->bottom);
        clean_Bounds(&temp);
    }

    if (r->coord->y > p->bounds->bottom) {
        Bounds* temp = p->bounds;
        p->bounds = init_Bounds(p->bounds->left, p->bounds->top, p->bounds->right, r->coord->y);
        clean_Bounds(&temp);
    }
}

extern void linkOneWay_Dungeon(Dungeon* p, Room* r1, Room* r2, Symbol* c) {
    if (get_TreeMap(p->rooms, r1->coord) == NULL && get_TreeMap(p->rooms, r2->coord)) {
        // Err

        return;
    }

    if (!isAdjacent_Coord(r1->coord, r2->coord)) {
        // Err

        return;
    }

    Direction* d = getDirectionTo_Coord(r1->coord, r2->coord);
    getEdges_Room(r1)[d->code] = init_Edge(c);
}

extern void link_Dungeon(Dungeon* p, Room* r1, Room* r2, Symbol* c) {
    if (get_TreeMap(p->rooms, r1->coord) == NULL && get_TreeMap(p->rooms, r2->coord)) {
        // Err

        return;
    }

    if (!isAdjacent_Coord(r1->coord, r2->coord)) {
        // Err

        return;
    }

    Direction* d = getDirectionTo_Coord(r1->coord, r2->coord);
    getEdges_Room(r1)[d->code] = init_Edge(c);
    getEdges_Room(r2)[opposite_Direction(d)->code] = init_Edge(c);

    clean_Direction(&d);
}


extern bool areRoomsLinked_Dungeon(Room* r1, Room* r2) {
    Direction* d = getDirectionTo_Coord(r1->coord, r2->coord);
    bool result = getEdge_Room(r1, d) != NULL || getEdge_Room(r2, d) != NULL;

    if (d != NULL) {
        clean_Direction(&d);
    }

    return result;
}

extern Room* findStart_Dungeon(Dungeon* p) {
    return NULL;
}

extern Room* findBoss_Dungeon(Dungeon* p) {
    return NULL;
}

extern Room* findGoal_Dungeon(Dungeon* p) {
    return NULL;
}