#ifndef _A_STAR_
#define _A_STAR_

#include "graph_search.h"

class AStar : public GraphSearcher
{
public:
    AStar(/* args */);
    ~AStar();
    vector<int> findPath();
private:
    
};

AStar::AStar(/* args */)
{
}

AStar::~AStar() {};

bool AStar::findPath() {
    while(!open_list_.empty()) {

    }
    return false;
}

#endif // !_A_STAR_