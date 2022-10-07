#ifndef _MAP_H_
#define _MAP_H_

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <vector>
#include <string>

using namespace cv;

class Map
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
	Map();
	Map(string picture, int start_x, int start_y, int goal_x, int goal_y);
	~Map();
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
	 * @param a point
	 * @return true -- outside the obstacle; false -- in the obstacle
	 */
	bool isFeasiblePoint(vector<int> point);
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

Map::Map() {};
Map::Map(string picture,int start_x, int start_y, int goal_x, int goal_y) {
	start_point_[0] = start_x;
	start_point_[1] = start_y;
	goal_point_[0] = goal_x;
	goal_point_[1] = goal_y;

	mat_init_ = cv::imread(picture);
	if (mat_init_.empty()) {
		printf("could not find the picture!");
	}
	map_size_[0] = mat_init_.rows;
	map_size_[1] = mat_init_.cols;

	cvtColor(mat_init_, mat_bin_, COLOR_BGR2GRAY);
	//threshold(mat_bin_, mat_bin_, 100, 200, THRESH_BINARY);
}

Map::~Map() {}

vector<int> Map::getStart() {
	return start_point_;
}

vector<int> Map::getGoal() {
	return goal_point_;
}

Mat Map::getMat() {
	return mat_init_.clone();
}

Mat Map::getMatBin() {
	return mat_bin_.clone();
}

vector<int> Map::getMapSize() {
	return map_size_;
}

double Map::getDistance(vector<int> x1, vector<int> x2) {
	if(x1[0] < 0 || x1[0] >= map_size_[0] ||
		x1[1] < 0 || x1[1] >= map_size_[1]) 
	{
		cout << "fail: the first point is out the map";
		return -1;
	}
	if(x2[0] < 0 || x2[0] >= map_size_[0] ||
		x2[1] < 0 || x2[1] >= map_size_[1]) 
	{
		cout << "fail: the second point is out the map";
		return -1;
	}
	return sqrt((x1[0] - x2[0]) * (x1[0] - x2[0]) + (x1[1] - x2[1]) * (x1[1] - x2[1]));
}

double Map::getDistance(pair<int,int> x1, pair<int,int> x2) {
	if(x1.first < 0 || x1.first >= map_size_[0] ||
		x1.second < 0 || x1.second >= map_size_[1]) 
	{
		cout << "fail: the first point is out the map";
		return -1;
	}
	if(x2.first < 0 || x2.first >= map_size_[0] ||
		x2.second < 0 || x2.second >= map_size_[1]) 
	{
		cout << "fail: the second point is out the map";
		return -1;
	}
	return sqrt((x1.first - x2.first) * (x1.first - x2.first) 
				+ (x1.first - x2.first) * (x1.first - x2.first));
}

bool Map::isFeasiblePoint(vector<int> point) {
	if (point[0] > 0 && point[0] < map_size_[0] &&
		point[1] > 0 && point[1] < map_size_[1] &&
		(int)mat_bin_.at<uchar>(point[0], point[1]) < 100)
	{
		return false;
	}
	return true;
}

#endif // !_MAP_H_
