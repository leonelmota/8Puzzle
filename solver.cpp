#include "solver.h"
#include "node.h"
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <set>
#include <iostream>

#define MAX_DEPTH 100
#define PROBLEM_SIZE 9
const int INF = 0x3f3f3f3f;

using namespace std;

Solver::Solver(vector<int> initial_config, int size){
    this->initial_config = initial_config;
    this->size = size;
}

Solver::~Solver()
{
    for (auto node : all_nodes)
    {
        delete node;
    }
}

vector<Node> Solver::solve(char alg)
{
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
            return hill_climbing();
            break;
        default:
            return vector<Node>();
            break;
        }
}

vector<Node> Solver::bfs()
{
    set<Node> created;
    nodes_expanded = 0;
    queue<Node *> q;
    Node *initial_node = new Node(initial_config, NULL);
    q.push(initial_node);
    created.insert(*initial_node);
    all_nodes.push_back(initial_node);

    while (!q.empty())
    {
        nodes_expanded++;
        Node *n = q.front();
        q.pop();
        if (n->is_final())
            return resp = n->get_parents();

        for (auto c : n->get_children())
        {
            all_nodes.push_back(c);
            if (created.find(*c) == created.end())
            {
                created.insert(*c);
                q.push(c);
            }
        }
    }
    return vector<Node>();
}

bool Solver::dfs_limited(Node *n, int limit, set<Node> &parents)
{
    nodes_expanded++;
    if (n->depth > limit)
        return false;

    if (n->is_final())
    {
        resp = n->get_parents();
        return true;
    }

    parents.insert(*n);

    for (auto c : n->get_children())
        all_nodes.push_back(c);
    for (auto c : n->get_children())
    {
        if (parents.find(*c) == parents.end() and dfs_limited(c, limit, parents))
        {
            return true;
        }
    }
    parents.erase(*n);
    return false;
}

vector<Node> Solver::ids()
{
    nodes_expanded = 0;
    for (int d = 0; d < MAX_DEPTH; d++)
    {
        //cout << "depth " << d << endl;
        //cout << "nodes expanded " << nodes_expanded << endl;
        Node *initial_node = new Node(initial_config, NULL);
        all_nodes.push_back(initial_node);
        set<Node> parents;
        if (dfs_limited(initial_node, d, parents))
        {
            return resp;
        }
    }
    //cout << "Solution not found at max depth of " << MAX_DEPTH << endl;
    return {};
}

vector<Node> Solver::ucs()
{
    set<Node> visited;
    nodes_expanded = 0;
    priority_queue<pair<int, Node *>> q;
    Node *initial_node = new Node(initial_config, NULL);
    q.push({-initial_node->depth, initial_node});
    all_nodes.push_back(initial_node);

    while (!q.empty())
    {
        Node *n = q.top().second;
        q.pop();
        if (visited.find(*n) != visited.end())
            continue;
        nodes_expanded++;
        visited.insert(*n);

        if (n->is_final())
            return resp = n->get_parents();

        for (auto c : n->get_children())
        {
            all_nodes.push_back(c);
            q.push({-c->depth, c});
        }
    }
    return vector<Node>();
}

vector<Node> Solver::a_star()
{
    set<Node> created;
    nodes_expanded = 0;
    priority_queue<pair<int, Node *>> q;
    Node *initial_node = new Node(initial_config, NULL);
    q.push({-initial_node->depth, initial_node});
    created.insert(*initial_node);
    all_nodes.push_back(initial_node);

    while (!q.empty())
    {
        nodes_expanded++;
        Node *n = q.top().second;
        q.pop();
        if (n->is_final())
            return resp = n->get_parents();

        for (auto c : n->get_children())
        {
            all_nodes.push_back(c);

            if (created.find(*c) == created.end())
            {
                created.insert(*c);
                q.push({-(c->depth + c->heuristic_out_of_place()), c});
            }
        }
    }
    return vector<Node>();
}

vector<Node> Solver::gbfs()
{
    set<Node> created;
    nodes_expanded = 0;
    priority_queue<pair<int, Node *>> q;
    Node *initial_node = new Node(initial_config, NULL);
    q.push({-initial_node->depth, initial_node});
    created.insert(*initial_node);
    all_nodes.push_back(initial_node);

    while (!q.empty())
    {
        nodes_expanded++;
        Node *n = q.top().second;
        q.pop();
        if (n->is_final())
            return resp = n->get_parents();
        

        for (auto c : n->get_children())
        {
            all_nodes.push_back(c);

            if (created.find(*c) == created.end())
            {
                created.insert(*c);
                q.push({-c->heuristic_out_of_place(), c});
            }
        }
    }
    return resp = {};
}
vector<Node> Solver::hill_climbing()
{
    nodes_expanded = 0;
    int MAX_LATERAL_MOVES = INF;
    int counter_lateral_moves = 0;
    set<Node> created;

    Node *current_node = new Node(initial_config, NULL);
    all_nodes.push_back(current_node);
    created.insert(*current_node);

    while (true)
    {
        nodes_expanded++;
        int best_child_value = INF;
        Node *best_child;
        bool child_found = false;
        if (current_node->is_final())
            return resp = current_node->get_parents();
        
        for (auto child : current_node->get_children())
        {
            if (child->heuristic_distance() <= best_child_value and created.find(*child) == created.end())
            {
                best_child_value = child->heuristic_distance();
                best_child = child;
                child_found = true;
            }
            created.insert(*child);
            all_nodes.push_back(child);
        }
        if (child_found and current_node->heuristic_distance() > best_child_value)
        {
            counter_lateral_moves = 0;
            current_node = best_child;
        }
        else if (child_found and current_node->heuristic_distance() == best_child_value and counter_lateral_moves < MAX_LATERAL_MOVES)
        {
            counter_lateral_moves++;
            current_node = best_child;
        }
        else
        {
            //cout << "Hill Climbing found local maximum, unable to find global maximum" << endl;
            break;
        }
    }
    return resp = {};
}