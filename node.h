#ifndef INCLUDE_NODE_H
#define INCLUDE_NODE_H

#include <vector>

using namespace std;

class Node{
public:
    vector<int> config;
    
    Node(vector<int> _config, Node *_parent);
    //~Node();
    Node *get_parent();
    vector<Node*> get_children();
    bool is_final();
    vector<Node> get_parents();
    int depth;
    Node *parent;
    int problem_size = 3;
    friend bool operator < (const Node& n1, const Node& n2) {return n1.config < n2.config;}
    // returns the number of tiles out of place
    int heuristic_out_of_place();
    // returns the distance of the tile from its goal position
    int heuristic_distance();

private:
    vector<Node*> children;

    int is_root;

    int find_idx0();
    vector<Node*> find_children();
    int inside(int i, int d);
};

#endif

