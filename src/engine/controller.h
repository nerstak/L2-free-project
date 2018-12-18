#ifndef FREE_PROJECT_ENGINE_CONTROLLER_H
#define FREE_PROJECT_ENGINE_CONTROLLER_H

typedef struct referenceKey {
    int UP;
    int DOWN;
    int LEFT;
    int RIGHT;
    int INVENTORY;
    int DELETE;
    int UP_ATTACK;
    int DOWN_ATTACK;
    int LEFT_ATTACK;
    int RIGHT_ATTACK;
    int SELECT;
    int SWITCH;
}referenceKey;


/**
 * Initialise a referenceKey object
 * @return a pointer of referenceKey Object
 */
extern referenceKey* initKeys();

/**
 * Clean a referenceKey object
 * @param referenceKey a double pointer to a referenceKey Object
 */
extern void cleanKeys(referenceKey** p);

#endif
