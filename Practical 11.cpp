#include <iostream>
using namespace std;

int main()
{
    const int n = 4;
    const int INF = 99999;

    int dist[n][n] = {
        {0, 2, INF, 3},
        {1, 0, 2, INF},
        {INF, INF, 0, INF},
        {4, INF, 3, 0}
    };

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

    // Floyd-Warshall Algorithm
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (dist[i][k] != INF &&
                    dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }

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