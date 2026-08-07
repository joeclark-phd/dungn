#ifndef UTIL_H
#define UTIL_H

typedef struct Pos Pos;
struct Pos {
    int y;
    int x;
};

int rand_between(int low, int high);

#endif