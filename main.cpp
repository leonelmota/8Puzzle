#include <iostream>
#include <vector>
#include <chrono>
#include "solver.h"
#include "node.h"

#define PROBLEM_SIZE 3

using namespace std;
using namespace std::chrono;

void print_resp(vector<Node> resp);

int main(int argc, char *argv[])
{

    char alg = argv[1][0];
    vector<int> initial_config(PROBLEM_SIZE * PROBLEM_SIZE);
    bool print = false;

    for (int i = 0; i < initial_config.size(); i++)
    {
        initial_config[i] = atoi(argv[i + 2]);
    }

    if (argc == 12)
    {
        print = string(argv[11]) == "PRINT";
    }
    Solver s(initial_config, PROBLEM_SIZE);
    	 	
	
	// time_point<high_resolution_clock> start_point, end_point; // creating time points
	// start_point = high_resolution_clock::now(); // storing the starting time point in start 
	
    vector<Node> resp = s.solve(alg);
	 
	// end_point = high_resolution_clock::now(); //storing the ending time in end 
	// auto start = time_point_cast<microseconds>(start_point).time_since_epoch().count(); 
	// // casting the time point to microseconds and measuring the time since time epoch
	// auto end = time_point_cast<microseconds>(end_point).time_since_epoch().count();
	
	cout << int(resp.size()) -1  << endl;
    // cout << endl << "Response size " << resp.size() - 1 << endl;
    // cout << "Nodes expanded " << s.get_nodes_expanded() << endl;
    // cout<<"Time taken = "<<(end-start)<<" microseconds"<<endl;
    if (print and resp.size() > 0)
    {
        print_resp(resp);
    }

    return 0;
}

void print_resp(vector<Node> resp)
{
    for (auto n : resp){

        for (int i = 0; i < n.config.size(); i += PROBLEM_SIZE)
        {
            for (int j = i; j < i + PROBLEM_SIZE; j++)
            {
                if (n.config[j] == 0)
                    cout << "  ";
                else
                    cout << n.config[j] << ' ';
            }
            cout << endl;
        }
        cout << endl;
    }
}