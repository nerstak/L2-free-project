#include <stdlib.h>
#include <stdio.h>

#include "treemap.h"
#include "queue.h"

static bool isRed(TreeMapNode* root);

static TreeMapNode* singleRotation(TreeMapNode* root, int dir);
static TreeMapNode* doubleRotation(TreeMapNode* root, int dir);
static int assert(TreeMapNode* root);
static TreeMapNode* createNode(Room* value);
static TreeMapNode* insertRecursively(TreeMapNode* root, Room* value);
static TreeMapNode* removeRecursively(TreeMapNode* root, Room* value, int* done);
static TreeMapNode* removeBalance(TreeMapNode* root, int dir, int* done);

extern TreeMap* init_TreeMap() {
    // Initialization of a TreeMap pointer
    TreeMap* myTreeMap = NULL;
    myTreeMap = malloc(1 * sizeof(TreeMap));

    // If we failed to allocate, exit the program
    if (myTreeMap == NULL) {
        printf("An error occured while initializing a TreeMap object");
        exit(EXIT_FAILURE);
    }

    myTreeMap->root = NULL;

    return myTreeMap;
}

extern void clean_TreeMap(TreeMap** tree) {
    TreeMapNode* temp = (*tree)->root;
    TreeMapNode* save = NULL;

    while (temp != NULL) {
        if (temp->link[0] == NULL) {
            save = temp->link[1];

            clean_Room(&(save->value));

            free(temp);
        } else {
            save = temp->link[0];
            temp->link[0] = save->link[1];
            save->link[1] = temp;
        }

        temp = save;
    }

    free(*tree);
    (*tree) = NULL;
}

extern void printf_TreeMap(TreeMap* tree) {
    Queue* queue = init_Queue();
    TreeMapNode* temp = tree->root;

    while (temp != NULL) {
        if (temp->link[0]) {
            enQueue_Queue(queue, temp->link[0]);
        }

        if (temp->link[1]) {
            enQueue_Queue(queue, temp->link[1]);
        }

        temp = deQueue_Queue(queue);
    }
}


extern TreeMapNode* get_TreeMap(TreeMap* tree, Coord* myCoord) {
    TreeMapNode* temp = tree->root;

    while (temp != NULL) {
        // Duplicate or not ?
        int cmp = compareTo_Coord(temp->key, myCoord);

        if (cmp == 0) {
            break;
        }

        temp = temp->link[cmp < 0];
    }

    return temp == NULL ? NULL: temp;
}

extern void put_TreeMap(TreeMap* tree, Room* myRoom) {
    tree->root = insertRecursively(tree->root, myRoom);
    tree->root->red = false;
}

extern void delete_TreeMap(TreeMap* tree, Room* value) {
    int done = 0;

    tree->root = removeRecursively(tree->root, value, &done);

    if (tree->root != NULL) {
        tree->root->red = false;
    }
}

static bool isRed(TreeMapNode* root) {
    return root != NULL && root->red == true;
}

static TreeMapNode* singleRotation(TreeMapNode* root, int dir) {
    TreeMapNode* save = root->link[!dir];

    root->link[!dir] = save->link[dir];
    save->link[dir] = root;

    root->red = true;
    save->red = false;

    return save;
}

static TreeMapNode* doubleRotation(TreeMapNode* root, int dir) {
    root->link[!dir] = singleRotation(root->link[!dir], !dir);

    return singleRotation(root, dir);
}

static int assert(TreeMapNode* root) {
    int lh, rh; // ?

    if (root == NULL) {
        return 1;
    } else {
        TreeMapNode* leftNode = root->link[0];
        TreeMapNode* rightNode = root->link[1];

        // Red violation check
        if (isRed(root)) {
            if (isRed(leftNode) || isRed(rightNode)) {
                printf("An error occured while asserting a TreeMap object (Red violation)");
                return 0;
            }
        }

        lh = assert(leftNode);
        rh = assert(rightNode);

        // Binary search tree violation check
        if ((leftNode != NULL && compareTo_Coord(leftNode->key, root->key) >= 0) || (rightNode != NULL && compareTo_Coord(rightNode->key, root->key
        ) <= 0)) {
            printf("An error occured while asserting a TreeMap object (Binary tree violation)");
            return 0;
        }

        // Black violation check
        if (lh != 0 && rh != 0 && lh != rh) {
            printf("An error occured while asserting a TreeMap object (Black violation)");
            return 0;
        }

        // Count black links
        if (lh != 0 && rh != 0) {
            return (isRed(root) ? lh : lh + 1); // Ternary operator
        } else {
            return 0;
        }
    }
}

static TreeMapNode* createNode(Room* value) {
    TreeMapNode* myNode = malloc(1 * sizeof(TreeMapNode));

    // If we failed to allocate, exit the program
    if (myNode == NULL) {
        printf("An error occured while initializing a TreeMapNode object");
        exit(EXIT_FAILURE);
    }

    myNode->key = value->coord;
    myNode->value = value;
    myNode->red = true;
    myNode->link[0] = NULL;
    myNode->link[1] = NULL;

    return myNode;
}

static TreeMapNode* insertRecursively(TreeMapNode* root, Room* value) {
    if (root == NULL) {
        root = createNode(value);
    } else if (compareTo_Coord(root->key, value->coord) != 0) {
        int direction = compareTo_Coord(root->key, value->coord) < 0;
        root->link[direction] = insertRecursively(root->link[direction], value);

        if (isRed(root->link[direction])) {
            if (isRed(root->link[!direction])) {
                // Case 1
                root->red = true;
                root->link[0]->red = false;
                root->link[1]->red = false;
            } else {
                // Case 2 & 3
                if (isRed(root->link[direction]->link[direction])) {
                    root = singleRotation(root, !direction);
                } else if (isRed(root->link[direction]->link[!direction])) {
                    root = doubleRotation(root, !direction);
                }
            }
        }
    }

    return root;
}

static TreeMapNode* removeRecursively(TreeMapNode* root, Room* value, int* done) {
    if (root == NULL) {
        (*done) = 1;
    } else {
        int direction;

        if (compareTo_Coord(root->key, value->coord) == 0) {
            if (root->link[0] == NULL || root->link[1] == NULL) {
                TreeMapNode* temp = root->link[root->link[0] == NULL];

                // Case 0
                if (isRed(root)) {
                    (*done) = 1;
                } else if (isRed(temp)) {
                    temp->red = false;
                    (*done) = 1;
                }

                clean_Room(&(root->value));
                free(root);

                return temp;
            } else {
                TreeMapNode* heir = root->link[0];

                while (heir->link[1] != NULL) {
                    heir = heir->link[1];
                }

                root->key = heir->key;
                root->value = heir->value;
                value = heir->value;
            }
        }

        direction = compareTo_Coord(root->key, value->coord) < 0;
        root->link[direction] = removeRecursively(root->link[direction], value, done);

        if (!(*done)) {
            root = removeBalance(root, direction, done);
        }
    }

    return root;
}

static TreeMapNode* removeBalance(TreeMapNode* root, int dir, int* done) {
    TreeMapNode* parent = root;
    TreeMapNode* sibling = root->link[!dir];

    // Case reduction, remove red sibling
    if (isRed(sibling)) {
        root = singleRotation(root, dir);
        sibling = parent->link[!dir];
    }

    if (sibling != NULL) {
        // Black sibling cases
        if (!isRed(sibling->link[0]) && !isRed(sibling->link[1])) {
            if (isRed(parent)) {
                (*done) = 1;
            }

            parent->red = 0;
            sibling->red = 1;
        } else {
            bool temp = root->red;
            bool newRoot = (root == parent);

            if (isRed(sibling->link[!dir])) {
                parent = singleRotation(parent, dir);
            } else {
                parent = doubleRotation(parent, dir);
            }

            parent->red = temp;
            parent->link[0]->red = 0;
            parent->link[1]->red = 0;

            if (newRoot) {
                root = parent;
            } else {
                root->link[dir] = parent;
            }

            (*done) = 1;
        }
    }

    return root;
}


extern int size_TreeMap(TreeMapNode* root) {
    TreeMapNode* temp = root;

    if (temp != NULL) {
        return 1 + size_TreeMap(temp->link[0]) + size_TreeMap(temp->link[1]);
    } else {
        return 0;
    }
}