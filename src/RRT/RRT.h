#ifndef _RRT_H_
#define _RRT_H_

#include <vector>
#include <ctime>

#include "tree.h"
#include "../common/grip_map.h"
#include "../common/point.h"

using namespace cv;
using std::vector;
using common::GripMap;

class RRT
{
public:
	RRT(const GripMap& _map, const common::Point& _point_start, const common::Point& _point_goal);
	~RRT();

	/**
	 * @brief 
	 * @return 
	 */
	void findPath();
private:
	Tree tree_;
	//TODO(gcx): RRT should not store an object of GripMap which should be passed into the pathFinder(); dijkstra and astar are the same
	GripMap map_;
	Mat mat_bin_;
	common::Point point_start_;
	common::Point point_goal_;
	double step_size_;
	double goal_range_;

	/**
	 * @brief get a point which is generated randomly
	 * @return a point
	 */
	common::Point sample();

	/**
	 * @brief get a point is closest to the point_rand
	 * @return a point
	 */
	inline Tree::TreeNode* getNear(common::Point point_rand);

	/**
	 * @brief get a point step_size_ away from the point_near along the direction from point_near to point_rand
	 * @return a point 
	 */
	common::Point steer(common::Point point_rand, common::Point point_near);

	/**
	 * @brief check success to find the path
	 * @param a point which was add to the tree just now
	 * @return true -- success; false -- do not success yet
	 */
	inline bool isSuccess(common::Point point_new);

	/**
	 * @brief check if the line which links point1 and point1 is collision free
	 * @param two points
	 * @return true -- collision free; false -- collison occurs
	 */
	bool collisionCheck(common::Point point1, common::Point point2);
};

RRT::RRT(const GripMap& _map, const common::Point& _point_start, const common::Point& _point_goal) : map_(_map), point_start_(_point_start), point_goal_(_point_goal) {
	goal_range_ = 20;
	step_size_ = 20;
	tree_.setRoot(point_start_.x, point_start_.y);
	mat_bin_ = map_.getMatBin();
}

RRT::~RRT() {}

void RRT::findPath() {
	Mat mat_temp = map_.getMat();

	circle(mat_temp, Point(point_start_.y, point_start_.x), 8, Scalar(0, 0, 255), -1);	//red
	circle(mat_temp, Point(point_goal_.y, point_goal_.x), 8, Scalar(0, 255, 0), -1);		//green

	common::Point point_rand;
	Tree::TreeNode* node_near = nullptr;
	common::Point point_near;
	common::Point point_new = {0,0};
	Tree::TreeNode* node_new = nullptr;
	while (!isSuccess(point_new)) {
		point_rand = sample();
		node_near = getNear(point_rand);
		point_near = node_near->position;
		point_new = steer(point_rand, point_near);
		if (collisionCheck(point_new, point_near)) {
			circle(mat_temp, Point(point_rand.y, point_rand.x), 4, Scalar(255, 0, 0), -1);	//blue
			circle(mat_temp, Point(point_new.y, point_new.x), 4, Scalar(0, 0, 255), -1);		//red
			node_new = tree_.addNode(node_near, point_new);
			line(mat_temp, Point(point_new.y, point_new.x), Point(point_near.y, point_near.x), Scalar(0, 0, 255), 1, CV_AA); //red
		}
		else {
			circle(mat_temp, Point(point_rand.y, point_rand.x), 4, Scalar(0, 255, 255), -1);	//yellow
		}
		Mat mat_temp1 = mat_temp.clone();
		circle(mat_temp1, Point(point_near.y, point_near.x), 8, Scalar(255, 0, 0), 2);
		imshow("RRT visulization", mat_temp1);
		waitKey(10);
	}


	common::Point point_path(point_new);
	//Tree::TreeNode* node_path = tree_.findNode(point_path);
	Tree::TreeNode* node_path = node_new;
	while (point_path != point_start_) {
		circle(mat_temp, Point(point_path.y, point_path.x), 4, Scalar(0, 255, 0), -1);		//green
		line(mat_temp, Point(point_path.y, point_path.x), Point(node_path->parent->position.y, node_path->parent->position.x), Scalar(0, 255, 0), 1, CV_AA);//green
		imshow("RRT visulization", mat_temp);
		waitKey(10);

		node_path = node_path->parent;
		point_path = node_path->position;
	}

	waitKey(0);
}

common::Point  RRT::sample() {
	//srand((int)time(0));
	vector<int> map_size = map_.getMapSize();
	int point_rand_x = rand() % map_size[0];
	int point_rand_y = rand() % map_size[1];
	return common::Point{point_rand_x, point_rand_y};
}

inline Tree::TreeNode* RRT::getNear(common::Point  point_rand) {
	return tree_.getNearestNode(point_rand);
}

common::Point RRT::steer(common::Point point_rand, common::Point point_near) {
	double distance = common::getDistance(point_rand, point_near);
	common::Point point{0,0};
	point.x = (int)(point_near.x + (point_rand.x - point_near.x) * step_size_ / distance);
	point.y = (int)(point_near.y + (point_rand.y - point_near.y) * step_size_ / distance);
	return point;
}

inline bool RRT::isSuccess(common::Point point_new) {
	if (goal_range_ > common::getDistance(point_new, point_goal_)) {
		return true;
	}
	return false;
}

bool RRT::collisionCheck(common::Point point1, common::Point point2) {
	//return isFeasiblePoint(point1);
	int distance = common::getDistance(point1, point2);
	common::Point point_temp{point1.x, point1.y};
	for (int i = 0; i < distance; ++i) {
		point_temp.x = point1.x + (int)((point2.x - point1.x) * i / distance);
		point_temp.y = point1.y + (int)((point2.y - point1.y) * i / distance);
		if (!map_.isFeasiblePoint(point_temp)) {
			// cout << " false" << endl;
			return false;
		}
		else {
			// cout << " true" << endl;
		}
	}
	return true;
}

#endif // !_RRT_H_