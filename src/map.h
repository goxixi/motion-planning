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
	Map(string picture, int start_x, int start_y, int goal_x, int goal_y);
	~Map();
	vector<int> getStart();
	vector<int> getGoal();
	Mat getMat();
	Mat getMatBin();
	vector<int> getMapSize();
private:
	//三通道的地图Mat
	Mat mat_init_;
	//单通道的地图Mat
	Mat mat_bin;
	vector<int> start_point_ = {10,10};
	vector<int> goal_point_ = {50,50};
	vector<int> map_size_ = {0,0};
	vector<vector<int>> path_;
};

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
	//灰度化
	cvtColor(mat_init_, mat_bin, COLOR_BGR2GRAY);
	//二值化
	//threshold(mat_bin, mat_bin, 100, 200, THRESH_BINARY);
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
	return mat_bin.clone();
}

vector<int> Map::getMapSize() {
	return map_size_;
}

#endif // !_MAP_H_
