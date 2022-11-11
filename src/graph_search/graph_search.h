#ifndef _GRAPH_SEARCH_
#define _GRAPH_SEARCH_

#include <vector>
#include <queue>
#include <utility>
#include <set>
#include <map>

#include "../common/grip_map.h"
#include "../common/point.h"
#include "pri_queue.h"

using std::map;
using std::vector;
using common::GripMap;

class GraphSearcher
{
public:
    GraphSearcher(const GripMap& _map, const common::Point& _point_start, const common::Point& _point_goal);
    ~GraphSearcher();
    vector<common::Point> getPath();

protected:
    PriQueue open_list_;
    // set<common::Point> close_list_;    //point
    map<common::Point,common::Point> close_list_;    //point, point's parent

    common::Point point_start_;
    common::Point point_goal_;
    vector<common::Point> path_;
    GripMap map_;

    PriQueueNode* createPriQueueNode(common::Point& point, PriQueueNode* parent, double f);

    vector<common::Point> getUnexpandedNeighbors(common::Point& point);
};

GraphSearcher::GraphSearcher(const GripMap& _map, const common::Point& _point_start, const common::Point& _point_goal) : map_(_map), point_start_(_point_start), point_goal_(_point_goal) {};

GraphSearcher::~GraphSearcher() {};

vector<common::Point> GraphSearcher::getPath() {
    return path_;
}

PriQueueNode* GraphSearcher::createPriQueueNode(common::Point& point, PriQueueNode* parent, double g) {
    PriQueueNode* openlist_node = new(PriQueueNode);
    openlist_node->pos = point;
    openlist_node->parent = parent;
    openlist_node->g = g;
    return openlist_node;
}

vector<common::Point> GraphSearcher::getUnexpandedNeighbors(common::Point& point) {
    vector<common::Point> neighbors;
    int step = 10;
    for(int i=-step; i<=step; i+=step) {
        for(int j=-step; j<=step; j+=step) {
            common::Point point_new = common::Point{point.x+i, point.y+j};
            if(map_.isFeasiblePoint(point_new) && close_list_.find(point_new) == close_list_.end() && (i!=0 || j!=0)) {
                neighbors.emplace_back(point_new);
            }
        }
    }
    return neighbors;
}

#endif // !_GRAPH_SEARCH_