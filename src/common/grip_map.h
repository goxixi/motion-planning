#ifndef _MAP_H_
#define _MAP_H_

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <vector>
#include <string>

#include "point.h"

using namespace cv;
using std::string;
using std::vector;
using std::pair;
using std::cout;

class GripMap
{
public:
	/**
	 * @brief struct
	 * @prama string of the path of the map's picture
	 * @prama start point's x coordinate
	 * @prama start point's y coordinate
	 * @prama goal point's x coordinate
	 * @prama goal point's y coordinate
	 */
	GripMap();
	GripMap(string picture, int start_x, int start_y, int goal_x, int goal_y);
	~GripMap();
	vector<int> getStart();
	vector<int> getGoal();
	Mat getMat();
	Mat getMatBin();
	vector<int> getMapSize();

	/**
	 * @brief get distance
	 * @param two point(vector<int>{x, y})
	 * @return the Euclidean Distance between x1 and x2
	 */
	double getDistance(vector<int> x1, vector<int> x2);

	/**
	 * @brief get distance
	 * @param two point(pair<int,int>)
	 * @return the Euclidean Distance between x1 and x2
	 */
	double getDistance(pair<int,int> x1, pair<int,int> x2);

	/**
	 * @check if the point is in the obstacle
	 * @param a point(vector<int>{x, y})
	 * @return true -- outside the obstacle; false -- in the obstacle
	 */
	bool isFeasiblePoint(vector<int> point);

	/**
	 * @check if the point is in the obstacle
	 * @param a point(pair<int,int>)
	 * @return true -- outside the obstacle; false -- in the obstacle
	 */
	bool isFeasiblePoint(pair<int,int> point);

	bool isFeasiblePoint(Point point);

private:
	//the mat with 3 channals
	Mat mat_init_;
	//the mat with 1 channal
	Mat mat_bin_;
	vector<int> start_point_ = {10,10};
	vector<int> goal_point_ = {50,50};
	vector<int> map_size_ = {0,0};
	vector<vector<int>> path_;
};

GripMap::GripMap() {};
GripMap::GripMap(string picture,int start_x, int start_y, int goal_x, int goal_y) {
	start_point_[0] = start_x;
	start_point_[1] = start_y;
	goal_point_[0] = goal_x;
	goal_point_[1] = goal_y;

	mat_init_ = cv::imread(picture);
	if (mat_init_.empty()) {
		printf("could not find the picture!\n");
	}
	map_size_[0] = mat_init_.rows;
	map_size_[1] = mat_init_.cols;

	cvtColor(mat_init_, mat_bin_, COLOR_BGR2GRAY);
	//threshold(mat_bin_, mat_bin_, 100, 200, THRESH_BINARY);
}

GripMap::~GripMap() {}

vector<int> GripMap::getStart() {
	return start_point_;
}

vector<int> GripMap::getGoal() {
	return goal_point_;
}

Mat GripMap::getMat() {
	return mat_init_.clone();
}

Mat GripMap::getMatBin() {
	return mat_bin_.clone();
}

vector<int> GripMap::getMapSize() {
	return map_size_;
}

double GripMap::getDistance(vector<int> x1, vector<int> x2) {
	if(x1[0] < 0 || x1[0] >= map_size_[0] ||
		x1[1] < 0 || x1[1] >= map_size_[1]) 
	{
		cout << "fail: the first point is out the map\n";
		return -1;
	}
	if(x2[0] < 0 || x2[0] >= map_size_[0] ||
		x2[1] < 0 || x2[1] >= map_size_[1]) 
	{
		cout << "fail: the second point is out the map\n";
		return -1;
	}
	return sqrt((x1[0] - x2[0]) * (x1[0] - x2[0]) + (x1[1] - x2[1]) * (x1[1] - x2[1]));
}

double GripMap::getDistance(pair<int,int> x1, pair<int,int> x2) {
	if(x1.first < 0 || x1.first >= map_size_[0] ||
		x1.second < 0 || x1.second >= map_size_[1]) 
	{
		cout << "fail: the first point is out the map\n";
		return -1;
	}
	if(x2.first < 0 || x2.first >= map_size_[0] ||
		x2.second < 0 || x2.second >= map_size_[1]) 
	{
		cout << "fail: the second point is out the map\n";
		return -1;
	}
	return sqrt((x1.first - x2.first) * (x1.first - x2.first) 
				+ (x1.second - x2.second) * (x1.second - x2.second));
}

bool GripMap::isFeasiblePoint(vector<int> point) {
	if (point[0] > 0 && point[0] < map_size_[0] &&
		point[1] > 0 && point[1] < map_size_[1] &&
		(int)mat_bin_.at<uchar>(point[0], point[1]) < 100)
	{
		return false;
	}
	return true;
}

bool GripMap::isFeasiblePoint(pair<int,int> point) {
	if (point.first < 0 || point.first > map_size_[0] ||
		point.second < 0 || point.second > map_size_[1] ||
		(int)mat_bin_.at<uchar>(point.first, point.second) < 100)
	{
		return false;
	}
	return true;
}

bool GripMap::isFeasiblePoint(Point point) {
	if (point.x < 0 || point.y > map_size_[0] ||
		point.x < 0 || point.y > map_size_[1] ||
		(int)mat_bin_.at<uchar>(point.x, point.y) < 100)
	{
		return false;
	}
	return true;
}

#endif // !_MAP_H_
