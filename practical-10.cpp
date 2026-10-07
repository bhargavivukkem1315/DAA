#include <iostream>
#include <algorithm>
using namespace std;

struct Edge
{
    int u, v, weight;
};

// Find which group the vertex belongs to
int findParent(int parent[], int x)
{
    while (parent[x] != x)
        x = parent[x];

    return x;
}

void kruskalMST(Edge edges[], int V, int E)
{
    // Sort edges by weight
    sort(edges, edges + E, [](Edge a, Edge b)
    {
        return a.weight < b.weight;
    });

    int parent[20];

    // Initially every vertex is separate
    for (int i = 0; i < V; i++)
        parent[i] = i;

    int total = 0;
    int count = 0;

    cout << "\nMinimum Spanning Tree:\n";
    cout << "Edge\tWeight\n";

    // Check edges one by one
    for (int i = 0; i < E; i++)
    {
        int u = edges[i].u;
        int v = edges[i].v;

        int parentU = findParent(parent, u);
        int parentV = findParent(parent, v);

        // If different groups, no cycle
        if (parentU != parentV)
        {
            cout << u << " - " << v
                 << "\t" << edges[i].weight << endl;

            total += edges[i].weight;
            count++;

            // Join the two groups
            parent[parentV] = parentU;
        }

        // MST needs V-1 edges
        if (count == V - 1)
            break;
    }

    cout << "\nMinimum Cost = " << total << endl;
}

int main()
{
    int V, E;
    Edge edges[50];

    cout << "Enter number of vertices: ";
    cin >> V;

    cout << "Enter number of edges: ";
    cin >> E;

    cout << "Enter edges (u v weight):\n";

    for (int i = 0; i < E; i++)
    {
        cin >> edges[i].u
            >> edges[i].v
            >> edges[i].weight;
    }

    kruskalMST(edges, V, E);

    return 0;
}