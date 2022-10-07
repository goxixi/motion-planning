#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_

#include "graph_search.h"

class Dijkstra : public GraphSearcher
{
public:
    Dijkstra(/* args */);
    ~Dijkstra();
    bool findPath();
private:

    
};

Dijkstra::Dijkstra(/* args */)
{
}

Dijkstra::~Dijkstra() {};

bool Dijkstra::findPath() {
    while (!open_list_.empty()) {
        pair<int, int> point_temp = open_list_.top()
        close_list_.emplace(point_temp);
        open_list_.pop();
        if(point_temp == goal_point) {
            while() {

            }
            reuturn true;
        }
    }

    return false;    
}

#endif // !_DIJKSTRA_H_