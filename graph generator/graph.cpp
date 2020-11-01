#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string.h>
#include <fstream>
#include <iomanip>

using namespace std;

int checkArg(char *arg)
{
    stringstream sstr;
    sstr << arg;
    int size;
    sstr >> size;
    sstr << "";
    sstr.clear();
    sstr << size;
    string ch;
    sstr >> ch;
    if (strcmp(ch.c_str(), arg))
        return 0;
    return size;
}

int *GenerateGraph(int size)
{
    int *graph = new int[size * size]{};
    int num_of_edges = rand() % size * size + size;
    int rows, cols;
    for (int i = 0; i < num_of_edges; ++i)
    {
        rows = rand() % size;
        cols = rand() % size;
        if (rows == cols)
        {
            --i;
            continue;
        }
        if (!graph[rows * size + cols])
            graph[rows * size + cols] = rand() % 50 + 1;
    }
    return graph;
}

void save_graph(ofstream &file, int *graph, int size)
{
    file << size << endl;
    int i;
    for (i = 0; i < size - 1; ++i)
    {
        for (int j = 0; j < size; ++j)
            file << left << setw(3) << graph[size * j + i];
        file << endl;
    }
    for (int j = 0; j < size; ++j)
        file << left << setw(3) << graph[size * j + i];
}

int main(int argc, char *argv[])
{
    int size;
    if (argc != 3 || !(size = checkArg(argv[1])))
    {
        cout << "Invalid argument" << endl;
        return -1;
    }
    ofstream file(argv[2]);
    if (!file.is_open())
    {
        cout << "Invalid argument" << endl;
        file.close();
        return -1;
    }
    srand(time(NULL));
    int *graph = GenerateGraph(size);
    save_graph(file, graph, size);
    delete[] graph;
    file.close();
}