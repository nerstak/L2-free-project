#ifndef FREE_PROJECT_STRUCTURES_OPTIONS_H
#define FREE_PROJECT_STRUCTURES_OPTIONS_H

enum actionOptions {O_NONE = 0, O_UP = -10, O_DOWN = 10, O_LEFT = -1, O_RIGHT = 1, O_ENTER = 5, O_LEAVE = 15};

typedef struct options_t {
    int askAction;
    int isKeyChanging;
    int newKey;
    int nTypeSelected;
    int nSelected;
}options_t;

#endif //FREE_PROJECT_STRUCTURES_OPTIONS_H