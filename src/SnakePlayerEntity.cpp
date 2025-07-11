#include "SnakePlayerEntity.h"
#include "Game.h"
#include <curses.h>

SnakeSegmentEntity::SnakeSegmentEntity() {}

SnakeSegmentEntity::SnakeSegmentEntity(Vec2 pos) {
  this->pos.y = pos.y;
  this->pos.x = pos.x;
  this->ch = '@';
  this->color = COLOR_PAIR(GREEN_BLACK);
}

SnakeSegmentEntity::~SnakeSegmentEntity() {}

SnakePlayerEntity::SnakePlayerEntity() {}

SnakePlayerEntity::~SnakePlayerEntity() {}

// Add to the back of the queue (front of snake)
void SnakePlayerEntity::addSegment(SnakeSegmentEntity newSegment) {
  segments.push(newSegment);
}

// Remove from front of the queue (tail of the snake)
void SnakePlayerEntity::removeSegment() { segments.pop(); }

// The tail of the snake is the front of the queue
SnakeSegmentEntity SnakePlayerEntity::getTail() { return segments.front(); }

// The head of the snake is the back of the queue
SnakeSegmentEntity SnakePlayerEntity::getHead() { return segments.back(); }

void SnakePlayerEntity::moveTo(int newY, int newX) {
  // Add new segment at newPos
  Vec2 newPos{newY, newX};
  addSegment(SnakeSegmentEntity(newPos));

  // Pop tail
  removeSegment();
}
