/*
 * Program : Travelling Salesman Problem (TSP) using Brute Force
 * Purpose : Finds the shortest possible tour visiting every city once and 
 *           returning to the starting city by checking all permutations.
 *           Time Complexity: O(n!) | Space Complexity: O(n)
 */

#include <iostream>
#include <vector>
#include <algorithm> // For next_permutation
#include <climits>   // For INT_MAX
using namespace std;

int main()
{
    int n;
    cout << "Enter number of cities: ";
    cin >> n;

    int cost[10][10]; // Adjacency matrix storing travel cost between cities

    cout << "Enter cost matrix:\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> cost[i][j];
        }
    }

    // Store all cities except starting city (index 0) to generate permutations
    vector<int> path;
    for (int i = 1; i < n; i++)
    {
        path.push_back(i);
    }

    int minCost = INT_MAX;
    vector<int> bestPath;

    // ---------------- GENERATE & EVALUATE ALL TOURS ----------------
    // Checks all (n - 1)! possible routes starting and ending at city 0
    do
    {
        int totalCost = 0;
        int currentCity = 0;

        // Calculate cost along the current permutation path
        for (int i = 0; i < path.size(); i++)
        {
            totalCost += cost[currentCity][path[i]];
            currentCity = path[i];
        }

        // Add return cost back to the starting city (city 0)
        totalCost += cost[currentCity][0];

        // Update minimum cost and optimal route if a shorter tour is found
        if (totalCost < minCost)
        {
            minCost = totalCost;
            bestPath = path;
        }

    } while (next_permutation(path.begin(), path.end()));

    // Display optimal cost and tour (converting 0-based index to 1-based city numbers)
    cout << "\nMinimum cost: " << minCost;
    cout << "\nBest tour: 1 -> ";

    for (int i = 0; i < bestPath.size(); i++)
    {
        cout << bestPath[i] + 1 << " -> ";
    }

    cout << "1\n";

    return 0;
}
