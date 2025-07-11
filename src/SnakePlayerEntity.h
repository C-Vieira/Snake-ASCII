#pragma once
#include "Entity.h"
#include <queue>

class SnakeSegmentEntity : public Entity {
public:
  SnakeSegmentEntity();
  SnakeSegmentEntity(Vec2 pos);
  ~SnakeSegmentEntity();
};

class SnakePlayerEntity {
public:
  std::queue<SnakeSegmentEntity> segments;
  Vec2 dir;

  SnakePlayerEntity();
  ~SnakePlayerEntity();

  void addSegment(SnakeSegmentEntity newSegment);
  void removeSegment();
  SnakeSegmentEntity getTail();
  SnakeSegmentEntity getHead();

  void moveTo(int newY, int newX);
};
