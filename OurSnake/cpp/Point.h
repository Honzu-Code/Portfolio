#ifndef POINT
#define POINT

#define POINT_ENCODED_LENGTH sizeof(float) * 2

#include <math.h>
#include <string.h>


class Point
{
public:
  float x;
  float y;
  Point() : x(0.0), y(0.0) {}
  Point(float a, float b) : x(a), y(b) {}
  float distance(Point p);

  std::string encode();
  static Point decode(std::string input);
};

float Point::distance(Point p)
{
  float a = this->x - p.x;
  float b = this->y - p.y;
  return hypot(a, b);
}

std::string Point::encode()
{
  char *data = new char[POINT_ENCODED_LENGTH];
  int size = 0;

  // X
  memcpy(data + size, &(this->x), sizeof(this->x));
  size += sizeof(this->x);

  // Y
  memcpy(data + size, &(this->y), sizeof(this->y));
  size += sizeof(this->y);

  return std::string(data, size);
}

Point Point::decode(std::string input){
  const char *data = input.c_str();
  Point object;
  int size = 0;

  // X
  memcpy(&(object.x), data + size, sizeof(object.x));
  size += sizeof(object.x);

  // Y
  memcpy(&(object.y), data + size, sizeof(object.y));
  size += sizeof(object.y);

  return object;
}

#endif //POINT
