#ifndef _PRI_QUEUE_H_
#define _PRI_QUEUE_H_

#include <utility>
#include <vector>

using namespace std;

struct PriQueueNode {
    pair<int,int> pos;
    PriQueueNode* parent;
    double g;
    double h;

    PriQueueNode() : g(0), h(0) {};
    PriQueueNode(pair<int,int> _pos, PriQueueNode* _parent, double _g) : pos(_pos), parent(_parent), g(_g), h(0){};
    PriQueueNode(pair<int,int> _pos, PriQueueNode* _parent, double _g, double _h) : pos(_pos), parent(_parent), g(_g), h(_h) {};
};

class PriQueue
{
public:
    PriQueue();
    ~PriQueue();
    PriQueueNode* top();
    PriQueueNode* pop();
    void insert(PriQueueNode* new_node);
    bool decreaseKey(int index, double new_g);
    int find(pair<int,int>);
    PriQueueNode* getNode(int index);
    bool empty();
private:
    vector<PriQueueNode*> pri_que_;
};


PriQueue::PriQueue() {};

PriQueue::~PriQueue() {};

PriQueueNode* PriQueue::top() {
    PriQueueNode* node_min = pri_que_[0];
    int f_min = pri_que_[0]->g + pri_que_[0]->h;
    for(auto node:pri_que_) {
        int f_node = node->g + node->h;
        if(f_node < f_min) {
            f_min = f_node;
            node_min = node;
        }
    }
    return node_min;
}

PriQueueNode* PriQueue::pop() {
    PriQueueNode* node_min = pri_que_[0];
    int f_min = pri_que_[0]->g + pri_que_[0]->h;
    int index_min = 0;
    for(int i=0; i<pri_que_.size(); ++i) {
        int f_node = pri_que_[i]->g + pri_que_[i]->h;
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

void PriQueue::insert(PriQueueNode* new_node) {
    pri_que_.emplace_back(new_node);
}

bool PriQueue::decreaseKey(int index, double new_g) {
    if(pri_que_[index]->g > new_g) { 
        pri_que_[index]->g = new_g;
        return true;
    }
    return false;
}

int PriQueue::find(pair<int,int> point) {
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

#endif // !_PRI_QUEUE_H_