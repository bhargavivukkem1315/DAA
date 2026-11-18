/*
 * Program : Coin Change Problem (Greedy vs. Dynamic Programming)
 * Purpose : Finds minimum coins for a target amount using Greedy (fast, may 
 *           be suboptimal) and DP (always optimal).
 */
#include <iostream>
#include <algorithm> // For std::min
using namespace std;

int main() {
    int coins[] = {1, 5, 6, 9}; // Must be sorted in ascending order
    int n = 4, amount = 11;

    // ---------------- 1. GREEDY APPROACH ----------------
    // Picks the largest coin possible at each step | Time: O(n) | Space: O(1)
    int remaining = amount;
    int greedyCount = 0;

    cout << "GREEDY APPROACH" << endl;
    cout << "Coins selected: ";

    for (int i = n - 1; i >= 0; i--) {
        while (remaining >= coins[i]) {
            cout << coins[i] << " ";
            remaining -= coins[i];
            greedyCount++;
        }
    }

    cout << "\nMinimum coins = " << greedyCount << endl;

    // ---------------- 2. DYNAMIC PROGRAMMING APPROACH ----------------
    // Evaluates all subproblems to guarantee optimal result | Time: O(amount * n) | Space: O(amount)
    int dp[amount + 1];
    dp[0] = 0; // Base case: 0 coins needed to make amount 0

    for (int i = 1; i <= amount; i++) {
        dp[i] = 9999; // Initialize with a large value representing infinity

        for (int j = 0; j < n; j++) {
            if (coins[j] <= i) {
                dp[i] = min(dp[i], dp[i - coins[j]] + 1);
            }
        }
    }

    // Display DP lookup table
    cout << "\n\nDYNAMIC PROGRAMMING APPROACH" << endl;
    cout << "Amount : ";
    for (int i = 0; i <= amount; i++)
        cout << i << " ";

    cout << "\nDP     : ";
    for (int i = 0; i <= amount; i++)
        cout << dp[i] << " ";
    cout << endl;

    // Backtrack through the DP table to print the exact coins chosen
    cout << "Coins selected: ";
    int x = amount;

    while (x > 0) {
        for (int j = 0; j < n; j++) {
            if (coins[j] <= x && dp[x] == dp[x - coins[j]] + 1) {
                cout << coins[j] << " ";
                x -= coins[j];
                break;
            }
        }
    }

    cout << "\nMinimum coins = " << dp[amount] << endl;

    return 0;
}
