#include <iostream>
#include <fstream>
#include <map>

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

int *Prim(int *graph, int size)
{
    int *tree = new int[size]{};
    int min, min_i;
    for (int i = 0; i < size; ++i)
    {
        min = INT16_MAX;
        min_i = -1;
        for (int j = 0; j < size; ++j)
        {
            if (graph[size * i + j] != 0 && graph[size * i + j] < min)
            {
                min = graph[size * i + j];
                min_i = j;
            }
        }
        if (min_i != -1)
            tree[i] = min_i;
    }
    return tree;
}
void save_tree(ofstream &file, int *tree, int size)
{
    for (int i = 0; i < size; ++i)
        file << i << ": " << tree[i] << endl;
}

int main()
{
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