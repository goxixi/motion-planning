#ifndef _D_STAR_H_
#define _D_STAR_H_

#include "graph_search.h"
#include "../common/visualization"

class DStar : public GraphSearcher {
public:
    DStar();
    ~DStar();
    bool findPath();
private:
    double dis_sensor_detect;   // the obstacle which is most far away from the robot that the sensor can detect

    void processState();
    void modifyCost();
};

DStar::DStar(const GripMap& _map, const common::Point& _point_start, const common::Point& _point_goal) : GraphSearcher(_map, _point_start, _point_goal) {}

DStar::~DStar() {}

bool DStar::findPath() {
	Mat mat_temp = map.getMat();
    
    PriQueueNode* dommy_node = createPriQueueNode(point_goal_, nullptr, 0.0);
    PriQueueNode* node_goal = createPriQueueNode(point_goal_, dommy_node, 0.0);
    open_list_.insert(node_goal);

    while(!open_list_.empty()) {
        processState();
    }
    

}

void DStar::processState() {
    PriQueneNode* node_cur = open_list_.pop();
    close_list_[node_cur->pos] = node_cur->parent->pos;
    map_.isFeasiblePoint(node_cur);
    double k_old = node_cur->f;
    double h_x = common::getDistance();
    
    // new obstacle appear
    if(node_cur->f < h_x) {

    } 
    // initial or the map doesn't change(static)
    else if(node_cur->f == h_x) {
        vector<common::Point> unexpanded_neighbors = getUnexpandedNeighbors(node_cur->pos);
        for(auto point : unexpanded_neighbors) {
            int index_in_openlist = open_list_.find(point);
            // index_in_openlist==-1 means that it isn't in the openlist(and the point is "unexpanded", so it is NEW)
            double g_temp = node_cur->g + common::getDistance(node_cur->pos, point); 
            if(index_in_openlist == -1) {
                PriQueueNode* temp = new PriQueueNode(point, node_cur, g_temp);
                open_list_.insert(temp);
            } else {
                if(g_temp < open_list_[index_in_openlist]->f) {
                    open_list_[index_in_openlist]->parent = cur_node; 
                    open_list_.decreaseKey(index_in_openlist, g_temp);
                }
            }
        }
    } 
    // obstacle disappear
    else {
        
    }
}

void DStar::modifyCost() {

}


#endif // !_D_STAR_H_
