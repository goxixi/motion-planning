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

namespace common{
class GripMap
{
public:
	/**
	 * @brief struct
	 * @prama string of the path of the map's picture
	 */
	GripMap();
	GripMap(string picture);
	GripMap(const GripMap& _grip_map);
	~GripMap();
	Mat getMat();
	Mat getOriginMat();
	Mat getMatBin();
	vector<int> getMapSize();

	/**
	 * @check if the point is in the obstacle
	 * @param a point(common::Point)
	 * @return true -- outside the obstacle; false -- in the obstacle
	 */
	bool isFeasiblePoint(common::Point point);

private:
	//the mat with 3 channals
	Mat mat_init_;
	//the mat with 1 channal
	Mat mat_bin_;
	vector<int> map_size_ = {0,0};
	vector<vector<int>> path_;
};


GripMap::GripMap() {};
GripMap::GripMap(string picture) {
	mat_init_ = cv::imread(picture);
	if (mat_init_.empty()) {
		printf("could not find the picture!\n");
	}
	map_size_[0] = mat_init_.rows;
	map_size_[1] = mat_init_.cols;

	cvtColor(mat_init_, mat_bin_, COLOR_BGR2GRAY);
	//threshold(mat_bin_, mat_bin_, 100, 200, THRESH_BINARY);
}


GripMap::GripMap(const GripMap& _grip_map) {
	mat_init_ = _grip_map.mat_init_;
	map_size_[0] = mat_init_.rows;
	map_size_[1] = mat_init_.cols;
	cvtColor(mat_init_, mat_bin_, COLOR_BGR2GRAY);
}

GripMap::~GripMap() {}

Mat GripMap::getMat() {
	return mat_init_.clone();
}

Mat GripMap::getOriginMat() {
	return mat_init_;
}

Mat GripMap::getMatBin() {
	return mat_bin_.clone();
}

vector<int> GripMap::getMapSize() {
	return map_size_;
}

bool GripMap::isFeasiblePoint(common::Point point) {
	if (point.x < 0 || point.x > map_size_[0] ||
		point.y < 0 || point.y > map_size_[1] ||
		(int)mat_bin_.at<uchar>(point.x, point.y) < 100)
	{
		return false;
	}
	return true;
}

}


#endif // !_MAP_H_
