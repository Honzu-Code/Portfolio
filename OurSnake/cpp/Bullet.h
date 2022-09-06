#ifndef BULLET
#define BULLET

#define BULLET_ENCODED_LENGTH sizeof(float) * 4 + sizeof(int) * 2
#define BULLET_DISTORTION 0.1
#define BULLET_BASE_SPEED 5
#define BULLET_EXTRA_SPEED 8
#define BULLET_OWNER_SPEED_FACTOR 2
#define BULLET_OWNER_SPEED_DISTORTION_NULLIFICATION 12 // speed at which you got sniper aim

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Point.h"
#include "Vector.h"

using std::string;

static int bulletsCount = 0;

class Bullet: public Point, public Vector
{
public:
  int id;
  int owner;
  float lastX = 0;
  float lastY = 0;

  Bullet() : Bullet(Point(0, 0), 0.0, -1, 6) {};
  Bullet(Point position, float direction, int owner, float ownerSpeed)
  : Point(position.x, position.y),
    id(bulletsCount++), owner(owner){
      float distortion = ((rand() / (float) RAND_MAX) - 0.5) * BULLET_DISTORTION;
      distortion *= 1 - fmin(1, ownerSpeed / BULLET_OWNER_SPEED_DISTORTION_NULLIFICATION); 
      this->direction = direction + distortion;
      this->length = BULLET_BASE_SPEED;
      this->length += BULLET_EXTRA_SPEED * (rand() / (float) RAND_MAX);
      this->length += BULLET_OWNER_SPEED_FACTOR * ownerSpeed;

    };
  void move();
  void tick(){
    this->move();
  };

  std::string encode();
  std::string encodeId();
  static Bullet decode(std::string input);
};

void Bullet::move()
{
  this->lastX = this->x;
  this->lastY = this->y;
  this->x += cos(this->direction) * this->length;
  this->y += sin(this->direction) * this->length;
}

// If you can, make encode and decode shorter with loop.

std::string Bullet::encode(){
  char *data = new char[BULLET_ENCODED_LENGTH];
  int size = 0;

  // ID
  memcpy(data + size, &(this->id), sizeof(this->id));
  size += sizeof(this->id);

  // Owner ID
  memcpy(data + size, &(this->owner), sizeof(this->owner));
  size += sizeof(this->owner);

  // X
  memcpy(data + size, &(this->x), sizeof(this->x));
  size += sizeof(this->x);

  // Y
  memcpy(data + size, &(this->y), sizeof(this->y));
  size += sizeof(this->y);

  // Direction
  memcpy(data + size, &(this->direction), sizeof(this->x));
  size += sizeof(this->direction);

  // Length
  memcpy(data + size, &(this->length), sizeof(this->x));
  size += sizeof(this->length);

  return std::string(data, size);
}

string Bullet::encodeId(){
  char *data = new char[sizeof(this->id)];
  int size = 0;
  int s = 0;
  // ID
  s = sizeof(this->id);
  memcpy(data + size, &(this->id), s);
  size += s;

  return string(data, size);
}

Bullet Bullet::decode(std::string input){
  const char *data = input.c_str();
  Bullet object;
  int size = 0;

  // ID
  memcpy(&(object.id), data + size, sizeof(object.id));
  size += sizeof(object.id);

  // Owner ID
  memcpy(&(object.owner), data + size, sizeof(object.owner));
  size += sizeof(object.owner);

  // X
  memcpy(&(object.x), data + size, sizeof(object.x));
  size += sizeof(object.x);

  // Y
  memcpy(&(object.y), data + size, sizeof(object.y));
  size += sizeof(object.y);

  // Direction
  memcpy(&(object.direction), data + size, sizeof(object.direction));
  size += sizeof(object.direction);

  // Length
  memcpy(&(object.length), data + size, sizeof(object.length));
  size += sizeof(object.length);

  return object;
}

#endif
