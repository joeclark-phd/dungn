#ifndef UTIL_H
#define UTIL_H

typedef struct Pos Pos;
struct Pos {
    int y;
    int x;
};
typedef struct PosArray PosArray;
struct PosArray {
    Pos* positions;
    int count;
};

int rand_between(int low, int high);
Pos random_position_in_room(Room*);
PosArray line(int ay, int ax, int by, int bx);

#endif