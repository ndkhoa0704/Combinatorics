#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include <exception>

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

bool Prim(int *graph, int *&tree, int size)
{
    int *visited = new int[size]{};
    int i = rand() % size;
    int count = 1;
    int min, j, k, min_i1, min_i2;
    while (count < size)
    {
        min = INT16_MAX;
        min_i1 = -1;
        min_i2 = -1;
        for (j = 0; j < size; ++j)
        {
            if (i != j && !visited[j] && graph[size * i + j] != 0 && graph[size * i + j] < min)
            {
                min = graph[size * i + j];
                min_i1 = j;
            }
        }
        for (k = 0; k < size; ++k)
        {
            if (visited[k])
            {
                if (k != min_i1 && graph[size * k + min_i1] != 0 && graph[size * k + min_i1] < min)
                {
                    min = graph[size * k + min_i1];
                    min_i2 = k;
                }
            }
        }
        if (min_i1 == -1)
            return false;
        visited[i] = 1;
        if (min_i2 != -1)
        {
            tree[size * min_i1 + min_i2] = min;
            tree[size * min_i2 + min_i1] = min;
        }
        else
        {
            tree[size * i + min_i1] = min;
            tree[size * min_i1 + i] = min;
            i = min_i1;
        }
        ++count;
    }
    delete[] visited;
    return true;
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
    int *tree = new int[size * size]{};
    if (!Prim(graph, tree, size))
        return -1;
    ofstream fout;
    fout.open("result", ios::out);
    save_tree(fout, tree, size);
    fout.close();
    delete[] graph;
    delete[] tree;
}