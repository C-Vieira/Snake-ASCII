#pragma once
#include "View.h"

class Game;

class Scene {
public:
  virtual ~Scene() = 0;

  virtual void init() = 0;
  virtual void handleInput(Game &gameRef) = 0;
  virtual void update(Game &gameRef) = 0;
  virtual void draw() = 0;
};

class TitleScene : public Scene {
public:
  TitleScene();
  ~TitleScene();

  virtual void init() override;
  virtual void handleInput(Game &gameRef) override;
  virtual void update(Game &gameRef) override;
  virtual void draw() override;

private:
  View m_TitleScreen;
};

class GameScene : public Scene {
public:
  int boardHeight;
  int boardWidth;

  GameScene();
  GameScene(int boardHeight, int boardWidth);
  ~GameScene();

  virtual void init() override;
  virtual void handleInput(Game &gameRef) override;
  virtual void update(Game &gameRef) override;
  virtual void draw() override;

  void pause();
  void gameOver();

private:
  View m_GameBoard;
  View m_ScoreBoard;
  View m_PauseScreen;
  View m_GameOverScreen;
};
