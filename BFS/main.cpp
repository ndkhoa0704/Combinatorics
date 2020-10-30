#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> read_graph(ifstream &file)
{
    int size, tmp;
    file >> size;
    vector<vector<int>> graph;
    int i = 0, j = 0;
    for (int i = 0; i < size; ++i)
    {
        vector<int> row;
        for (int j = 0; j < size; ++j)
        {
            file >> tmp;
            if (tmp == 1)
                row.emplace_back(j);
        }
        graph.emplace_back(row);
    }
    return graph;
}

/*************
* Create a tree that use same pattern as the graph
* to_be_check will hold points to be checked
* visited preresents number of points that have been checked
*************/

vector<vector<int>> BFS(const vector<vector<int>> &graph)
{
    int count = 0;
    int *visited = new int[graph.size()]{0};
    queue<int> to_be_check;
    vector<vector<int>> tree(graph.size());
    // Random first point
    int origin = rand() % graph.size();
    to_be_check.push(origin);
    visited[origin] = 1;
    // Check until the queue empty
    while (!to_be_check.empty())
    {
        vector<int> points;
        int t = to_be_check.front();
        to_be_check.pop();
        for (auto &i : graph[t])
        {
            if (visited[i] == 1)
                continue;
            visited[i] = 1;
            to_be_check.push(i);
            points.emplace_back(i);
        }
        tree[t] = points;
    }
    delete[] visited;
    tree.shrink_to_fit();
    return tree;
}

/*******
 * Write data to file
 * Adjacency matrix
*******/

void save_tree(ofstream &file, const vector<vector<int>> &tree)
{
    int size = tree.size();
    int *arr = new int[size * size]{0};
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < tree[i].size(); ++j)
            arr[tree[i][j] + size * i] = 1;
    }
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
            file << arr[j + size * i] << " ";
        file << endl;
    }
    delete[] arr;
}

int main()
{
    srand(time(NULL));
    ifstream file1("graph");
    if (!file1.is_open())
        return -1;
    int size;
    vector<vector<int>> graph = read_graph(file1);
    graph = BFS(graph);
    file1.close();
    ofstream file2("result");
    save_tree(file2, graph);
    file2.close();
    return 0;
}