#ifndef INCLUDE_NODE_H
#define INCLUDE_NODE_H

#include <vector>

using namespace std;

class Node{
public:
    vector<int> config;
    
    Node(vector<int> _config, Node *_parent);
    Node *get_parent();
    vector<Node*> get_children();
    bool is_final();
    vector<Node*> get_parents();

    friend bool operator < (const Node& n1, const Node& n2) {return n1.config < n2.config;}
    

private:
    vector<Node*> children;
    Node *parent;
    int is_root;
    int problem_size = 3;

    int find_idx0();
    vector<Node*> find_children();
    int inside(int i, int d);
    //void swap(vector<int>x, int a, int b);
};

#endif

