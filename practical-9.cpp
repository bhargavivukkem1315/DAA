/*
 * Program : Minimum Spanning Tree (MST) using Prim's Algorithm
 * Purpose : Finds the MST of a connected, undirected weighted graph represented 
 *           as an adjacency matrix by greedily growing the tree from vertex 0.
 *           Time Complexity: O(V^2) | Space Complexity: O(V)
 */

#include <iostream>
#include <climits> // For INT_MAX
using namespace std;

// Builds and prints the MST starting from vertex 0 | Time: O(V^2) | Space: O(V)
void primMST(int graph[][20], int V)
{
    int parent[20]; // Stores parent of each vertex in the constructed MST
    int key[20];    // Stores minimum edge weight connecting each vertex to MST
    bool inMST[20]; // Tracks vertices already included in the MST

    // Step 1: Initialize all keys to infinity and mark all vertices unvisited
    for (int i = 0; i < V; i++)
    {
        key[i] = INT_MAX;
        inMST[i] = false;
        parent[i] = -1;
    }

    // Start MST construction from vertex 0
    key[0] = 0;

    // Step 2: Include all V vertices into the MST one by one
    for (int count = 0; count < V; count++)
    {
        // Pick unvisited vertex u with the minimum key value
        int u = -1;
        for (int v = 0; v < V; v++)
        {
            if (!inMST[v] && (u == -1 || key[v] < key[u]))
                u = v;
        }

        inMST[u] = true; // Add selected vertex u to MST

        // Step 3: Update key values and parent pointers of adjacent vertices
        for (int v = 0; v < V; v++)
        {
            // graph[u][v] != 0 ensures an edge exists between u and v
            if (graph[u][v] != 0 &&
                !inMST[v] &&
                graph[u][v] < key[v])
            {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // Display MST edges and calculate total minimum weight (start from i = 1 since 0 is root)
    int totalWeight = 0;

    cout << "\nMinimum Spanning Tree:\n";
    cout << "Edge\tWeight\n";

    for (int i = 1; i < V; i++)
    {
        cout << parent[i] << " - " << i
             << "\t" << graph[i][parent[i]] << endl;

        totalWeight += graph[i][parent[i]];
    }

    cout << "\nMinimum Cost of MST = " << totalWeight << endl;
}

int main()
{
    int V;
    int graph[20][20];

    cout << "Enter number of vertices: ";
    cin >> V;

    // Read weighted adjacency matrix (0 indicates no direct edge)
    cout << "Enter adjacency matrix:\n";
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            cin >> graph[i][j];
        }
    }

    primMST(graph, V);

    return 0;
}
