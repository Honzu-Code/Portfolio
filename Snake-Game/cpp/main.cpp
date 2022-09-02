#include <iostream>
#include "Point.h"
#include "Vector.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Bullet.h"
#include "Food.h"
#include "Snake.h"
#include "Server.h"
#include <limits>
using std::cout;
using std::endl;
using std::string;

struct struktura
{
  int id;
  string nazwa;
};

int main()
{

  srand(time(NULL));
  Point p(10,30);
  Point p2(5,10);
  Vector v(5,6);
  Vector v2(4,6);
  v.add(v2);
  v.apply_on(p);

  cout << "p.x = " << p.x << ", p.y = " << p.y << endl;

  cout << p.distance(p2) << endl;

  struktura str = {2,"POPO"};
  cout << str.nazwa << endl;
  cout << endl << endl;

  float scale = rand() / (float) RAND_MAX;
  float scale2 = rand() / (float) RAND_MAX;
  cout << scale << endl;
  cout << scale2 << endl;

  cout << "Point and Vector encode/decode tests.";

  cout << "p2: x=" << p2.x << " y=" << p2.y << endl;
  Point p3 = Point::decode(p2.encode());
  cout << "p3 = p2: x=" << p3.x << " y=" << p3.y << endl;

  cout << "v2: d=" << v2.direction << " l=" << v2.length << endl;
  Vector v3 = Vector::decode(v2.encode());
  cout << "v3 = v2: d=" << v3.direction << " l=" << v3.length << endl;

  cout << "Food constructor test:" << endl;

  Food a(Point(5, 7), Vector(0, 2), 3);
  cout << a.x << " ";
  cout << a.y << " ";
  cout << a.direction << " ";
  cout << a.length << " ";
  cout << a.size << endl;


  cout << "Bullet constructor test:" << endl;

  Bullet b(Point(5, 7), 0.0, -1);
  cout << b.x << " ";
  cout << b.y << " ";
  cout << b.direction << " ";
  cout << b.length << endl;

  cout << "Bullet moved towards positive x:" << endl;
  b.move();
  cout << b.x << " ";
  cout << b.y << " ";
  cout << b.direction << " ";
  cout << b.length << endl;


  Point p4(1,2);
  // cout << "Creating snake:)" << endl;  Test not finished, i'm too lazy to test all that.
  Snake goshko("Goshko123", "fitnessman.png");
  goshko.controlPoints.push_back(p4);
  goshko.move();
  Snake goshko2 = Snake::decode(goshko.encode());
  cout << "creating Snake Goshko!" << goshko.controlPoints[0].x << ", " << goshko.controlPoints[0].y << endl;
  cout << "creating Snake Goshko2!" << goshko2.controlPoints[0].x << ", " << goshko2.controlPoints[0].y << endl;

  if(std::numeric_limits<float>::is_iec559)
    cout << "Work" << endl;
  else
    cout << "Doesn't Work" << endl;

  return 0;
}
