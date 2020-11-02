#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <iomanip>

using namespace std;

int load_graph(ifstream &file, int *&graph)
{
    int tmp;
    if (graph)
        delete[] graph;
    file >> tmp;
    int size = tmp * tmp;
    graph = new int[size];
    for (int i = 0; i < size; ++i)
        file >> graph[i];
    return tmp;
}

// Choose the vertex
// Iterates to find the minimum edge length
// Choose the vertex that the minimum-length edge links to
// Repeat step 1

int *Prim(int *graph, int size)
{
    int *visited = new int[size]{};
    int *tree = new int[size * size]{};
    int i = rand() % size;
    int count = 0;
    int min, tmp_index;
    while (count < size - 1)
    {
        min = INT32_MAX;
        for (int j = 0; j < size; ++j)
        {
            if (i == j)
                continue;
            if (graph[size * j + i] != 0 && graph[size * j + i] < min && visited[j] != 1)
            {
                tmp_index = j;
                min = graph[size * j + i];
            }
        }
        ++count;
        tree[size * i + tmp_index] = min;
        tree[size * tmp_index + i] = min;
        visited[i] = 1;
        i = tmp_index;
    }
    delete[] visited;
    return tree;
}

void save_tree(ofstream &file, int *tree, int size)
{
    {
        file << size << endl;
        int i;
        for (i = 0; i < size - 1; ++i)
        {
            for (int j = 0; j < size; ++j)
                file << left << setw(3) << tree[size * j + i];
            file << endl;
        }
        for (int j = 0; j < size; ++j)
            file << left << setw(3) << tree[size * j + i];
    }
}

int main()
{
    srand(time(0));
    ifstream fin("graph");
    if (!fin.is_open())
        return -1;
    int *graph = nullptr;
    int size = load_graph(fin, graph);
    fin.close();
    int *tree = Prim(graph, size);
    ofstream fout("result");
    save_tree(fout, tree, size);
    delete[] graph;
    delete[] tree;
}