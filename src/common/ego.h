#ifndef _EGO_H_
#define _EGO_H_

#include <vector>
#include <algorithm>

#include "point.h"

using std::vector;

class Ego {
public:
    Ego(common::Point pos_, vector<double> size_=vector<double>{1, 0.5});
    ~Ego();
    void move(common::Point& desired_pos);
    common::Point getCurPos();
private:
    vector<int> size_;
    common::Point pos_;
};

Ego::Ego(common::Point pos_, vector<double> size_) {}

Ego::~Ego() {}

void Ego::move(common::Point& desired_pos) {
    // ego move to the next point
    pos_ = desired_pos;
}

common::Point Ego::getCurPos() {
    return pos_;
}


#endif // ! _EGO_H_