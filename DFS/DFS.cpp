#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>

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

void save_tree(ofstream &file, const vector<int> &path)
{
    int size = path.size();
    int *arr = new int[size * size]{0};
    for (int i = 1; i < size; ++i)
    {
        arr[path[i] + path[i - 1] * size] = 1;
        arr[path[i - 1] + path[i] * size] = 1;
    }
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
            file << arr[j + size * i] << " ";
        file << endl;
    }
    delete[] arr;
}

// base case count reach the graph size (number of vertices)
// index the points that need to be check

bool driver_DFS(const vector<vector<int>> &graph, vector<int> &path, int *visited, int index)
{
    if (visited[index] == 1)
        return false;
    if (path.size() == graph.size())
        return true;
    visited[index] = 1;
    // iterate through vertices that "index" is connecting to
    for (int i = 0; i < graph[index].size(); ++i)
    {
        path.emplace_back(graph[index][i]);
        if (driver_DFS(graph, path, visited, graph[index][i]))
            return true;
        else
            path.pop_back();
    }
    visited[index] = 0;
    return false;
}

vector<int> DFS(vector<vector<int>> &graph)
{
    int *visited = new int[graph.size()]{};
    vector<int> path;
    for (int i = 0; i < graph.size(); ++i)
    {
        path.emplace_back(i);
        if (driver_DFS(graph, path, visited, i))
            return path;
        else
            path.pop_back();
    }
    delete[] visited;
    return path;
}

void save_path(ofstream &file, const vector<int> &path)
{
    for (int i = 0; i < path.size(); ++i)
        file << i << ": " << path[i] << endl;
}

int main()
{
    ifstream fin("graph");
    vector<vector<int>> graph = read_graph(fin);
    vector<int> path = DFS(graph);
    fin.close();
    ofstream fout("result");
    save_tree(fout, path);
    fout.close();
    fout.open("path");
    save_path(fout, path);
    fout.close();
}