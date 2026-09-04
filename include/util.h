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
Room* random_room_in_level(Level*);
Pos random_position_in_room(Room*);
PosArray line(int ay, int ax, int by, int bx);
bool can_see(int ay, int ax, int by, int bx, double range);
void do_fov(void);

#endif