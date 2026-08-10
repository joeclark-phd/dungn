#include "game.h"

int num_steps(int ay, int ax, int by, int bx);
int interpolate(int from, int to, double t);

int rand_between(int low, int high) {
    return low + (rand() % (1 + high - low));
}


Pos random_position_in_room(Room* r) {
    int y = rand_between(r->y, r->y+r->height-1);
    int x = rand_between(r->x, r->x+r->width-1);
    return (Pos) {y,x};
}

PosArray line(int ay, int ax, int by, int bx) {
    int n = num_steps(ay,ax,by,bx);
    Pos* points = calloc(n+1, sizeof(Pos));
    for(int step=0; step<=n; ++step) {
        double t = (n==0) ? 0.0 : (double)step/n;
        points[step].y = interpolate(ay, by, t);
        points[step].x = interpolate(ax, bx, t);
    }
    return (PosArray) {points, n+1};
}

int num_steps(int ay, int ax, int by, int bx) {
    int ydist = abs(ay-by);
    int xdist = abs(ax-bx);
    return (ydist > xdist) ? ydist : xdist;
}

int interpolate(int from, int to, double t) {
    double diff = t*(to-from); // relative
    int int_diff = (int) round(diff); // int version
    return from + int_diff;
}