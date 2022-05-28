#ifndef INCLUDE_SOLVER_H
#define INCLUDE_SOLVER_H

#include <vector>
#include "node.h"

using namespace std;

class Solver{

public:
    Solver(vector<int> initial_config, int size);
    vector<Node*> solve(char alg);

private:
    vector<int> initial_config;
    int size;
    int nodes_expanded = 0;

    vector<Node*> bfs();
    vector<Node*> ids();
    vector<Node*> ucs();
    vector<Node*> a_star();
    vector<Node*> gbfs();
    vector<Node*> hill_clibing();

};

#endif