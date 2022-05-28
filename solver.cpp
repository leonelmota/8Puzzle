#include "solver.h"
#include "node.h"
#include <vector>
#include <algorithm>
#include <stack>
#include <set>
#include <iostream>

using namespace std;

Solver::Solver(vector<int> initial_config, int size){
    this->initial_config = initial_config;
    this->size = size;
}

vector<Node*> Solver::solve(char alg){
    switch (alg){
        case 'B':
            return bfs();
            break;
        case 'I':
            return ids();
            break;
        case 'U':
            return ucs();
            break;
        case 'A':
            return a_star();
            break;
        case 'G':
            return gbfs();
            break;
        case 'H':
            return hill_clibing();
            break;
    }
}

vector<Node*> Solver::bfs(){
    set<Node> visited;
    nodes_expanded = 0;
    stack<Node*> st;
    Node *initial_node = new Node(initial_config, NULL);
    st.push(initial_node);

    while(!st.empty()){
        cout << "#nodes: "<< nodes_expanded << endl;
        nodes_expanded++;
        Node n = *st.top();
        st.pop();
        for (auto c : n.get_children()){
            if (c->is_final()){ 
                cout << "estado final" << endl;
                //for (auto i : c->config) cout << i << ' '; cout << endl;
                return c->get_parents(); 
            }
            if (visited.find(*c) == visited.end()){
                visited.insert(*c);
                st.push(c);
            }    
        } 
    }
}


vector<Node*> Solver::ids(){
    
}

vector<Node*> Solver::ucs(){
    
}

vector<Node*> Solver::a_star(){
    
}


vector<Node*> Solver::gbfs(){
    
}


vector<Node*> Solver::hill_clibing(){
    
}