#ifndef FREE_PROJECT_UTILS_DIRECTION_H
#define FREE_PROJECT_UTILS_DIRECTION_H

/**
 * N:0 0 -1
 * E:1 1 0
 * S:2 0 1
 * W:3 -1 0
 */

 /**
  * 4 Direction possible
  */

typedef struct Direction {
    int code;
    int x;
    int y;
} Direction;

extern Direction* init_Direction(int code, int x, int y);
extern void clean_Direction(Direction** myDirection);

extern Direction* fromCode_Direction(int code);
extern Direction* opposite_Direction(Direction* myDirection);

#endif //FREE_PROJECT_UTILS_DIRECTION_H
