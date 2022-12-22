#include <iostream>
#include <vector>
#include <algorithm>

typedef struct
{
    int source;
    int destination;
    int weight;
} edge_t;

typedef struct
{
    int parent;
    int rank;
} node_t;

std::vector<edge_t> edge_list;
std::vector<node_t> nodes;

int find_set(int x)
{
    if (x != nodes.at(x).parent)
    {
        nodes.at(x).parent = find_set(nodes.at(x).parent);
    }

    return nodes.at(x).parent;
}

void union_set(int x, int y)
{
    x = find_set(x);
    y = find_set(y);

    if (nodes.at(x).rank > nodes.at(y).rank)
    {
        nodes.at(y).parent = x;
    }
    else
    {
        nodes.at(x).parent = y;

        if (nodes.at(x).rank == nodes.at(y).rank)
        {
            nodes.at(y).rank++;
        }
    }
}

int kruskal(int vertices)
{
    int result = 0;

    for (int i = 0; i < vertices; i++)
    {
        node_t new_subset = {i, 0};
        nodes.push_back(new_subset);
    }

    std::sort(edge_list.begin(), edge_list.end(), [](const edge_t &a, const edge_t &b)
              { return a.weight > b.weight; });

    for (auto const &edge : edge_list)
    {
        if (find_set(edge.source) != find_set(edge.destination))
        {
            union_set(edge.source, edge.destination);
            result += edge.weight;
        }
    }

    return result;
}

int main()
{
    int vertices, edges;
    std::cin >> vertices >> edges;

    for (int i = 0; i < edges; i++)
    {
        edge_t new_edge;
        std::cin >> new_edge.source >> new_edge.destination >> new_edge.weight;
        new_edge.source--;
        new_edge.destination--;
        edge_list.push_back(new_edge);
    }

    std::cout << kruskal(vertices) << std::endl;

    return 0;
}
