#ifndef _GRAPH_SEARCH_
#define _GRAPH_SEARCH_

#include <vector>
#include <queue>
#include <utility>
#include <set>
#include <map>

#include "../common/grip_map.h"
#include "pri_queue.h"

using std::map;
using std::pair;

class GraphSearcher
{
public:
    GraphSearcher();
    ~GraphSearcher();
    void setMap(GripMap& map);
    vector<pair<int,int>> getPath();

protected:
    PriQueue open_list_;
    // set<pair<int,int>> close_list_;    //point
    map<pair<int,int>,pair<int,int>> close_list_;    //point, point's parent

    pair<int, int> point_start_;
    pair<int, int> point_goal_;
    vector<pair<int, int>> path_;
    GripMap map_;

    PriQueueNode* createPriQueueNode(pair<int,int> point, PriQueueNode* parent, double f);

    vector<pair<int,int>> getUnexpandedNeighbors(pair<int,int> point);
};

GraphSearcher::GraphSearcher() {};

GraphSearcher::~GraphSearcher() {};

void GraphSearcher::setMap(GripMap& map) {
    map_ = map;

    vector<int> start = map.getStart();
    vector<int> goal = map.getGoal();
    point_start_.first = start[0];
    point_start_.second = start[1];
    point_goal_.first = goal[0];
    point_goal_.second = goal[1];
}

vector<pair<int,int>> GraphSearcher::getPath() {
    return path_;
}

PriQueueNode* GraphSearcher::createPriQueueNode(pair<int,int> point, PriQueueNode* parent, double g) {
    PriQueueNode* openlist_node = new(PriQueueNode);
    openlist_node->pos = point;
    openlist_node->parent = parent;
    openlist_node->g = g;
    return openlist_node;
}

vector<pair<int,int>> GraphSearcher::getUnexpandedNeighbors(pair<int,int> point) {
    vector<pair<int,int>> neighbors;
    int step = 10;
    for(int i=-step; i<=step; i+=step) {
        for(int j=-step; j<=step; j+=step) {
            pair<int,int> point_new = pair<int,int>{point.first+i, point.second+j};
            if(map_.isFeasiblePoint(point_new) && close_list_.find(point_new) == close_list_.end() && (i!=0 || j!=0)) {
                neighbors.emplace_back(point_new);
            }
        }
    }
    return neighbors;
}

#endif // !_GRAPH_SEARCH_