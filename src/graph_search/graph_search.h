#ifndef _GRAPH_SEARCH_
#define _GRAPH_SEARCH_

#include <vector>
#include <queue>
#include <utility>
#include <unordered_map>

#include "map.h"

using namespace std;

class GraphSearcher
{
public:
    GraphSearcher();
    ~GraphSearcher();
    vector<pair<int,int>> getPath();
private:
    struct OpenListNode {
        pair<int, int> 
        double h;
        double g;
        bool operator() () {
            return ;
        }
    }
    vector<vector<int>> graph_;
    priority_queue<pair<int,int>, vector<pair<int,int>>, OpenListNode> open_list;
    //point, point's parent
    unordered_map<pair<int,int>, pair<int,int>> closed_list_;

    pair<int, int> start_point_;
    pair<int, int> goal_point_;
    vector<pair<int, int>> path_;
};

GraphSearcher::GraphSearcher() {}

GraphSearcher::~GraphSearcher() {};


vector<pair<int,int>> GraphSearcher::getPath() {

}

#endif // !_GRAPH_SEARCH_