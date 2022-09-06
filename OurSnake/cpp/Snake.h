#ifndef SNAKE
#define SNAKE

#define SNAKE_DEFAULT_NAME "Anon"
#define SNAKE_DEFAULT_SKIN "/static/images/sprites/snake01.png"
#define SNAKE_START_LENGTH 80
#define SNAKE_START_AMMO 3.0
#define SNAKE_BASE_SPEED 6.0
#define SNAKE_MAX_SPEED 20.0
#define SNAKE_SHOOT_LENGTH_COST 8.0
#define SNAKE_MIN_LENGTH_TO_SHOOT 50.0
#define SNAKE_HEAD_CENTER_TO_MOUNT_DISTANCE 12.0
#define FOOD_SATISFACTION_MULTIPLIER 3.0
#define FOOD_BOOST_MULTIPLIER 0.5
#define FOOD_AMMO_MULTIPLIER 0.3
#define FOOD_SCORE_MULTIPLIER 1.0
#define SNAKE_DECELERATION 0.1
#define SNAKE_USE_AREA_COLLISION_PRECHECK false
#define SNAKE_USE_DISTANCE_COLLISION_PRECHECK true


#include <vector>
#include <string>
#include <cmath>
#include <math.h>
#include <cfloat>

#include "Point.h"
#include "Vector.h"
#include "Bullet.h"
#include "Food.h"
#include "Rect.h"

#include <iostream>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
using websocketpp::connection_hdl;
using namespace std;

using std::string;
using std::vector;
using std::min;
using std::max;
using std::cout;
using std::endl;

static int snakeCount = 0;

bool do_lines_cross(Point line1_a, Point line1_b, Point line2_a, Point line2_b);


class Snake
{
public:
  int id;
  connection_hdl hdl; // mainatined by server class
  void* userData = nullptr;
  bool alive = true; // can be used for multithreading jobs.
  // like, if snake dies, we don't care for it more in this tick,
  // then we respawn at the end of the tick. Not implemented yet
  string name = SNAKE_DEFAULT_NAME;
  string skin = SNAKE_DEFAULT_SKIN;

  vector<Point> controlPoints;
  float direction = 0;
  int length = SNAKE_START_LENGTH;

  float score = 0;
  float ammo = SNAKE_START_AMMO;

  float speed = SNAKE_BASE_SPEED;
  int kills = 0;

  Snake(): id(snakeCount++) {
    this->name = string(SNAKE_DEFAULT_NAME + to_string(this->id));
  };
  Snake(string name, string skin)
    : id(snakeCount++), name(name), skin(skin) {};

  void reset(){
    cout << "Snake " << this->id << " died." << endl;
    cout << "Point[0].x = " << this->controlPoints[0].x << ",Point[0].y " << this->controlPoints[0].y << endl;
    this->controlPoints.clear();
    cout << "Snake after controlPoints" << endl;
    this->length = SNAKE_START_LENGTH;
    this->score = 0;
    this->ammo = SNAKE_START_AMMO;
    this->speed = SNAKE_BASE_SPEED;
  }

  bool can_shoot();
  Bullet spawn_bullet();
  void consume_food(Food& food);
  void tick();

  void calculate_speed();
  void move();
  void cut_to_size();
  float get_extra_size();
  void merge_lines();
  bool needs_merge(int i);
  bool is_colliding(Snake &snake);

  #if SNAKE_USE_AREA_COLLISION_PRECHECK
    Rect area();
    void calculateArea();
    void addDotToArea(Point p);
    void removeDotFromArea(Point p);
  #endif

  int getEncodedLength();
  string encode();
  string encodeId();
  string encodeDataFromTick();
  string encodeScore();
  static Snake decode(string input);

  //operators overloads
  bool operator == (const Snake & s);
};

bool Snake::can_shoot()
{
  return this->ammo > 0 &&
         this->length > SNAKE_MIN_LENGTH_TO_SHOOT &&
         !this->controlPoints.empty();
}

Bullet Snake::spawn_bullet()
{
  if(!this->can_shoot())
    throw "Snake can't shoot";
  if(this->controlPoints.size() == 0)
    throw "Snake has no points, so it can't shoot";

  Point head = this->controlPoints.back();
  Point position = Point(head.x, head.y);
  Vector(this->direction, SNAKE_HEAD_CENTER_TO_MOUNT_DISTANCE)
    .apply_on(position);
  Bullet bullet = Bullet(position, this->direction, this->id, this->speed);
  this->ammo -= 1;
  this->length -= SNAKE_SHOOT_LENGTH_COST;

  // We'll use broadcast function from server class.

  return bullet;
}

void Snake::consume_food(Food &food)
{
  this->ammo += 1;
  this->score += food.size * FOOD_SCORE_MULTIPLIER;
  this->length += food.size * FOOD_SATISFACTION_MULTIPLIER;
  this->speed += food.size * FOOD_BOOST_MULTIPLIER;

  // We'll use broadcast function from server class.
}

void Snake::tick()
{
  //cout << "  speed" << endl;
  this->calculate_speed();
  //cout << "  move" << endl;
  this->move();
  //cout << "  cut" << endl;
  this->cut_to_size();
  //cout << "  merge" << endl;
  this->merge_lines();
}

void Snake::calculate_speed()
{
  this->speed = (float) min(this->speed, (float) SNAKE_MAX_SPEED);
  this->speed = (float) max(this->speed, (float) SNAKE_BASE_SPEED);

  if(this->speed > SNAKE_BASE_SPEED)
     this->speed -= SNAKE_DECELERATION;
}

void Snake::move()
{
  Point head = this->controlPoints.back();
  Point next = Point(head.x, head.y);
  Vector(this->direction, this->speed).apply_on(next);
  this->controlPoints.push_back(next);

  #if SNAKE_USE_AREA_COLLISION_PRECHECK
    this->addDotToArea(next);
  #endif
}

void Snake::merge_lines()
{
  if(this->controlPoints.size() > 4)
  {
    for(long unsigned int i = 1; i < this->controlPoints.size() - 4; i++)
      while(i < this->controlPoints.size() - 4 && Snake::needs_merge(i)){
        //cout << "   merging..." << this->controlPoints.size() << endl;
        this->controlPoints.erase(this->controlPoints.begin() + i);
      }
  }
}

bool Snake::needs_merge(int i)
{
  Point a = this->controlPoints[i + 1];
  Point b = this->controlPoints[i];
  Point c = this->controlPoints[i - 1];
  Point v1 = Point(a.x - b.x, a.y - b.y);
  Point v2 = Point(b.x - c.x, b.y - c.y);
  double difference = abs(atan2(v1.y, v1.x) - atan2(v2.y, v2.x));
  return difference < FLT_EPSILON;
}

void Snake::cut_to_size()
{
  #if SNAKE_USE_AREA_COLLISION_PRECHECK
    vector<Point> pointsToRemoveFromArea;
  #endif

  float size = this->get_extra_size();
  while(size > 1 && this->controlPoints.size() > 1)
  {
    Point p0 = this->controlPoints[0];
    Point p1 = this->controlPoints[1];
    Point v = Point(p1.x - p0.x, p1.y - p0.y);
    float distance = hypot(v.x, v.y);
    float a = atan2(v.y, v.x);

    distance = fmax(distance - size, 0);

    #if SNAKE_USE_AREA_COLLISION_PRECHECK
      pointsToRemoveFromArea.push_back(p0);
    #endif

    this->controlPoints[0].x = p1.x - round(distance * cos(a));
    this->controlPoints[0].y = p1.y - round(distance * sin(a));

    while(this->controlPoints[0].x == this->controlPoints[1].x
          && this->controlPoints[0].y == this->controlPoints[1].y)
    {
      this->controlPoints.erase(this->controlPoints.begin());
    }

    size = this->get_extra_size();
  }

  #if SNAKE_USE_AREA_COLLISION_PRECHECK
    for(int i = 1; i < (int) pointsToRemoveFromArea.size() - 1; i++)
      this->removeDotFromArea(pointsToRemoveFromArea[i]);
  #endif
}

float Snake::get_extra_size()
{
  float size = 0;
  for(long unsigned int i=0; i < this->controlPoints.size()-1; i++){
    Point p1 = this->controlPoints[i];
    Point p2 = this->controlPoints[i + 1];
    size += p1.distance(p2);
  }
  return fmax(0, size - this->length);
}

bool Snake::is_colliding(Snake &snake){ // FIXME, after you fix controlPoints disappearance
  if(this->controlPoints.size() < 2)
    return false;
  Point head_1 = this->controlPoints[this->controlPoints.size() - 1];
  Point head_2 = this->controlPoints[this->controlPoints.size() - 2];

  #if SNAKE_USE_DISTANCE_COLLISION_PRECHECK
    if(head_1.distance(snake.controlPoints.back()) > snake.length)
      return false;
  #endif

  #if SNAKE_USE_AREA_COLLISION_PRECHECK
    if(!this->area->overlaps(snake.area))
      return false;
  #endif

  int max = snake.controlPoints.size() - 1;
  if(snake.id == this->id)
    max--;
  for (int i = 1; i < max; i++){
    Point p1 = snake.controlPoints[i - 1];
    Point p2 = snake.controlPoints[i];
    if(do_lines_cross(p1, p2, head_1, head_2)){
      return true;
    }
  }
  return false;
}

#if SNAKE_USE_AREA_COLLISION_PRECHECK
  void Snake::addDotToArea(Point p){
    this->area.include(p);
  }

  void Snake::removeDotFromArea(Point p){
    bool needsRecalculation = false;
    if(abs(p.x - this.area.x) < FLT_EPSILON){
      needsRecalculation = true;
    }
    if(abs(p.y - this.area.y) < FLT_EPSILON){
      needsRecalculation = true;
    }
    if(abs(p.x - (this.area.x + this.area.w)) < FLT_EPSILON){
      needsRecalculation = true;
    }
    if(abs(p.y - (this.area.y + this.area.h)) < FLT_EPSILON){
      needsRecalculation = true;
    }

    if(needsRecalculation){
      this->calculateArea();
    }
  }

  void Snake::calculateArea(){
    Point tail = this->controlPoints[0];
    this->area = Rect(tail.x, tail.y);
    for (int i = 1; i < (int) this->controlPoints.size() - 2; i++){
      this->area.include(this->controlPoints[i]);
    }
  }
#endif

// GetData method will not be needed here
// because we'll send data from server class
// when data is ready, and we will not
// buffer the data


int Snake::getEncodedLength(){
  int size = 0;
  size += sizeof(this->id);
  size += sizeof(int) + this->name.size() * 1; // 1 for sizeof(char)
  size += sizeof(int) + this->skin.size() * 1;
  size += sizeof(int) + this->controlPoints.size() * POINT_ENCODED_LENGTH;
  size += sizeof(this->direction);
  size += sizeof(this->length);
  size += sizeof(this->score);
  size += sizeof(this->ammo);
  size += sizeof(this->speed);
  return size;
}

string Snake::encode(){
  int len = this->getEncodedLength();
  char *data = new char[len];
  int size = 0;
  int s = 0;
  // ID
  s = sizeof(this->id);
  memcpy(data + size, &(this->id), s);
  size += s;

  // Length of Name
  int nameSize = this->name.size();
  s = sizeof(nameSize);
  memcpy(data + size, &nameSize, s);
  size += s;

  // Length of Skin
  int skinSize = this->skin.size();
  s = sizeof(skinSize);
  memcpy(data + size, &skinSize, s);
  size += s;

  // Length of ControlPoints
  int pointsLen = this->controlPoints.size();
  s = sizeof(pointsLen);
  memcpy(data + size, &pointsLen, s);
  size += s;

  // Name
  s = nameSize;
  memcpy(data + size, this->name.c_str(), s);
  size += s;

  // Skin
  s = skinSize;
  memcpy(data + size, this->skin.c_str(), s);
  size += s;

  // ControlPoints
  s = POINT_ENCODED_LENGTH;
  for(int i = 0; i < pointsLen; i++){
    memcpy(data + size, this->controlPoints[i].encode().c_str(), s);
    size += s;
  }

  // Direction
  s = sizeof(this->direction);
  memcpy(data + size, &(this->direction), s);
  size += s;

  // Length
  s = sizeof(this->length);
  memcpy(data + size, &(this->length), s);
  size += s;

  // Score
  s = sizeof(this->score);
  memcpy(data + size, &(this->score), s);
  size += s;

  // Ammo
  s = sizeof(this->ammo);
  memcpy(data + size, &(this->ammo), s);
  size += s;

  // Speed
  s = sizeof(this->speed);
  memcpy(data + size, &(this->speed), s);
  size += s;

  return string(data, size);
}

string Snake::encodeId(){
  char *data = new char[sizeof(this->id)];
  int size = 0;
  int s = 0;
  // ID
  s = sizeof(this->id);
  memcpy(data + size, &(this->id), s);
  size += s;

  return string(data, size);
}

string Snake::encodeDataFromTick(){
  int len = 0;
  len += sizeof(this->id);
  len += POINT_ENCODED_LENGTH;
  len += sizeof(this->direction);
  len += sizeof(this->length);
  len += sizeof(this->score);
  len += sizeof(this->ammo);
  len += sizeof(this->speed);

  char *data = new char[len];
  int size = 0, s;

  // ID
  s = sizeof(this->id);
  memcpy(data + size, &(this->id), s);
  size += s;

  // LastPoint
  s = POINT_ENCODED_LENGTH;
  memcpy(data + size, this->controlPoints.back().encode().c_str(), s);
  size += s;

  // Direction
  s = sizeof(this->direction);
  memcpy(data + size, &(this->direction), s);
  size += s;

  // Length
  s = sizeof(this->length);
  memcpy(data + size, &(this->length), s);
  size += s;

  // Score
  s = sizeof(this->score);
  memcpy(data + size, &(this->score), s);
  size += s;

  // Ammo
  s = sizeof(this->ammo);
  memcpy(data + size, &(this->ammo), s);
  size += s;

  // Speed
  s = sizeof(this->speed);
  memcpy(data + size, &(this->speed), s);
  size += s;

  return string(data, size);
}

string Snake::encodeScore(){
  int len = 0;
  len += sizeof(this->id);
  len += sizeof(int) + this->name.size() * 1; // 1 for sizeof(char)
  len += sizeof(this->score);

  char *data = new char[len];
  int size = 0, s;

  // Length of Name
  int nameSize = this->name.size();
  s = sizeof(nameSize);
  memcpy(data + size, &nameSize, s);
  size += s;

  // Score
  s = sizeof(this->score);
  memcpy(data + size, &(this->score), s);
  size += s;

  // Name
  s = nameSize;
  memcpy(data + size, this->name.c_str(), s);
  size += s;

  return string(data, size);
}

Snake Snake::decode(string input){
  const char *data = input.c_str();
  int size = 0;

  // ID
  int id = 0;
  int s = sizeof(id);
  memcpy(&id, data + size, s);
  size += s;

  // NameLength
  int nameLen;
  s = sizeof(nameLen);
  memcpy(&nameLen, data + size, s);
  size += s;

  // SkinLength
  int skinLen = 0;
  s = sizeof(skinLen);
  memcpy(&skinLen, data + size, s);
  size += s;

  // Length of ControlPoints
  int pointsLen;
  s = sizeof(pointsLen);
  memcpy(&(pointsLen), data + size, s);
  size += s;

  // Name
  s = nameLen;
  string name(data + size, s);
  size += s;

  // Skin
  s = skinLen;
  string skin(data + size, s);
  size += s;

  Snake object(name, skin);
  object.id = id;

  // Points
  s = POINT_ENCODED_LENGTH;
  for(int i = 0; i < pointsLen; i++){
    Point newPoint = Point::decode(data + size);
    object.controlPoints.push_back(newPoint);
    size += s;
  }

  // Direction
  s = sizeof(object.direction);
  memcpy(&(object.direction), data + size, s);
  size += s;

  // Length
  s = sizeof(object.length);
  memcpy(&(object.length), data + size, s);
  size += s;

  // Score
  s = sizeof(object.score);
  memcpy(&(object.score), data + size, s);
  size += s;

  // Ammo
  s = sizeof(object.ammo);
  memcpy(&(object.ammo), data + size, s);
  size += s;

  // Speed
  s = sizeof(object.speed);
  memcpy(&(object.speed), data + size, s);
  size += s;

  return object;
}

bool Snake::operator == (const Snake & s)
{
  if(this->id == s.id)
    return true;
  else
    return false;
}


bool do_lines_cross(Point p1, Point p2, Point l1, Point l2)
{

  Point p = Point(p2.x - p1.x, p2.y - p1.y);
  Point l = Point(l2.x - l1.x, l2.y - l1.y);

  float pA = p2.y - p1.y;
  float pB = p1.x - p2.x;
  float pC = -(pA * p1.x + pB * p1.y);

  float lA = l2.y - l1.y;
  float lB = l1.x - l2.x;
  float lC = -(lA * l1.x + lB * l1.y);

  if(pA * lB == lA * pB){
    if(lC == pC){
      std::cout << "Same line ";
      std::cout << p1.x << ":" << p1.y << " ";
      std::cout << p2.x << ":" << p2.y << " ";
      std::cout << l1.x << ":" << l1.y << " ";
      std::cout << l2.x << ":" << l2.y << " --- ";
      std::cout << pA << ' ' << pB << ' ' << pC << " ; ";
      std::cout << lA << ' ' << lB << ' ' << lC << " ; ";
      std::cout << std::endl;
    }
    if(lC != pC){
      return false;
    }
  }

  float x = (pB * lC - lB * pC) / (pA * lB - lA * pB);
  float y = (pA * lC - lA * pC) / (lA * pB - pA * lB);
  Point crossingPoint(x, y);
  Rect linePzone(p1.x, p1.y, p.x, p.y);
  Rect lineLzone(l1.x, l1.y, l.x, l.y);

  if(!linePzone.contains(crossingPoint)){
    return false;
  }
  if(!lineLzone.contains(crossingPoint)){
    return false;
  }
  std::cout << "Normal collision." << std::endl;
  return true;
}

#endif
