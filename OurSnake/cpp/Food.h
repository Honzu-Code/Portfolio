#ifndef FOOD
#define FOOD

#define FOOD_DODGE_MULTIPLIER 0.1
#define FOOD_ENCODED_LENGTH sizeof(float) * 5 + sizeof(int)
#define FOOD_DODGE_DISTANCE 300

#include "Point.h"
#include "Vector.h"

using std::string;

static int foodCount = 0;

class Food: public Point, public Vector
{
public:
  int id;
  float size;
  float lastX;
  float lastY;

  Food() : Food(Point(0, 0), Vector(0, 0), 0) {};
  Food(Point position, Vector movement, float size)
  : Point(position.x, position.y),
    Vector(movement.direction, movement.length),
    id(foodCount++), size(size){
      this->lastX = this->x;
      this->lastY = this->y;
    };
  void move();
  void tick(){
    this->move();
  } // If food doesn't move, fix this line.
  void dodge_to(float direction);

  std::string encode();
  std::string encodeId();
  static Food decode(std::string input);
};

/* We'll need this math later.
  this->boost = size / 2;
  this->satisfaction = size * 3;
  this->dodgeSpeed = movement.length * 0.1 / size;
  this->speedBoost = size * 0.5;
*/

void Food::move()
{
  this->lastX = this->x;
  this->lastY = this->y;
  this->x += cos(this->direction) * this->length;
  this->y += sin(this->direction) * this->length;
}

void Food::dodge_to(float direction)
{
/*
 * I'm removing this to test if game can work without it.
 * I turned off constant data broadcast, and disabled this.
 * I would've used it if i was able to recreate the same effect in
 * front-end, but since i can't synchronise the front-end and backend,
 * i can't fake the dodge_to. Maybe we can later apply it once per N ticks
 */
  //this->add(Vector(direction, FOOD_DODGE_MULTIPLIER * this->length / this->size));
}

// If you can, make encode and decode shorter with loop.

std::string Food::encode(){
  char *data = new char[FOOD_ENCODED_LENGTH];
  int size = 0;

  // ID
  memcpy(data + size, &(this->id), sizeof(this->id));
  size += sizeof(this->id);

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

  // Size
  memcpy(data + size, &(this->size), sizeof(this->x));
  size += sizeof(this->size);

  return std::string(data, size);
}

string Food::encodeId(){
  char *data = new char[sizeof(this->id)];
  int size = 0;
  int s = 0;
  // ID
  s = sizeof(this->id);
  memcpy(data + size, &(this->id), s);
  size += s;

  return string(data, size);
}

Food Food::decode(std::string input){
  const char *data = input.c_str();
  Food object;
  int size = 0;

  // Id
  memcpy(&(object.id), data + size, sizeof(object.id));
  size += sizeof(object.id);

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

  // Size
  memcpy(&(object.size), data + size, sizeof(object.size));
  size += sizeof(object.size);

  return object;
}

#endif
