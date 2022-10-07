#ifndef _GRAPH_SEARCH_
#define _GRAPH_SEARCH_

#include <vector>
#include <queue>
#include <utility>
#include <set>

#include "../map.h"
#include "pri_queue.h"

using namespace std;

class GraphSearcher
{
public:
    GraphSearcher();
    ~GraphSearcher();
    vector<pair<int,int>> getPath();

protected:
    PriQueue open_list_;
    set<pair<int,int>> close_list_;    //point, point's parent

    pair<int, int> start_point_;
    pair<int, int> goal_point_;
    vector<pair<int, int>> path_;
    Map map_;


    PriQueueNode* createPriQueueNode(pair<int,int> point, PriQueueNode* parent, double cost);

    vector<pair<int,int>> getUnexpandedNeighbors(pair<int,int> point);
};

GraphSearcher::GraphSearcher() {};

GraphSearcher::~GraphSearcher() {};

vector<pair<int,int>> GraphSearcher::getPath() {
    return path_;
}

PriQueueNode* GraphSearcher::createPriQueueNode(pair<int,int> point, PriQueueNode* parent, double cost) {
    PriQueueNode* openlist_node = new(PriQueueNode);
    openlist_node->pos = point;
    openlist_node->parent = parent;
    openlist_node->cost = cost;
    return openlist_node;
}

vector<pair<int,int>> GraphSearcher::getUnexpandedNeighbors(pair<int,int> point) {
    vector<pair<int,int>> neighbors;

    for(int i=-1; i<=1; ++i) {
        for(int j=-1; j<=1; ++j) {
            if(close_list_.find(point) != close_list_.end() || (i==0 && j==0)) {
                break;
            }
            neighbors.emplace_back(pair<int,int>{point.first+i, point.second+j});
        }
    }
    return neighbors;
}

#endif // !_GRAPH_SEARCH_