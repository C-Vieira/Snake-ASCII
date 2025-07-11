#include "Game.h"
#include "Scene.h"
#include <ctime>
#include <curses.h>

Game::Game() {}

Game::~Game() { endwin(); }

void Game::init() {
  // Rand Init
  srand(time(NULL));

  // Curses Init
  initscr();
  noecho();
  curs_set(0);

  if (has_colors()) {
    start_color();

    init_pair(WHITE_BLACK, COLOR_WHITE, COLOR_BLACK);     // blue
    init_pair(BLUE_BLACK, COLOR_BLUE, COLOR_BLACK);       // white
    init_pair(RED_BLACK, COLOR_RED, COLOR_BLACK);         // red
    init_pair(YELLOW_BLACK, COLOR_YELLOW, COLOR_BLACK);   // yellow
    init_pair(GREEN_BLACK, COLOR_GREEN, COLOR_BLACK);     // green
    init_pair(BLACK_BLACK, COLOR_BLACK, COLOR_BLACK);     // black
    init_pair(CYAN_BLACK, COLOR_CYAN, COLOR_BLACK);       // cyan
    init_pair(MAGENTA_BLACK, COLOR_MAGENTA, COLOR_BLACK); // magenta

  } else {
    mvprintw(20, 50, "Your system doesn't support color. Can't start game!");
    getch();
  }

  currScene = new TitleScene();
  currScene->init();
}

void Game::changeScene(Scene *newScene){
  delete currScene;
  currScene = newScene;
  currScene->init();
}

void Game::run() {
  // Game Loop
  while (!shouldClose) {
    // Input
    currScene->handleInput(*this);

    // Update
    currScene->update(*this);

    // Draw
    currScene->draw();
  }
}
