#ifndef VECTOR
#define VECTOR

#define VECTOR_ENCODED_LENGTH sizeof(float) * 2

#include <cmath>
#include <math.h>
#include "Point.h"


class Vector
{
public:
  float direction;
  float length;
  Vector() : direction(0.0), length(0.0) {}
  Vector(float dir,float len) : direction(dir),
  length(len) {}
  void add(Vector v);
  void apply_on(Point &p);

  char* encode();
  static Vector decode(char* data);
};

void Vector::add(Vector v)
{
  float x = cos(this->direction) * this->length + cos(v.direction) * v.length;
  float y = sin(this->direction) * this->length + sin(v.direction) * v.length;
  this->direction = atan2(y,x);
  this->length = hypot(x,y);
}

void Vector::apply_on(Point &p)
{
  p.x += cos(this->direction) * this->length;
  p.y += sin(this->direction) * this->length;
}

char* Vector::encode()
{
  char *data = new char[VECTOR_ENCODED_LENGTH];
  int size = 0;

  // Direction
  memcpy(data + size, &(this->direction), sizeof(this->direction));
  size += sizeof(this->direction);

  // Length
  memcpy(data + size, &(this->length), sizeof(this->length));
  size += sizeof(this->length);

  return data;
}

Vector Vector::decode(char* data)
{
  Vector object;
  int size = 0;

  // Direction
  memcpy(&(object.direction), data + size, sizeof(object.direction));
  size += sizeof(object.direction);

  // Length
  memcpy(&(object.length), data + size, sizeof(object.length));
  size += sizeof(object.length);

  return object;
}

#endif //Vector
