#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_

#include "graph_search.h"

class Dijkstra : public GraphSearcher
{
public:
    Dijkstra();
    ~Dijkstra();
    /**
     * @brief the core code of Dijkstra()
     * @return if find a path from point_start to point_goal 
     */
    bool findPath();
};

Dijkstra::Dijkstra() {};

Dijkstra::~Dijkstra() {};

bool Dijkstra::findPath() {
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
            while(point_path != point_start_) {
                circle(mat_temp, Point(point_path.second, point_path.first), 2, Scalar(0, 0, 255), -1);	    //red
                point_path = close_list_[point_path]; //point_path = point_path's parent

                imshow("Dijkstra visulization", mat_temp);
                waitKey(10);
            }

            // imshow("Dijkstra visulization", mat_temp);
            waitKey(0);
            return true;
        }

        vector<pair<int,int>> unexpaned_neighbors = getUnexpandedNeighbors(openlist_node->pos);
        for(auto point : unexpaned_neighbors) {
            int index_in_openlist = open_list_.find(point);
            if(index_in_openlist == -1) {
                double cost_temp = openlist_node->cost + map_.getDistance(openlist_node->pos, point);
                open_list_.insert(createPriQueueNode(point, openlist_node, cost_temp));
                circle(mat_temp, Point(point.second, point.first), 2, Scalar(0, 255, 0), -1);
            } else {
                open_list_.decreaseKey(index_in_openlist, openlist_node->cost + map_.getDistance(point, openlist_node->pos));
            }
        }

        imshow("Dijkstra visulization", mat_temp);
        waitKey(1);
    }

    return false;
}

#endif // !_DIJKSTRA_H_