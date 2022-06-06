#ifndef INCLUDE_SOLVER_H
#define INCLUDE_SOLVER_H

#include <vector>
#include <set>
#include "node.h"

using namespace std;

class Solver{

public:
    Solver(vector<int> initial_config, int size);
    ~Solver();
    vector<Node> solve(char alg);
    int get_nodes_expanded() { return nodes_expanded; }

private:
    vector<int> initial_config;
    int size;
    int nodes_expanded = 0;
    vector<Node> resp;
    vector<Node *> all_nodes;

    vector<Node> bfs();
    vector<Node> ids();
    vector<Node> ucs();
    vector<Node> a_star();
    vector<Node> gbfs();
    vector<Node> hill_climbing();

    bool dfs_limited(Node *n, int limit, set<Node> &parents);
};

#endif