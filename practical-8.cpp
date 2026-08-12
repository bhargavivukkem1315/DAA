#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <chrono>

using namespace std;
using namespace chrono;

class Graph
{
    int V;
    vector<vector<int>> adj;

public:

    Graph(int vertices)
    {
        V = vertices;
        adj.resize(V);
    }

    // Add edge with validation
    void addEdge(int u, int v)
    {
        if (u < 0 || u >= V || v < 0 || v >= V)
        {
            cout << "Invalid Edge!\n";
            return;
        }

        adj[u].push_back(v);
        adj[v].push_back(u);     // Remove for Directed Graph
    }

    // Display Adjacency List
    void displayGraph()
    {
        cout << "\nAdjacency List\n";

        for (int i = 0; i < V; i++)
        {
            cout << i << " -> ";

            for (int neighbour : adj[i])
                cout << neighbour << " ";

            cout << endl;
        }
    }

    // Iterative DFS
    void DFS(int start)
    {
        vector<bool> visited(V, false);
        stack<int> st;

        st.push(start);

        cout << "\nDFS Traversal : ";

        while (!st.empty())
        {
            int node = st.top();
            st.pop();

            if (!visited[node])
            {
                visited[node] = true;
                cout << node << " ";

                for (auto it = adj[node].rbegin(); it != adj[node].rend(); ++it)
                {
                    if (!visited[*it])
                        st.push(*it);
                }
            }
        }
    }
        // BFS
    void BFS(int start)
    {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "\nBFS Traversal : ";

        while (!q.empty())
        {
            int node = q.front();
            q.pop();

            cout << node << " ";

            for (int neighbour : adj[node])
            {
                if (!visited[neighbour])
                {
                    visited[neighbour] = true;
                    q.push(neighbour);
                }
            }
        }
    }
};

int main()
{
    int V, E;

    cout << "Enter number of vertices: ";
    cin >> V;

    Graph g(V);

    cout << "Enter number of edges: ";
    cin >> E;

    cout << "Enter edges (u v):\n";

    for (int i = 0; i < E; i++)
    {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    g.displayGraph();

    int start;

    cout << "\nEnter starting vertex: ";
    cin >> start;

    if (start < 0 || start >= V)
    {
        cout << "Invalid Starting Vertex!";
        return 0;
    }

    // DFS Time Analysis
    auto startDFS = high_resolution_clock::now();

    g.DFS(start);

    auto endDFS = high_resolution_clock::now();

    auto dfsTime = duration_cast<nanoseconds>(endDFS - startDFS);

    // BFS Time Analysis
    auto startBFS = high_resolution_clock::now();

    g.BFS(start);

    auto endBFS = high_resolution_clock::now();

    auto bfsTime = duration_cast<nanoseconds>(endBFS - startBFS);

    cout << "\n\nExecution Time";
    cout << "\nDFS : " << dfsTime.count() << " ns";
    cout << "\nBFS : " << bfsTime.count() << " ns";

    cout << "\n\nTime Complexity";
    cout << "\nDFS : O(V + E)";
    cout << "\nBFS : O(V + E)";

    cout << "\n\nSpace Complexity";
    cout << "\nDFS : O(V)";
    cout << "\nBFS : O(V)";

    return 0;
}