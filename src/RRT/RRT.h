#ifndef _RRT_H_
#define _RRT_H_

#include "tree.h"
#include "../map.h"
#include <vector>
#include <ctime>

using namespace cv;

class RRT
{
public:
	RRT(Map& map);
	~RRT();

	/**
	 * @brief 
	 * @return 
	 */
	void findPath();
private:
	Tree tree_;
	//TODO(gcx): RRT should not store an object of Map which should be passed into the pathFinder(); dijkstra and astar are the same
	Map map_;
	Mat mat_bin_;
	vector<int> map_size_;
	vector<int> point_start_;
	vector<int> point_goal_;
	double step_size_;
	double goal_range_;

	/**
	 * @brief get a point which is generated randomly
	 * @return a point
	 */
	vector<int> sample();

	/**
	 * @brief get a point is closest to the point_rand
	 * @return a point
	 */
	inline Tree::TreeNode* getNear(vector<int> point_rand);

	/**
	 * @brief get a point step_size_ away from the point_near along the direction from point_near to point_rand
	 * @return a point 
	 */
	vector<int> steer(vector<int> point_rand, vector<int> point_near);

	//modify:has been moved to src/map.h
	/**
	 * @brief get distance
	 * @param two point
	 * @return the Euclidean Distance between x1 and x2
	 */
	// double getDistance(vector<int> x1, vector<int> x2);

	/**
	 * @brief check success to find the path
	 * @param a point which was add to the tree just now
	 * @return true -- success; false -- do not success yet
	 */
	inline bool isSuccess(vector<int> point_new);

	/**
	 * @brief check if the line which links point1 and point1 is collision free
	 * @param two points
	 * @return true -- collision free; false -- collison occurs
	 */
	bool collisionCheck(vector<int> point1, vector<int> point2);

	//modify:has been moved to src/map.h
	/**
	 * @check if the point is in the obstacle
	 * @param a point
	 * @return true -- outside the obstacle; false -- in the obstacle
	 */
	// bool isFeasiblePoint(vector<int> point);
};

RRT::RRT(Map& map) : map_(map), point_start_(map.getStart()), point_goal_(map.getGoal()), map_size_(map.getMapSize()), mat_bin_(map.getMatBin()) {
	goal_range_ = 20;
	step_size_ = 20;
	tree_.setRoot(point_start_[0], point_start_[1]);
}

RRT::~RRT() {}

void RRT::findPath() {
	Mat mat_temp = map_.getMat();

	circle(mat_temp, Point(point_start_[1], point_start_[0]), 8, Scalar(0, 0, 255), -1);	//red
	circle(mat_temp, Point(point_goal_[1], point_goal_[0]), 8, Scalar(0, 255, 0), -1);		//green

	vector<int> point_rand;
	Tree::TreeNode* node_near = nullptr;
	vector<int> point_near;
	vector<int> point_new = {0,0};
	Tree::TreeNode* node_new = nullptr;
	while (!isSuccess(point_new)) {
		point_rand = sample();
		node_near = getNear(point_rand);
		point_near = node_near->position;
		point_new = steer(point_rand, point_near);
		if (collisionCheck(point_new, point_near)) {
			circle(mat_temp, Point(point_rand[1], point_rand[0]), 4, Scalar(255, 0, 0), -1);	//blue
			circle(mat_temp, Point(point_new[1], point_new[0]), 4, Scalar(0, 0, 255), -1);		//red
			node_new = tree_.addNode(node_near, point_new);
			line(mat_temp, Point(point_new[1], point_new[0]), Point(point_near[1], point_near[0]), Scalar(0, 0, 255), 1, CV_AA); //red
		}
		else {
			circle(mat_temp, Point(point_rand[1], point_rand[0]), 4, Scalar(0, 255, 255), -1);	//yellow
		}
		Mat mat_temp1 = mat_temp.clone();
		circle(mat_temp1, Point(point_near[1], point_near[0]), 8, Scalar(255, 0, 0), 2);
		imshow("RRT visulization", mat_temp1);
		waitKey(100);
	}

	vector<int> point_path(point_new);
	//Tree::TreeNode* node_path = tree_.findNode(point_path);
	Tree::TreeNode* node_path = node_new;
	while (point_path != point_start_) {
		circle(mat_temp, Point(point_path[1], point_path[0]), 4, Scalar(0, 255, 0), -1);		//green
		line(mat_temp, Point(point_path[1], point_path[0]), Point(node_path->parent->position[1], node_path->parent->position[0]), Scalar(0, 255, 0), 1, CV_AA);//green
		imshow("RRT visulization", mat_temp);
		waitKey(10);

		node_path = node_path->parent;
		point_path = node_path->position;
	}

	waitKey(0);
}

vector<int> RRT::sample() {
	//srand((int)time(0));
	int point_rand_x = rand() % map_size_[0];
	int point_rand_y = rand() % map_size_[1];
	return vector<int>{point_rand_x, point_rand_y};
}

inline Tree::TreeNode* RRT::getNear(vector<int> point_rand) {
	return tree_.getNearestNode(point_rand);
}

vector<int> RRT::steer(vector<int> point_rand, vector<int> point_near) {
	double distance = map_.getDistance(point_rand, point_near);
	vector<int> point{0,0};
	point[0] = (int)(point_near[0] + (point_rand[0] - point_near[0]) * step_size_ / distance);
	point[1] = (int)(point_near[1] + (point_rand[1] - point_near[1]) * step_size_ / distance);
	return point;
}

inline bool RRT::isSuccess(vector<int> point_new) {
	if (goal_range_ > map_.getDistance(point_new, point_goal_)) {
		return true;
	}
	return false;
}

// double RRT::getDistance(vector<int> x1, vector<int> x2) {
// 	return sqrt((x1[0] - x2[0]) * (x1[0] - x2[0]) + (x1[1] - x2[1]) * (x1[1] - x2[1]));
// }

bool RRT::collisionCheck(vector<int> point1, vector<int> point2) {
	//return isFeasiblePoint(point1);
	int distance = map_.getDistance(point1, point2);
	vector<int> point_temp{point1[0], point1[1]};
	for (int i = 0; i < distance; ++i) {
		point_temp[0] = point1[0] + (int)((point2[0] - point1[0]) * i / distance);
		point_temp[1] = point1[1] + (int)((point2[1] - point1[1]) * i / distance);
		if (!map_.isFeasiblePoint(point_temp)) {
			cout << " false" << endl;
			return false;
		}
		else {
			cout << " true" << endl;
		}
	}
	return true;
}

// bool RRT::isFeasiblePoint(vector<int> point) {
// 	if (point[0] > 0 && point[0] < map_size_[0] &&
// 		point[1] > 0 && point[1] < map_size_[1] &&
// 		(int)mat_bin_.at<uchar>(point[0], point[1]) < 100)
// 	{
// 		return false;
// 	}
// 	return true;
// }

#endif // !_RRT_H_