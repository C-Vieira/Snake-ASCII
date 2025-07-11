#include "View.h"
#include <curses.h>

View::View() { m_ViewWindow = NULL; }

View::~View() {}

View::View(int height, int width, int yOffset, int xOffset)
    : m_Height(height), m_Width(width) {
  m_Starty = ((LINES - height) + yOffset) / 2;
  m_Startx = ((COLS - width) + xOffset) / 2;

  m_ViewWindow = newwin(m_Height, m_Width, m_Starty, m_Startx);
}

void View::setTimeout(int timeout) { wtimeout(m_ViewWindow, timeout); }

int View::getHeight() { return m_Height; }

int View::getWidth() { return m_Width; }

void View::addColorBegin(int color) { wattron(m_ViewWindow ,COLOR_PAIR(color)); }

void View::addColorEnd(int color) { wattroff(m_ViewWindow ,COLOR_PAIR(color)); }

void View::addBorder() { box(m_ViewWindow, 0, 0); }

void View::clear() {
  wclear(m_ViewWindow);
  wrefresh(m_ViewWindow);
}

void View::refresh() { wrefresh(m_ViewWindow); }

void View::addEntity(Entity entity) {
  addCharAt(entity.pos.y, entity.pos.x, entity.ch, entity.color);
}

void View::addNumAt(int y, int x, int num) {
  mvwprintw(m_ViewWindow, y, x, "%d", num);
}

void View::addCharAt(int y, int x, chtype ch, int color) {
  mvwaddch(m_ViewWindow, y, x, ch | color);
}

void View::clearCharAt(int y, int x) { mvwaddch(m_ViewWindow, y, x, ' '); }

chtype View::getCharAt(int y, int x) { return mvwinch(m_ViewWindow, y, x); }

void View::addMessageAt(int y, int x, char *msg) {
  mvwprintw(m_ViewWindow, y, x, "%s", msg);
}

void View::getEmptyCoords(int &y, int &x) {
  while (mvwinch(m_ViewWindow, y = rand() % m_Height, x = rand() % m_Width) !=
         ' ')
    ;
}

chtype View::getInput() { return wgetch(m_ViewWindow); }

void View::show() {
  addBorder();
  refresh();
}

void View::deleteWindow() {
  if (m_ViewWindow != NULL)
    delwin(m_ViewWindow);
}
