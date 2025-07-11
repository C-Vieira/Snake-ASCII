#include "FruitEntity.h"
#include "Game.h"
#include "Scene.h"
#include "SnakePlayerEntity.h"

// Global Score value
int g_Score = 0;

// Global player reference
SnakePlayerEntity g_Player;

// Global fruit reference
FruitEntity g_Fruit;

// Helper functions:
bool isCollidingWithBorder(View view, Vec2 newPos) {
  if (newPos.y <= 0 || newPos.y >= view.getHeight() - 1 || newPos.x <= 0 ||
      newPos.x == view.getWidth() - 1)
    return true;
  return false;
}

void GameScene::pause() {
  // Paused State
  m_PauseScreen.show();
  m_PauseScreen.addMessageAt(2, 6, (char *)"PAUSED");
  m_PauseScreen.refresh();
  while (m_PauseScreen.getInput() != 'p')
    ;
  m_PauseScreen.clear();
}

void GameScene::gameOver() {
  // Game Over State
  m_GameOverScreen.show();
  m_GameOverScreen.addMessageAt(2, 1, (char *)"   GAME OVER!   ");
  m_GameOverScreen.addMessageAt(3, 1, (char *)">'r' to restart<");
  m_GameOverScreen.refresh();
  while (m_GameOverScreen.getInput() != 'r')
    ;
  m_GameOverScreen.clear();
}

GameScene::GameScene() {}

GameScene::GameScene(int boardHeight, int boardWidth)
    : boardHeight(boardHeight), boardWidth(boardWidth) {
  m_PauseScreen = View(5, 18, 0, 0);
  m_GameOverScreen = View(5, 18, 0, 0);
}

GameScene::~GameScene() {
  m_GameBoard.deleteWindow();
  m_ScoreBoard.deleteWindow();
  m_PauseScreen.deleteWindow();
  m_GameOverScreen.deleteWindow();
  endwin();
}

void GameScene::init() {
  // Views Init
  m_GameBoard.deleteWindow();
  m_GameBoard = View(boardHeight, boardWidth, 0, 0);
  m_GameBoard.setTimeout(300);
  m_GameBoard.show();

  g_Score = 0;
  m_ScoreBoard.deleteWindow();
  m_ScoreBoard = View(3, boardWidth, boardHeight + 2, 0);
  m_ScoreBoard.addMessageAt(1, 1, (char *)"Score: 0");
  m_ScoreBoard.show();

  // Player Init
  Vec2 playerDir = {1, 0}; // Down
  g_Player.dir = playerDir;

  // Clear segments
  while (!g_Player.segments.empty())
    g_Player.segments.pop();

  g_Player.addSegment(SnakeSegmentEntity(Vec2{2, 2}));
  m_GameBoard.addEntity(g_Player.getHead());

  // Add four initial segments to the snake
  for (int i = 0; i < 4; i++) {
    Vec2 nextPos{g_Player.getHead().pos.y + g_Player.dir.y,
                 g_Player.getHead().pos.x + g_Player.dir.x};
    SnakeSegmentEntity nextSegment(nextPos);

    g_Player.segments.push(nextSegment);

    m_GameBoard.addEntity(nextSegment);
  }

  // Fruit Init
  g_Fruit.ch = 'o';
  g_Fruit.color = COLOR_PAIR(RED_BLACK);
  m_GameBoard.getEmptyCoords(g_Fruit.pos.y, g_Fruit.pos.x);
  m_GameBoard.addEntity(g_Fruit);

  m_GameBoard.refresh();
}

void GameScene::handleInput(Game &gameRef) {
  chtype input = m_GameBoard.getInput();
  if (input == 'q')
    gameRef.changeScene(new TitleScene());

  Vec2 newDir;
  switch (input) {
  case 'w': {
    Vec2 up{-1, 0};
    newDir = up;
    break;
  }
  case 'a': {
    Vec2 left{0, -1};
    newDir = left;
    break;
  }
  case 's': {
    Vec2 down{1, 0};
    newDir = down;
    break;
  }
  case 'd': {
    Vec2 right{0, 1};
    newDir = right;
    break;
  }
  case 'p': {
    newDir = g_Player.dir;

    pause();
    break;
  }
  default:
    newDir = g_Player.dir;
  }

  // Ignore invalid moves
  if ((g_Player.dir.y + newDir.y != 0) && (g_Player.dir.x + newDir.x != 0))
    g_Player.dir = newDir;
}

void GameScene::update(Game &gameRef) {
  // Update state
  Vec2 newPos{g_Player.getHead().pos.y + g_Player.dir.y,
              g_Player.getHead().pos.x + g_Player.dir.x};

  // Handle collisions
  if (isCollidingWithBorder(m_GameBoard, newPos) ||
      m_GameBoard.getCharAt(newPos.y, newPos.x) ==
          (g_Player.getHead().ch | g_Player.getHead().color)) {

    gameOver();
    // Reset Game
    init();
    return;
  }

  // Collect fruit
  if ((newPos.y == g_Fruit.pos.y) && (newPos.x == g_Fruit.pos.x)) {
    g_Score += 10;
    g_Player.addSegment(SnakeSegmentEntity(Vec2{newPos.y, newPos.x}));
    m_GameBoard.getEmptyCoords(g_Fruit.pos.y, g_Fruit.pos.x);
  } else {
    // Move
    // Clear tail
    m_GameBoard.clearCharAt(g_Player.getTail().pos.y, g_Player.getTail().pos.x);

    g_Player.moveTo(newPos.y, newPos.x);
  }
}

void GameScene::draw() {
  // Draw frame
  m_GameBoard.addEntity(g_Player.getHead());
  m_GameBoard.addEntity(g_Fruit);

  m_GameBoard.refresh();

  m_ScoreBoard.addNumAt(1, 8, g_Score);
  m_ScoreBoard.refresh();
}
