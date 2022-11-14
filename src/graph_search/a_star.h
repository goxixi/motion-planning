#ifndef _A_STAR_
#define _A_STAR_

#include "graph_search.h"

class AStar : public GraphSearcher
{
public:
    AStar(const GripMap& _map, const common::Point& _point_start, const common::Point& _point_goal);
    ~AStar();    
    /**
     * @brief the core code of A_star()
     * @return ture if find a path from point_start_ to point_goal_; otherwise false;
     */
    bool findPath();
private:
    
};

AStar::AStar(const GripMap& _map, const common::Point& _point_start, const common::Point& _point_goal) : GraphSearcher(_map, _point_start, _point_goal) {}

AStar::~AStar() {};

bool AStar::findPath() {
	Mat mat_temp = map_.getMat();

    circle(mat_temp, Point(point_start_.y, point_start_.x), 8, Scalar(0, 0, 255), -1);	    //red
	circle(mat_temp, Point(point_goal_.y, point_goal_.x), 8, Scalar(0, 255, 0), -1);		//green

    PriQueueNode* init_node = createPriQueueNode(point_start_, nullptr,0.0);
    PriQueueNode* node_start_ = createPriQueueNode(point_start_,init_node,0.0);
    open_list_.insert(node_start_);

    while (!open_list_.empty()) {
        PriQueueNode* openlist_node = open_list_.top();
        circle(mat_temp, Point(openlist_node->pos.y, openlist_node->pos.x), 2, Scalar(255, 0, 0), -1);//blue
        close_list_[openlist_node->pos] = openlist_node->parent->pos;
        open_list_.pop();

        // have found the goal, then get the path by getting the parent node of the current node recursively
        if(openlist_node->pos == point_goal_) {
            common::Point point_path = openlist_node->pos;
            common::Point point_path_parent = openlist_node->pos;
            while(point_path != point_start_) {
                circle(mat_temp, Point(point_path.y, point_path.x), 2, Scalar(0, 0, 255), -1);	    //red
                line(mat_temp, Point(point_path_parent.y, point_path_parent.x), Point(point_path.y, point_path.x), Scalar(0, 0, 255), 1, CV_AA);//red
                point_path_parent = point_path;
                point_path = close_list_[point_path]; //point_path = point_path's parent

                imshow("A* visulization", mat_temp);
                waitKey(10);
            }

            waitKey(0);
            return true;
        }

        // "unexpanded" means that the points have not been in the close_list
        vector<common::Point> unexpaned_neighbors = getUnexpandedNeighbors(openlist_node->pos);
        for(auto point : unexpaned_neighbors) {
            int index_in_openlist = open_list_.find(point);
            // index_in_openlist==-1 means that it isn't in the openlist(and the point is "unexpanded", so it is NEW)
            if(index_in_openlist == -1) {
                double g_temp = openlist_node->g + common::getDistance(openlist_node->pos, point);
                double h = common::getDistance(point, point_goal_);
                PriQueueNode* temp = new PriQueueNode(point, openlist_node, g_temp, h);
                open_list_.insert(temp);
                circle(mat_temp, Point(point.y, point.x), 2, Scalar(0, 255, 0), -1);
            } else {
                if(g_temp < open_list_[index_in_openlist]->f) {
                    open_list_[index_in_openlist]->parent = openlist_node;   //find a shorter path and update the path
                    open_list_.decreaseKey(index_in_openlist, g_temp);
                }
            }
        }

        imshow("A* visulization", mat_temp);
        waitKey(1);
    }

    return false;
}

#endif // !_A_STAR_