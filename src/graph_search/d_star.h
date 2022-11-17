#ifndef _D_STAR_H_
#define _D_STAR_H_

#include <float.h>

#include "graph_search.h"
#include "list.h"
#include "../common/visualization.h"

using std::vector;

#define MYMAX DBL_MAX - 1000

class DStar : public GraphSearcher{
public:
    DStar(const GripMap& _map, const common::Point& _point_start, const common::Point& _point_goal, Visualization& _vis);
    ~DStar();

    /**
     * @brief 
     */ 
    bool initial();    
    
    /**
     * @brief execute when it detect that the path is obstacle
     * @param 
     */
    bool modify(ListNode* node);

    /**
     * @brief 
     */ 
    List getPathTemp();

private:
    bool flag_finish_ = false;
    List list_;
    double dis_sensor_detect_;   // the obstacle which is most far away from the robot that the sensor can detect
    List path_temp_; // use path_temp_ to replace path_, because d_star require the history info to replan
    ListNode* cur_node; // a node save the info of the robot's current position
    Visualization vis_;
    Mat mat_;

    /**
     * @brief 
     */ 
    double processState();

    /**
     * @brief 
     */ 
    void modifyCost(ListNode* node);

    /**
     * @brief 
     */ 
    double cost(const common::Point& point1, const common::Point& point2);

    vector<common::Point> getNeighbor(const common::Point& pos);
};

DStar::DStar(const GripMap& _map, const common::Point& _point_start, const common::Point& _point_goal, Visualization& _vis)
            : GraphSearcher(_map, _point_start, _point_goal), mat_(map_.getMat()), vis_(_vis) 
{
    vis_.goalPoint(point_goal_);
    vis_.startPoint(point_start_);
}

DStar::~DStar() {}

bool DStar::initial() {
    
    list_.insert(point_goal_, nullptr, 0.0);

    while(flag_finish_ == false) {
        processState();
        if(list_.empty()) {
            return false;
        }
    }
    
    return true;
}

bool DStar::modify(ListNode* node_cur) {
    modifyCost(node_cur);
    double k_min = processState();
    while(k_min < node_cur->g) {
        k_min = processState();
    }
    
    return true;
}

List DStar::getPathTemp() {    
    return path_temp_;
}

double DStar::processState() {
    ListNode* node_cur = list_.pop();
    // vis_.closeListPoint(node_cur->pos);

    if(node_cur->pos == point_start_) {
        flag_finish_ = true;
        while(node_cur->pos != point_goal_) {
            path_temp_.insert(node_cur->pos, node_cur->parent, node_cur->g);
            vis_.path(node_cur->pos, node_cur->parent->pos);                

            node_cur = node_cur->parent;
        }
    }

    double k_old = node_cur->k;

    // new obstacle appear
    if(k_old < node_cur->g) {
        vector<common::Point> vec_neighbors = getNeighbor(node_cur->pos);
        for(auto point : vec_neighbors) {
            int id_in_list = list_.find(point);
            double g_temp = list_[id_in_list]->g + cost(point, node_cur->pos);
            
            if(id_in_list == -1) {
                list_.insert(point, node_cur, g_temp);
                vis_.openListPoint(point);
            } else if(list_[id_in_list]->g <= k_old && node_cur->g > g_temp) {
                list_[id_in_list]->tag = OPEN;
                list_[id_in_list]->parent = node_cur;
                node_cur->g = g_temp;
            }
        }
    }
    // initial or the map doesn't change(static)
    else if(k_old == node_cur->g) {
        vector<common::Point> vec_neighbors = getNeighbor(node_cur->pos);
        for(auto point : vec_neighbors) {
            int id_in_list = list_.find(point);
            double g_temp = node_cur->g + common::getDistance(node_cur->pos, point); 
            if(id_in_list == -1) {
                if(!map_.isFeasiblePoint(point)) {                    
                    list_.insert(point, node_cur, MYMAX, OBS);   
                    break;
                }
                list_.insert(point, node_cur, g_temp);            
                // vis_.openListPoint(point);
            } else if((list_[id_in_list]->parent != node_cur && list_[id_in_list]->g > g_temp) ||
                (list_[id_in_list]->parent != node_cur && list_[id_in_list]->g > g_temp)) {
                    list_[id_in_list]->parent = node_cur;
                    list_[id_in_list]->g = g_temp;
            }
        }
    }
    // obstacle disappear
    else {
    
    }
    return list_.top()->k;
}

void DStar::modifyCost(ListNode* node) {
    if(node->tag == CLOSE) { //is this judgement necessary?
        node->tag = OPEN;
    }   
}

double DStar::cost(const common::Point& point1, const common::Point& point2) {
    if(map_.isFeasiblePoint(point1)) {
        return MYMAX;
    }
    return common::getDistance(point1, point2);
}


vector<common::Point> DStar::getNeighbor(const common::Point& pos) {
    vector<common::Point> vec_neighbors;
    int step = 10;
    for(int i=-step; i<=step; i+=step) {
        for(int j=-step; j<=step; j+=step) {
            common::Point point_new = common::Point(pos.x+i, pos.y+j);
            if((i!=0 || j!=0) && (point_new.x>0 || point_new.x<map_.getMapSize()[0]) && (point_new.y>0 || point_new.y<map_.getMapSize()[1])) {
                vec_neighbors.emplace_back(point_new);
            }
        }
    }
    return vec_neighbors;
}

#endif // !_D_STAR_H_