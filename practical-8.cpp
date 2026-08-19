#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;

class Graph
{
    int V;
    vector<vector<int>> adj;

public:

    // Constructor
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
        adj[v].push_back(u);     // Undirected graph
    }

    // Display adjacency list
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

    // Iterative DFS using vector as stack
    vector<int> DFS(int start)
    {
        vector<bool> visited(V, false);
        vector<int> result;
        vector<int> st;

        st.push_back(start);

        while (!st.empty())
        {
            int node = st.back();
            st.pop_back();

            if (!visited[node])
            {
                visited[node] = true;
                result.push_back(node);

                for (auto it = adj[node].rbegin();
                     it != adj[node].rend(); ++it)
                {
                    if (!visited[*it])
                        st.push_back(*it);
                }
            }
        }

        return result;
    }

    // BFS using vector as queue
    vector<int> BFS(int start)
    {
        vector<bool> visited(V, false);
        vector<int> result;
        vector<int> q;

        int front = 0;

        visited[start] = true;
        q.push_back(start);

        while (front < q.size())
        {
            int node = q[front];
            front++;

            result.push_back(node);

            for (int neighbour : adj[node])
            {
                if (!visited[neighbour])
                {
                    visited[neighbour] = true;
                    q.push_back(neighbour);
                }
            }
        }

        return result;
    }
};

int main()
{
    int V, E;

    cout << "Enter number of vertices: ";
    cin >> V;

    if (V <= 0)
    {
        cout << "Invalid number of vertices!";
        return 0;
    }

    Graph g(V);

    cout << "Enter number of edges: ";
    cin >> E;

    if (E < 0)
    {
        cout << "Invalid number of edges!";
        return 0;
    }

    cout << "Enter edges (u v):\n";

    for (int i = 0; i < E; i++)
    {
        int u, v;
        cin >> u >> v;

        g.addEdge(u, v);
    }

    // Display graph
    g.displayGraph();

    int start;

    cout << "\nEnter starting vertex: ";
    cin >> start;

    if (start < 0 || start >= V)
    {
        cout << "Invalid Starting Vertex!";
        return 0;
    }

    // DFS time
    auto startDFS = high_resolution_clock::now();

    vector<int> dfsResult = g.DFS(start);

    auto endDFS = high_resolution_clock::now();

    auto dfsTime =
        duration_cast<nanoseconds>(endDFS - startDFS);

    // BFS time
    auto startBFS = high_resolution_clock::now();

    vector<int> bfsResult = g.BFS(start);

    auto endBFS = high_resolution_clock::now();

    auto bfsTime =
        duration_cast<nanoseconds>(endBFS - startBFS);

    // Display DFS
    cout << "\nDFS Traversal : ";

    for (int node : dfsResult)
        cout << node << " ";

    // Display BFS
    cout << "\nBFS Traversal : ";

    for (int node : bfsResult)
        cout << node << " ";

    // Execution time
    cout << "\n\nExecution Time";
    cout << "\nDFS : " << dfsTime.count() << " ns";
    cout << "\nBFS : " << bfsTime.count() << " ns";

    // Complexity
    cout << "\n\nTime Complexity";
    cout << "\nDFS : O(V + E)";
    cout << "\nBFS : O(V + E)";

    cout << "\n\nSpace Complexity";
    cout << "\nDFS : O(V)";
    cout << "\nBFS : O(V)";

    return 0;
}
