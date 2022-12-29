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

static std::vector<node_t> nodes;
static std::vector<edge_t> edge_list;

int find_set(int x)
{
    if (x != nodes[x].parent)
    {
        nodes[x].parent = find_set(nodes[x].parent);
    }

    return nodes[x].parent;
}

void union_set(int x, int y)
{
    x = find_set(x);
    y = find_set(y);

    if (nodes[x].rank > nodes[y].rank)
    {
        nodes[y].parent = x;
    }
    else
    {
        nodes[x].parent = y;

        if (nodes[x].rank == nodes[y].rank)
        {
            nodes[y].rank++;
        }
    }
}

int kruskal(int vertices)
{
    int result = 0, count = 0;

    node_t new_subset;
    for (int i = 0; i < vertices; i++)
    {
        new_subset.parent = i;
        new_subset.rank = 0;
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
            if (++count == vertices - 1)
                return result;
        }
    }

    return result;
}

int main()
{
    int vertices, edges;
    scanf("%d %d", &vertices, &edges);

    nodes.reserve(vertices);
    edge_list.reserve(edges);

    edge_t new_edge;
    for (int i = 0; i < edges; i++)
    {
        scanf("%d %d %d", &new_edge.source, &new_edge.destination, &new_edge.weight);
        new_edge.source--;
        new_edge.destination--;
        edge_list.push_back(new_edge);
    }

    std::cout << kruskal(vertices) << std::endl;

    return 0;
}
