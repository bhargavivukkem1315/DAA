/*
 * Program : Minimum Spanning Tree (MST) using Kruskal's Algorithm
 * Purpose : Finds the MST of a connected, undirected weighted graph using 
 *           Greedy approach and Disjoint Set (Union-Find) cycle detection.
 *           Time Complexity: O(E log E) | Space Complexity: O(V + E)
 */

#include <iostream>
#include <algorithm> // For std::sort
using namespace std;

// Represents a weighted undirected edge between vertices u and v
struct Edge
{
    int u, v, weight;
};

// Disjoint Set (Find): Returns the root parent/component of vertex x
int findParent(int parent[], int x)
{
    while (parent[x] != x)
        x = parent[x];

    return x;
}

// Builds MST by greedily selecting smallest edges that do not form a cycle
void kruskalMST(Edge edges[], int V, int E)
{
    // Step 1: Sort all edges in ascending order of their weights
    sort(edges, edges + E, [](Edge a, Edge b)
    {
        return a.weight < b.weight;
    });

    int parent[20];

    // Step 2: Initialize Disjoint Sets (each vertex is its own parent)
    for (int i = 0; i < V; i++)
        parent[i] = i;

    int total = 0; // Stores total weight of MST
    int count = 0; // Tracks number of edges added to MST

    cout << "\nMinimum Spanning Tree:\n";
    cout << "Edge\tWeight\n";

    // Step 3: Pick smallest edges one by one and check for cycles
    for (int i = 0; i < E; i++)
    {
        int u = edges[i].u;
        int v = edges[i].v;

        int parentU = findParent(parent, u);
        int parentV = findParent(parent, v);

        // Include edge only if u and v belong to different components (no cycle)
        if (parentU != parentV)
        {
            cout << u << " - " << v
                 << "\t" << edges[i].weight << endl;

            total += edges[i].weight;
            count++;

            // Union: Merge the two components into a single set
            parent[parentV] = parentU;
        }

        // Stop early once V - 1 edges are included in the MST
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

    // Read graph edges (0-indexed vertices expected: 0 to V-1)
    for (int i = 0; i < E; i++)
    {
        cin >> edges[i].u
            >> edges[i].v
            >> edges[i].weight;
    }

    kruskalMST(edges, V, E);

    return 0;
}
