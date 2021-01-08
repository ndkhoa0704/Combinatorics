#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

bool LoadGraph(vector<vector<int>> &graph, const char *path)
{
    ifstream file(path);
    if (!file.is_open())
        return false;
    int n;
    file >> n;
    int tmp;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            vector<int> vertex;
            file >> tmp;
            vertex.emplace_back(tmp);
        }
    }
}

vector<int> Dijkstra(const vector<vector<bool>> &graph, int starting_node)
{
    int size = graph.size();
    vector<int> weight(graph.size(), INT64_MAX);
    vector<int> path;
    path.emplace_back(starting_node);
    int cur = starting_node;
    while (path.size() != size)
    {
        for (int i = 0; i < size; ++i)
        {
            if (graph[cur][i] != 0)
            {
                if (weight[])
            }
        }
    }
}

int main()
{
}