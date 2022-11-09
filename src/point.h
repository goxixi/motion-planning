#ifndef _POINT_H_
#define _POINT_H_

#include <cmath>

namespace common {


class Point {
public:
  double x;
  double y;
  friend double getDistance();
};

double getDistance(Point p1, Point p2) {
    return sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y));
}

}



#endif // !_POINT_H_
