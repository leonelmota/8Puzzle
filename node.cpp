#include "node.h"
#include <algorithm>
#include <iostream>

using namespace std;

Node::Node(vector<int> _config, Node*_parent){
    this->config = _config;
    this->parent = _parent;
    is_root = _parent == NULL;
    if (is_root)
        depth = 0;
    else
        depth = this->parent->depth + 1;
}

vector<Node *> Node::find_children()
{
    vector<int> move = {1, -1, problem_size, -problem_size};
    vector<Node*> resp;
    int idx0 = find_idx0();

    for (auto d : move)
    {
        if (inside(idx0, d)){
            vector<int> new_config = config;
            swap(new_config[idx0], new_config[idx0 + d]);

            Node *new_node = new Node(new_config, this);
            resp.push_back(new_node);
        }
    }
    return resp;
}

bool Node::is_final(){
    for (int i = 1; i < config.size(); i++)
    {
        if (config[i] != 0 and config[i] != i + 1)
            return false;
    }
    return true;
}

int Node::find_idx0(){
    auto itr = find(config.begin(), config.end(), 0);
    return distance(config.begin(), itr);
}

vector<Node> Node::get_parents()
{
    vector<Node> resp = {*this};
    Node n = *this;
    while (n.depth > 0)
    {
        n = *(n.parent);
        resp.push_back(n);
    }
    reverse(resp.begin(), resp.end());
    return resp;
}

int Node::inside(int i, int d){
    if (0 <= i+d and i+d < problem_size*problem_size){
        if (abs(d) == 1){
            return (i/problem_size == (i+d)/problem_size);
        } 
        return true;
    }
    return false;
}

vector<Node *> Node::get_children()
{
    //return find_children();
    if (this->children.size() > 0)
        return this->children;
    return this->children = find_children();
}

Node* Node::get_parent(){
    return this->parent;
}

int Node::heuristic_out_of_place()
{
    int count = 0;
    for (int i = 0; i < config.size(); i++)
    {
        if (config[i] != 0 and config[i] != i + 1)
            count++;
    }
    return count;
}

int Node::heuristic_distance()
{
    int count = 0;
    for (int i = 0; i < config.size(); i++)
    {
        //cout << i << ' ' << config[i] << endl;
        if (config[i] != 0)
        {
            count += abs(((config[i] - 1) / problem_size) - i / problem_size);
            count += abs(((config[i] - 1) % problem_size) - i % problem_size);
        }
        //cout << count << endl;
    }
    return count;
}