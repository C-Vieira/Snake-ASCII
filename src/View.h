#pragma once
#include "Entity.h"
#include <curses.h>
#include <stdlib.h>

class View {
public:
  View();
  ~View();
  View(int height, int width, int yOffset, int xOffset);

  void setTimeout(int timeout);
  int getHeight();
  int getWidth();

  void addColorBegin(int color);
  void addColorEnd(int color);
  void addBorder();
  void clear();
  void refresh();
  void addEntity(Entity entity);
  void addNumAt(int y, int x, int num);
  void addCharAt(int y, int x, chtype ch, int color);
  void clearCharAt(int y, int x);
  chtype getCharAt(int y, int x);
  void addMessageAt(int y, int x, char* msg);
  void getEmptyCoords(int &y, int &x);
  chtype getInput();
  void show();
  void deleteWindow();

private:
  int m_Height, m_Width;
  int m_Starty, m_Startx;
  WINDOW *m_ViewWindow;
};
