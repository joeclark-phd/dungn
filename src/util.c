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

bool can_see(int ay, int ax, int by, int bx, double range) {
    Tile** map = game->level->map;
    PosArray ln = line(ay, ax, by, bx);
    for(int i=0; i<ln.count; ++i) {
        double dist = hypot( (double)ln.positions[i].y 
            - ay, (double)ln.positions[i].x - ax );
        if(dist > range) {
            return false;
        }
        if(ln.positions[i].y == by && ln.positions[i].x == bx) {
            return true;
        }
        if(map[ln.positions[i].y][ln.positions[i].x].transparent != true) {
            return false;
        }
    }
    return false;
}

void do_fov(void) {
    Tile** map = game->level->map;
    Creature* p = &game->player;
    // make all tiles invisible
    for(int y=0; y<DN_HEIGHT; ++y) {
        for(int x=0; x<DN_WIDTH; ++x) {
            map[y][x].visible = false;
        }
    }
    // make tiles visible if player can see them
    for(int y = p->y - PLAYER_VIS_RANGE; y <= p->y + PLAYER_VIS_RANGE; ++y) {
        for(int x=p->x - PLAYER_VIS_RANGE; x<= p->x + PLAYER_VIS_RANGE; ++x) {
            if( y >= 0 && x >= 0 && y < DN_HEIGHT && x < DN_WIDTH
                && can_see(p->y,p->x, y, x, PLAYER_VIS_RANGE)) {
                map[y][x].visible = true;
                map[y][x].remembered = true;
            }
        }
    }

}