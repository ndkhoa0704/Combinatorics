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

int *GenerateGraph_no_loop(int size)
{
    int *graph = new int[size * size]{};
    int tmp;
    for (int num_of_edge, j, i = 0; i < size; ++i)
    {
        num_of_edge = rand() % (size - 1) + 1;
        for (int l = 0; l < num_of_edge; ++l)
        {
            j = rand() % size;
            if (!graph[i * size + j] && i != j)
            {
                tmp = rand() % 50 + 1;
                graph[i * size + j] = tmp;
                graph[j * size + i] = tmp;
            }
        }
    }
    return graph;
}

int *GenerateGraph_with_loop(int size)
{
    int *graph = new int[size * size]{};
    int tmp;
    for (int num_of_edge, j, i = 0; i < size; ++i)
    {
        num_of_edge = rand() % (size - 1) + 1;
        for (int l = 0; l < num_of_edge; ++l)
        {
            j = rand() % size;
            if (!graph[i * size + j])
            {
                tmp = rand() % 50 + 1;
                graph[i * size + j] = tmp;
                graph[j * size + i] = tmp;
            }
        }
    }
    return graph;
}

int *GenerateGraph_directional_with_loop(int size)
{
    int *graph = new int[size * size]{};
    for (int num_of_edge, j, i = 0; i < size; ++i)
    {
        num_of_edge = rand() % (size - 1) + 1;
        for (int l = 0; l < num_of_edge; ++l)
        {
            j = rand() % size;
            if (!graph[i * size + j])
                graph[i * size + j] = rand() % 50 + 1;
        }
    }
    return graph;
}

int *GenerateGraph_directional_no_loop(int size)
{
    int *graph = new int[size * size]{};
    for (int num_of_edge, j, i = 0; i < size; ++i)
    {
        num_of_edge = rand() % (size - 1) + 1;
        for (int l = 0; l < num_of_edge; ++l)
        {
            j = rand() % size;
            if (!graph[i * size + j] && i != j)
                graph[i * size + j] = rand() % 50 + 1;
        }
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
    if (argc != 4 || !(size = checkArg(argv[1])))
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
    int *graph = nullptr;

    // 1 no loop
    // 2 loop
    // 3 directional, no loop
    // 4 directional, loop
    switch (atoi(argv[3]))
    {
    case 1:
        graph = GenerateGraph_no_loop(size);
        break;
    case 2:
        graph = GenerateGraph_with_loop(size);
        break;
    case 3:
        graph = GenerateGraph_directional_no_loop(size);
        break;
    case 4:
        graph = GenerateGraph_directional_with_loop(size);
        break;
    default:
        cout << "Invalid argument" << endl;
        file.close();
        return -1;
    }
    save_graph(file, graph, size);
    delete[] graph;
    file.close();
}