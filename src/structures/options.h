#ifndef FREE_PROJECT_STRUCTURES_OPTIONS_H
#define FREE_PROJECT_STRUCTURES_OPTIONS_H

enum actionOptions {O_NONE = 0, O_LEAVE = 15};

typedef struct options_t {
    int askAction;
    int nTypeSelected;
    int nSelected;
}options_t;

#endif //FREE_PROJECT_STRUCTURES_OPTIONS_H