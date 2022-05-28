#include <iostream>
#include <vector>
#include "solver.h"
#include "node.h"

#define PROBLEM_SIZE 3

using namespace std;


void print_resp(vector<Node*> resp);

int main(){
    char alg;
    vector<int> initial_config(9);
    bool print;
    string print_str;

    cin >> alg;
    for (auto & c : initial_config) cin >> c;
    cin >> print_str;
    print = print_str == "PRINT";

    Solver s(initial_config, PROBLEM_SIZE);

    vector<Node*> resp = s.solve(alg);

    cout << resp.size() << endl;
    if (print){
        print_resp(resp);
    }

    return 0;
}

void print_resp(vector<Node*> resp){
    for (auto n : resp){
        for (int i=0; i<n->config.size(); i++){
            cout << n->config[i] << ' ';
        }cout << endl;
    }
}