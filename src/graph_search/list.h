#ifndef _PRI_QUEUE2_H_
#define _PRI_QUEUE2_H_

#include <algorithm>

#include "../common/point.h"

enum State{NEW, OPEN, CLOSE, OBS};

struct ListNode {
    common::Point pos;
    ListNode* parent;
    double g;
    double h;
    double k;
    State tag;
    ListNode(common::Point& _pos, ListNode* _parent, double _g, State _tag=NEW) : pos(_pos), parent(_parent), g(_g), k(_g),tag(_tag) {};
    bool operator !=(ListNode*);
    bool operator ==(ListNode*);
};

bool ListNode::operator !=(ListNode* node) {
    if(pos != node->pos) {
        return true;
    }
    return false;
}

bool ListNode::operator ==(ListNode* node) {
    if(pos == node->pos) {
        return true;
    }
    return false;
}


class List {
public:
    ListNode* top();

    ListNode* pop();
    
    void insert(common::Point& pos, ListNode* parent, double g, State tag = OPEN);

    bool empty();

    void decreaseKey(int index, double new_g);

    int find(const common::Point& point);
    
    ListNode* operator[](int i);
private:
    //why not pri_queue? because the elements in it should be modifiable
    vector<ListNode*> pri_que_; //TODO(GCX): modify this to be unordered_set
    
};


ListNode* List::top() {
    ListNode* node_min = pri_que_[0];
    int k_min = pri_que_[0]->k;
    for(int i=0; i<pri_que_.size(); ++i) {
        int k_node = pri_que_[i]->k;
        if(pri_que_[i]->tag==OPEN && (k_node < k_min)) {
            k_min = k_node;
            node_min = pri_que_[i];
        }
    }
    return node_min;
}

ListNode* List::pop() {
    ListNode* node_min = nullptr;
    int k_min = INT_MAX;
    for(int i=0; i<pri_que_.size(); ++i) {
        int k_node = pri_que_[i]->k;
        if(pri_que_[i]->tag==OPEN && (k_node < k_min) ) {
            k_min = k_node;
            node_min = pri_que_[i];
        }
    }
    node_min->tag = CLOSE;
    return node_min;
}

void List::insert(common::Point& pos, ListNode* parent, double g, State tag) {
    ListNode* new_node = new ListNode(pos, parent, g, tag);
    pri_que_.emplace_back(new_node);
}

bool List::empty() {
    return pri_que_.size()==0;
}

// bool List::decreaseKey(int index, double new_g) {
//     if(pri_que_[index]->g > new_g) {
//         pri_que_[index]->g = new_g;        
//         pri_que_[index]->k = new_g + pri_que_[index]->h;    // update k. the h will be 0 when it runs dijkstra
//         return true;
//     }
//     return false;
// }

int List::find(const common::Point& point) {
    for(int i=0; i<pri_que_.size(); ++i) {
        if(pri_que_[i]->pos == point) {
            return i;
        }
    }
    return -1;
}

ListNode* List::operator[](int i) {
    return pri_que_[i];
}

#endif // !_PRI_QUEUE_H_