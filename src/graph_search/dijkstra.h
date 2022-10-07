#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_

#include "graph_search.h"

class Dijkstra : protected GraphSearcher
{
public:
    Dijkstra();
    ~Dijkstra();
    /**
     * @brief the core code of Dijkstra()
     * @return if find a path from start_point to goal_point 
     */
    bool findPath();
};

Dijkstra::Dijkstra() {};

Dijkstra::~Dijkstra() {};

bool Dijkstra::findPath() {
    PriQueueNode* openlist_node = createPriQueueNode(goal_point_,nullptr,0.0);
    open_list_.insert(openlist_node);
    while (!open_list_.empty()) {
        PriQueueNode* openlist_node = open_list_.top();

        close_list_.insert(openlist_node->pos);
        open_list_.pop();

        if(openlist_node->pos == goal_point_) {
            while(openlist_node->pos != start_point_) {
                path_.emplace_back(openlist_node->pos);
                openlist_node = openlist_node->parent;  //openlist_node = openlist_node's parent
            }
            return true;
        }

        vector<pair<int,int>> unexpaned_neighbors = getUnexpandedNeighbors(openlist_node->pos);
        for(auto point : unexpaned_neighbors) {
            int index_in_openlist = open_list_.find(point);
            if(index_in_openlist == -1) {
                double cost_temp = openlist_node->cost + map_.getDistance(openlist_node->pos, point);
                createPriQueueNode(point, openlist_node->parent, cost_temp);
            } else {
                open_list_.decreaseKey(index_in_openlist, openlist_node->cost + map_.getDistance(point, openlist_node->pos));
            }
        }
    }
    return false;
}

#endif // !_DIJKSTRA_H_