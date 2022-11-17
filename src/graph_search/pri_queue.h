#ifndef _PRI_QUEUE_H_
#define _PRI_QUEUE_H_

#include <utility>
#include <vector>

#include "../common/point.h"

using namespace std;

struct PriQueueNode {
    common::Point pos;
    PriQueueNode* parent;
    double g;
    double h;
    double f;

    PriQueueNode() : g(0), h(0) {};
    PriQueueNode(common::Point& _pos, PriQueueNode* _parent, double _g) : pos(_pos), parent(_parent), g(_g), h(0), f(g+h){};
    PriQueueNode(common::Point& _pos, PriQueueNode* _parent, double _g, double _h) : pos(_pos), parent(_parent), g(_g), h(_h), f(g+h) {};
};

class PriQueue {
public:
    PriQueue();

    ~PriQueue();

    PriQueueNode* top();

    PriQueueNode* pop();

    void removeFromOpen(PriQueueNode* node);

    void insert(common::Point pos, PriQueueNode* parent, double g, double h=0);

    void insert(PriQueueNode* new_node);

    void updateParent(int index, PriQueueNode* new_parent);

    bool decreaseKey(int index, double new_g);

    int find(common::Point);

    PriQueueNode* getNode(int index);

    bool empty();

    PriQueueNode* operator[](int i);
private:
    vector<PriQueueNode*> pri_que_; //why not a pri_queue? because the elements in it should be modifiable
};

PriQueue::PriQueue() {};

PriQueue::~PriQueue() {};

PriQueueNode* PriQueue::top() {
    PriQueueNode* node_min = pri_que_[0];
    int f_min = pri_que_[0]->f;
    for(int i=0; i<pri_que_.size(); ++i) {
        int f_node = pri_que_[i]->f;
        if(f_node < f_min) {
            f_min = f_node;
            node_min = pri_que_[i];
        }
    }
    return node_min;
}

PriQueueNode* PriQueue::pop() {
    PriQueueNode* node_min = pri_que_[0];
    // int f_min = pri_que_[0]->g + pri_que_[0]->h;
    int f_min = pri_que_[0]->f;
    int index_min = 0;
    for(int i=0; i<pri_que_.size(); ++i) {
        // int f_node = pri_que_[i]->g + pri_que_[i]->h;
        int f_node = pri_que_[i]->f;
        if(f_node < f_min) {
            f_min = f_node;
            node_min = pri_que_[i];
            index_min = i;
        }
    }
    auto it = pri_que_.begin() + index_min;
    pri_que_.erase(it);
    return node_min;
}

void PriQueue::insert(common::Point pos, PriQueueNode* parent, double g, double h) {
    PriQueueNode* new_node = new PriQueueNode(pos, parent, g, h);
    pri_que_.emplace_back(new_node);
}

void PriQueue::insert(PriQueueNode* new_node) {
    pri_que_.emplace_back(new_node);
}

void PriQueue::updateParent(int index, PriQueueNode* new_parent) {
    pri_que_[index]->parent = new_parent;
}

bool PriQueue::decreaseKey(int index, double new_g) {
    if(pri_que_[index]->g > new_g) { 
        pri_que_[index]->g = new_g;        
        pri_que_[index]->f = new_g + pri_que_[index]->h;    // update f. the h will be 0 when it runs dijkstra
        return true;
    }
    return false;
}

int PriQueue::find(common::Point point) {
    for(int i=0; i<pri_que_.size(); ++i) {
        if(pri_que_[i]->pos == point) {
            return i;
        }
    }
    return -1;
}

PriQueueNode* PriQueue::getNode(int index) {
    return pri_que_[index];
}

bool PriQueue::empty() {
    return pri_que_.empty();
}

PriQueueNode* PriQueue::operator[](int i) {
    return pri_que_[i]; 
}

#endif // !_PRI_QUEUE_H_