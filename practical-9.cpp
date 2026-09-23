#include <iostream>
#include <climits>
using namespace std;

void primMST(int graph[][20], int V)
{
    int parent[20];       // Stores MST
    int key[20];          // Minimum edge weight
    bool inMST[20];       // Checks selected vertices

    // Initialize
    for (int i = 0; i < V; i++)
    {
        key[i] = INT_MAX;
        inMST[i] = false;
        parent[i] = -1;
    }

    // Start from vertex 0
    key[0] = 0;

    // MST contains V vertices
    for (int count = 0; count < V; count++)
    {
        // Find vertex with minimum key
        int u = -1;

        for (int v = 0; v < V; v++)
        {
            if (!inMST[v] && (u == -1 || key[v] < key[u]))
                u = v;
        }

        // Add selected vertex to MST
        inMST[u] = true;

        // Update adjacent vertices
        for (int v = 0; v < V; v++)
        {
            if (graph[u][v] != 0 &&
                !inMST[v] &&
                graph[u][v] < key[v])
            {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // Display MST
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