#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main()
{
    int n;
    cout << "Enter number of cities: ";
    cin >> n;

    int cost[10][10];

    cout << "Enter cost matrix:\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> cost[i][j];
        }
    }

    vector<int> path;
    for (int i = 1; i < n; i++)
    {
        path.push_back(i);
    }

    int minCost = INT_MAX;
    vector<int> bestPath;

    do
    {
        int totalCost = 0;
        int currentCity = 0;

        for (int i = 0; i < path.size(); i++)
        {
            totalCost += cost[currentCity][path[i]];
            currentCity = path[i];
        }

        totalCost += cost[currentCity][0];

        if (totalCost < minCost)
        {
            minCost = totalCost;
            bestPath = path;
        }

    } while (next_permutation(path.begin(), path.end()));

    cout << "\nMinimum cost: " << minCost;
    cout << "\nBest tour: 1 -> ";

    for (int i = 0; i < bestPath.size(); i++)
    {
        cout << bestPath[i] + 1 << " -> ";
    }

    cout << "1\n";

    return 0;
}