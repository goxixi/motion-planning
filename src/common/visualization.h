#include <opencv2/opencv.hpp>
#include "point.h"
using namespace cv;

class Visualization
{
public:
    visualization();
    ~visualization();

    void Waypoint(common::Point point);
    void Line(common::Point point1, common::Point point2);
    void StartPoint(common::Point point);
    void GoalPoint(common::Point point);
    /**
     * @brief draw a curve, of which expression is pf, on the mat
     * 
     */
    void drawCurve(Mat &mat, double (*pf)(double x));
private:


};

Visualization::Visualization() {}

Visualization::~Visualization() {}


void Visualization::Waypoint(common::Point point) {

}

void Visualization::Line(common::Point point1, common::Point point2) {

}

void Visualization::StartPoint(common::Point point) {
    circle(mat_temp, Point(point.y, point.x), 8, Scalar(0, 0, 255), -1);	    //red
}

void Visualization::GoalPoint(common::Point point) {
	circle(mat_temp, Point(point.y, point.x), 8, Scalar(0, 255, 0), -1);		//green
}