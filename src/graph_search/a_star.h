#ifndef _A_STAR_
#define _A_STAR_

#include "graph_search.h"

class AStar : public GraphSearcher
{
public:
    AStar();
    ~AStar();
    vector<int> findPath();
private:
    
};

AStar::AStar() {}

AStar::~AStar() {};

bool AStar::findPath() {
	Mat mat_temp = map_.getMat();

    circle(mat_temp, Point(point_start_.second, point_start_.first), 8, Scalar(0, 0, 255), -1);	    //red
	circle(mat_temp, Point(point_goal_.second, point_goal_.first), 8, Scalar(0, 255, 0), -1);		//green

    PriQueueNode* init_node = createPriQueueNode(point_start_, nullptr,0.0);
    PriQueueNode* openlist_node = createPriQueueNode(point_start_,init_node,0.0);
    open_list_.insert(openlist_node);
    while (!open_list_.empty()) {
        PriQueueNode* openlist_node = open_list_.top();
        circle(mat_temp, Point(openlist_node->pos.second, openlist_node->pos.first), 2, Scalar(255, 0, 0), -1);//blue
        // close_list_.insert(openlist_node->pos);
        close_list_[openlist_node->pos] = openlist_node->parent->pos;
        open_list_.pop();

        if(openlist_node->pos == point_goal_) {
            pair<int,int> point_path = openlist_node->pos;
            pair<int,int> point_path_parent = openlist_node->pos;
            while(point_path != point_start_) {
                circle(mat_temp, Point(point_path.second, point_path.first), 2, Scalar(0, 0, 255), -1);	    //red
                line(mat_temp, Point(point_path_parent.second, point_path_parent.first), Point(point_path.second, point_path.first), Scalar(0, 0, 255), 1, CV_AA);//red
                point_path_parent = point_path;
                point_path = close_list_[point_path]; //point_path = point_path's parent

                imshow("A* visulization", mat_temp);
                waitKey(10);
            }

            waitKey(0);
            return true;
        }

        vector<pair<int,int>> unexpaned_neighbors = getUnexpandedNeighbors(openlist_node->pos);
        for(auto point : unexpaned_neighbors) {
            int index_in_openlist = open_list_.find(point);
            if(index_in_openlist == -1) {
                double cost_temp = openlist_node->cost + map_.getDistance(openlist_node->pos, point);
                PriQueue* 
                open_list_.insert(createPriQueueNode(point, openlist_node, cost_temp));
                circle(mat_temp, Point(point.second, point.first), 2, Scalar(0, 255, 0), -1);
            } else {
                open_list_.decreaseKey(index_in_openlist, openlist_node->cost + map_.getDistance(point, openlist_node->pos));
            }
        }

        imshow("A* visulization", mat_temp);
        waitKey(1);
    }

    return false;
}

#endif // !_A_STAR_