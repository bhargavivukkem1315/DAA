/*
 * Program : 0/1 Knapsack Problem using Dynamic Programming
 * Purpose : Maximizes total profit within a given weight capacity where each 
 *           item can either be included (1) or excluded (0).
 *           Time Complexity: O(n * W) | Space Complexity: O(n * W)
 */

#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n, maxWeight;

    cout << "Enter number of items: ";
    cin >> n;

    vector<int> weight(n);
    vector<int> profit(n);

    cout << "\nEnter weights: ";
    for (int i = 0; i < n; i++)
        cin >> weight[i];

    cout << "Enter profits: ";
    for (int i = 0; i < n; i++)
        cin >> profit[i];

    cout << "Enter maximum weight: ";
    cin >> maxWeight;

    // DP table where dp[i][w] stores max profit using first i items with capacity w
    vector<vector<int>> dp(n + 1, vector<int>(maxWeight + 1, 0));

    // ---------------- BUILD DP TABLE ----------------
    for (int i = 1; i <= n; i++)
    {
        for (int w = 0; w <= maxWeight; w++)
        {
            // Case 1: Exclude current item (carry forward previous best value)
            dp[i][w] = dp[i - 1][w];

            // Case 2: Include current item if it fits within current capacity w
            if (weight[i - 1] <= w)
            {
                int take = profit[i - 1] + dp[i - 1][w - weight[i - 1]];

                if (take > dp[i][w])
                    dp[i][w] = take;
            }
        }
    }

    // ---------------- BACKTRACK SELECTED ITEMS ----------------
    // Trace backwards from dp[n][maxWeight] to identify which items were included
    vector<int> selected(n, 0);
    int w = maxWeight;

    for (int i = n; i >= 1; i--)
    {
        // If profit changed compared to row above, item (i - 1) was included
        if (dp[i][w] != dp[i - 1][w])
        {
            selected[i - 1] = 1;
            w -= weight[i - 1];
        }
    }

    // ---------------- DISPLAY DP TABLE ----------------
    cout << "\n\n================ KNAPSACK DP TABLE ================\n\n";

    cout << "Profit | Available Weight | Maximum Weight\n";
    cout << "       |                   | ";

    for (int i = 0; i <= maxWeight; i++)
        cout << i << "   ";

    cout << "\n------------------------------------------------------\n";

    for (int i = 1; i <= n; i++)
    {
        cout << "   " << profit[i - 1] << "   |";
        cout << "        " << weight[i - 1] << "         | ";

        for (int w = 0; w <= maxWeight; w++)
            cout << dp[i][w] << "   ";

        cout << "\n";
    }

    cout << "------------------------------------------------------\n";

    // ---------------- DISPLAY OPTIMAL SOLUTION ----------------
    cout << "\n\n================ OPTIMAL SOLUTION =================\n\n";

    cout << "Profit          : ";
    for (int i = 0; i < n; i++)
        cout << profit[i] << "   ";

    cout << "\nAvailable Weight: ";
    for (int i = 0; i < n; i++)
        cout << weight[i] << "   ";

    cout << "\nSelection (0/1) : ";
    for (int i = 0; i < n; i++)
        cout << selected[i] << "   ";

    // Sum weights and profits of selected items
    int totalWeight = 0;
    int totalProfit = 0;

    cout << "\n\nSelected Weights: ";
    bool firstWeight = true;

    for (int i = 0; i < n; i++)
    {
        if (selected[i] == 1)
        {
            if (!firstWeight)
                cout << " + ";

            cout << weight[i];
            totalWeight += weight[i];
            firstWeight = false;
        }
    }
    cout << " = " << totalWeight;

    cout << "\nSelected Profits: ";
    bool firstProfit = true;

    for (int i = 0; i < n; i++)
    {
        if (selected[i] == 1)
        {
            if (!firstProfit)
                cout << " + ";

            cout << profit[i];
            totalProfit += profit[i];
            firstProfit = false;
        }
    }
    cout << " = " << totalProfit;

    cout << "\n\nMaximum Weight : " << maxWeight;
    cout << "\nMaximum Profit : " << totalProfit;

    cout << "\n\n=====================================================\n";

    return 0;
}
