#pragma once
#include <curses.h>

struct Vec2 {
  int y, x;
};

class Entity {
public:
  Vec2 pos;
  chtype ch;
  int color;
};
