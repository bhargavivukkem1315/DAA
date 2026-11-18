/*
 * Program : Graph Traversal using BFS and DFS
 * Purpose : Represents an undirected graph using an adjacency list, performs 
 *           iterative DFS and BFS traversals, and compares execution times.
 *           Time Complexity: O(V + E) | Space Complexity: O(V)
 */

#include <iostream>
#include <vector>
#include <chrono> // For high-resolution execution timing

using namespace std;
using namespace chrono;

// Represents an undirected graph using an Adjacency List
class Graph
{
    int V;                   // Total number of vertices
    vector<vector<int>> adj; // Adjacency list storing neighbors for each vertex

public:

    // Initializes graph with V vertices (0-indexed: 0 to V-1)
    Graph(int vertices)
    {
        V = vertices;
        adj.resize(V);
    }

    // Adds an undirected edge between u and v after bounds validation
    void addEdge(int u, int v)
    {
        if (u < 0 || u >= V || v < 0 || v >= V)
        {
            cout << "Invalid Edge!\n";
            return;
        }

        adj[u].push_back(v);
        adj[v].push_back(u); // Undirected edge requires entries in both lists
    }

    // Prints the adjacency list representation of the graph
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

    // Iterative Depth-First Search using a vector as a LIFO Stack | Time: O(V + E) | Space: O(V)
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

                // Push neighbors in reverse order so the first neighbor is popped first
                for (auto it = adj[node].rbegin(); it != adj[node].rend(); ++it)
                {
                    if (!visited[*it])
                        st.push_back(*it);
                }
            }
        }

        return result;
    }

    // Breadth-First Search using a vector with front pointer as a FIFO Queue | Time: O(V + E) | Space: O(V)
    vector<int> BFS(int start)
    {
        vector<bool> visited(V, false);
        vector<int> result;
        vector<int> q;

        int front = 0; // Index pointer to avoid O(n) front-erasure overhead

        visited[start] = true;
        q.push_back(start);

        while (front < q.size())
        {
            int node = q[front];
            front++;

            result.push_back(node);

            // Visit and enqueue all unvisited adjacent vertices level by level
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

    g.displayGraph();

    int start;
    cout << "\nEnter starting vertex: ";
    cin >> start;

    if (start < 0 || start >= V)
    {
        cout << "Invalid Starting Vertex!";
        return 0;
    }

    // Measure DFS execution time
    auto startDFS = high_resolution_clock::now();
    vector<int> dfsResult = g.DFS(start);
    auto endDFS = high_resolution_clock::now();
    auto dfsTime = duration_cast<nanoseconds>(endDFS - startDFS);

    // Measure BFS execution time
    auto startBFS = high_resolution_clock::now();
    vector<int> bfsResult = g.BFS(start);
    auto endBFS = high_resolution_clock::now();
    auto bfsTime = duration_cast<nanoseconds>(endBFS - startBFS);

    // Display Traversal Orders
    cout << "\nDFS Traversal : ";
    for (int node : dfsResult)
        cout << node << " ";

    cout << "\nBFS Traversal : ";
    for (int node : bfsResult)
        cout << node << " ";

    // Display Execution Times & Asymptotic Complexities
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
