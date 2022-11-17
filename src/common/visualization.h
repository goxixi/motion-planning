#ifndef _VISUALIZATION_H_
#define _VISUALIZATION_H_

#include <opencv2/opencv.hpp>
#include "point.h"
#include "grip_map.h"
using namespace cv;

class Visualization
{
public:
    Visualization(GripMap& map);
    // Visualization(Visualization& _vis);
    ~Visualization();

    void closeListPoint(const common::Point& point);  //blue
    void openListPoint(const common::Point& point);   //pink
    void samplePoint(const common::Point& point);
    void path(const common::Point& point1, const common::Point& point2);//red
    void startPoint(const common::Point& point);      //red
    void goalPoint(const common::Point& point);       //green
    /**
     * @brief draw a curve, of which expression is pf, on the mat
     * @param
     */
    void drawCurve(Mat& mat, double (*pf)(double x));

    void ego(const common::Point& point); //yellow rgb(252, 226, 219)
    void wait();
private:
    Mat mat_;
};

Visualization::Visualization(GripMap& map) : mat_(map.getMat()) {}

// Visualization(Visualization& _vis) : mat_(_vis.mat_) {}

Visualization::~Visualization() {}

void Visualization::closeListPoint(const common::Point& point) {
    circle(mat_, Point(point.y, point.x), 4, Scalar(122, 44, 67), -1);
    imshow("visulization", mat_);
    waitKey(1);
}

void Visualization::openListPoint(const common::Point& point) {
    circle(mat_, Point(point.y, point.x), 4, Scalar(177, 143, 255), -1);
    imshow("visulization", mat_);
    waitKey(1);
}

void Visualization::samplePoint(const common::Point& point) {
}

void Visualization::path(const common::Point& point1, const common::Point& point2) {
    line(mat_, Point(point1.y, point1.x), Point(point2.y, point2.x), Scalar(156, 72, 128), 2, CV_AA);
    imshow("visulization", mat_);
    waitKey(1);
}

void Visualization::startPoint(const common::Point& point) {
    circle(mat_, Point(point.y, point.x), 8, Scalar(0, 0, 255), -1);	    
    imshow("visulization", mat_);
    // waitKey(1);
}

void Visualization::goalPoint(const common::Point& point) {
	circle(mat_, Point(point.y, point.x), 8, Scalar(0, 255, 0), -1);		
    imshow("visulization", mat_);
    // waitKey(1);
}


void Visualization::ego(const common::Point& point) {
    Mat mat_temp = mat_.clone();
    circle(mat_temp, Point(point.y, point.x), 2, Scalar(0, 255, 0), -1);		
    imshow("visulization", mat_temp);
    waitKey(100);
}

void Visualization::wait() {
    imshow("visulization", mat_);
    waitKey(0);
}
#endif // !_VISUALIZATION_H_