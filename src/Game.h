#pragma once
#include "View.h"
#include "Scene.h"

// Color pairs
#define WHITE_BLACK 1
#define BLUE_BLACK 2
#define RED_BLACK 3
#define YELLOW_BLACK 4
#define GREEN_BLACK 5
#define BLACK_BLACK 6
#define CYAN_BLACK 7
#define MAGENTA_BLACK 8

class Game {
public:
  bool shouldClose = false;
  Scene *currScene;

  Game();
  ~Game();

  void init();
  void changeScene(Scene *newScene);
  void run();
};
