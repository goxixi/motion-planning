#ifndef _POINT_H_
#define _POINT_H_

#include <cmath>

namespace common {
struct Point {
  int x;
  int y;
  bool operator== (const Point& point);
  bool operator!= (const Point& point);
  bool operator< (const Point& point) const;
  friend double getDistance();
  
  Point() {}
  Point(int _x, int _y) : x(_x), y(_y) {}
  Point(const Point& _p) : x(_p.x), y(_p.y) {}
};

bool Point::operator== (const Point& point){
  if(point.x == x && point.y == y) {
    return true;
  }
  return false;
}

bool Point::operator!= (const Point& point){
  if(point.x != x || point.y != y) {
    return true;
  }
  return false;
}


bool Point::operator< (const Point& point) const{
  if(x > point.x) {
    return false;
  } else if(x < point.x) {
    return true;
  } else {
    if(x > point.x) {
      return false;
    } else if(y < point.y) {
      return true;
    } else {
      return false;
    }
  }
}

double getDistance(Point p1, Point p2) {
    return sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y));
}

}

#endif // !_POINT_H_
