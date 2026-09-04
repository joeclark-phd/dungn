#ifndef DRAW_H
#define DRAW_H

#define DRAW_MAP_Y 1

// colors
#define GRAY_BLUE 8
#define PALE_YELLOW 9

#define HONEY_GOLD 101
#define BLOOD_RED 102
#define ROYAL_PURPLE 103
#define OGRE_GREEN 104
#define OWLBEAR_BROWN 105
#define TIGER_ORANGE 106
#define FROST_BLUE 107
#define POTION_CYAN 108
#define STEEL_GRAY 109
#define BONE_WHITE 110

// color pairs
#define VISIBLE_TILE 1
#define REMEMBERED_TILE 2

#define CP_GOLD 3
#define CP_RED 4
#define CP_PURPLE 5
#define CP_GREEN 6
#define CP_BROWN 7
#define CP_ORANGE 8
#define CP_BLUE 9
#define CP_CYAN 10
#define CP_GRAY 11
#define CP_WHITE 12

void draw_everything(void);
void setup_colors(void);

#endif