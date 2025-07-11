#include "Game.h"
#include "Scene.h"

Scene::~Scene() {}

TitleScene::TitleScene() {}

TitleScene::~TitleScene() { m_TitleScreen.deleteWindow(); }

void TitleScene::init() {
  // Title View Init
  m_TitleScreen.deleteWindow();
  m_TitleScreen = View(LINES, COLS, 0, 0);

  int middleY = LINES / 2;
  int middleX = (COLS - 46) / 2;

  m_TitleScreen.addColorBegin(GREEN_BLACK);
  m_TitleScreen.addMessageAt(middleY - 3, middleX, (char *)".d88888b                    dP                ");
  m_TitleScreen.addMessageAt(middleY - 2, middleX, (char *)"89.    \"'                   88               ");
  m_TitleScreen.addMessageAt(middleY - 1, middleX, (char *)"`Y88888b. 88d888b. .d8888b. 88  .dP  .d8888b. ");
  m_TitleScreen.addMessageAt(middleY    , middleX, (char *)"      `8b 88'  `88 88'  `88 88888\"   88ooood8");
  m_TitleScreen.addMessageAt(middleY + 1, middleX, (char *)"d8'   .8P 88    88 88.  .88 88  `8b. 88.  ... ");
  m_TitleScreen.addMessageAt(middleY + 2, middleX, (char *)" Y88888P  dP    dP `88888P8 dP   `YP `88888P' ");
  m_TitleScreen.addColorBegin(WHITE_BLACK);

  m_TitleScreen.addMessageAt(middleY + 4, (COLS - 26) / 2, (char *)"> press any key to start <");

  m_TitleScreen.refresh();
}

void TitleScene::handleInput(Game &gameRef) {
  chtype input = m_TitleScreen.getInput();
  if (input == 'q') {
    gameRef.shouldClose = true;
  } else {
    int boardHeight = 28;
    int boardWidth = 50;

    // Do scene transition
    m_TitleScreen.clear();
    gameRef.changeScene(new GameScene(boardHeight, boardWidth));
  }
}

// These go unused...
void TitleScene::update(Game &gameRef) {}

void TitleScene::draw() {}
