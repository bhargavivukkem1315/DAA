/*
 * Program : All-Pairs Shortest Path using Floyd-Warshall Algorithm
 * Purpose : Finds shortest distances between every pair of vertices in a 
 *           weighted directed graph using Dynamic Programming.
 *           Time Complexity: O(V^3) | Space Complexity: O(V^2)
 */

#include <iostream>
using namespace std;

int main()
{
    const int n = 4;        // Number of vertices in the graph
    const int INF = 99999;  // Represents infinity (no direct edge)

    // Initial adjacency matrix (A0) representing direct edge weights
    int dist[n][n] = {
        {0, 2, INF, 3},
        {1, 0, 2, INF},
        {INF, INF, 0, INF},
        {4, INF, 3, 0}
    };

    // Display Initial Matrix A0
    cout << "Initial Matrix A0:\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (dist[i][j] == INF)
                cout << "INF\t";
            else
                cout << dist[i][j] << "\t";
        }
        cout << endl;
    }

    // ---------------- FLOYD-WARSHALL ALGORITHM ----------------
    // k = intermediate vertex, i = source vertex, j = destination vertex
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                // Update shortest path if going through vertex k is shorter
                // Check != INF to prevent integer overflow during addition
                if (dist[i][k] != INF &&
                    dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }

        // Display intermediate distance matrix (Ak) after considering vertex k+1
        cout << "\nMatrix A" << k + 1
             << " (Vertex " << k + 1 << "):\n";

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (dist[i][j] == INF)
                    cout << "INF\t";
                else
                    cout << dist[i][j] << "\t";
            }
            cout << endl;
        }
    }

    // Display Final Shortest Distance Matrix (A4)
    cout << "\nFinal Shortest Distance Matrix:\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (dist[i][j] == INF)
                cout << "INF\t";
            else
                cout << dist[i][j] << "\t";
        }
        cout << endl;
    }

    return 0;
}
