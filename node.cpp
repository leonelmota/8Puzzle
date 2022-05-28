#include "node.h"
#include <algorithm>
#include <iostream>

using namespace std;

Node::Node(vector<int> _config, Node*_parent){
    this->config = _config;
    this->parent = _parent;
    //is_root = _parent == NULL;
}

vector<Node*> Node::find_children(){
    cout << "inside find children" << endl;
    vector<int> move = {1, -1, problem_size, -problem_size};
    vector<Node*> resp;
    int idx0 = find_idx0();
    for (auto d : move){
        cout << d << endl;
        if (inside(idx0, d)){
            vector<int>new_config = config; //(config.begin(), config.end());

            swap(new_config[idx0], new_config[idx0 + d]);

            cout << "antes ";
            Node *new_node = new Node(new_config, this);
            cout << "depois ";
            resp.push_back(new_node);
            //for (auto i : new_config) cout << i << ' '; 
            //cout << endl;
        }
    }
    return resp;
}

bool Node::is_final(){
    vector<int> config_copy = config;
    config_copy.erase(find(config_copy.begin(), config_copy.end(), 0));
    for (int i=1; i<config_copy.size(); i++){
        if (config_copy[i] != config_copy[i-1]+1) return false;
    }
    return true;
}

int Node::find_idx0(){
    auto itr = find(config.begin(), config.end(), 0);
    return distance(config.begin(), itr);
}

vector<Node*> Node::get_parents(){
    vector<Node*> resp = {this};
    Node* n = this;
    cout << "init get resp" << endl;
    while(n->parent != NULL){
        n = n->parent;
        resp.push_back(n);
    }
    reverse(resp.begin(), resp.end());
    cout << "resp size" << resp.size() << endl;
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

// void Node::swap(vector<int> x, int a, int b){
//     int temp = x[a];
//     x[a] = x[b];
//     x[b] = temp; 
// }

vector<Node*> Node::get_children(){

    cout << "inside get children" << endl;
    if (this->children.size() > 0)
        return this->children;
    return this->children = find_children();
}

Node* Node::get_parent(){
    return this->parent;
}