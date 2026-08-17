#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int coins[] = {1, 5, 6, 9};
    int n = 4, amount = 11;

    // ---------------- GREEDY ----------------
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


    // ---------------- DP ----------------
    int dp[amount + 1];

    dp[0] = 0;

    for (int i = 1; i <= amount; i++) {
        dp[i] = 9999;

        for (int j = 0; j < n; j++) {
            if (coins[j] <= i) {
                dp[i] = min(dp[i],
                            dp[i - coins[j]] + 1);
            }
        }
    }

    // Print DP table
    cout << "\n\nDYNAMIC PROGRAMMING APPROACH" << endl;
    cout << "Amount : ";

    for (int i = 0; i <= amount; i++)
        cout << i << " ";

    cout << "\nDP     : ";

    for (int i = 0; i <= amount; i++)
        cout << dp[i] << " ";

    cout << endl;

    // Find selected coins
    cout << "Coins selected: ";

    int x = amount;

    while (x > 0) {
        for (int j = 0; j < n; j++) {
            if (coins[j] <= x &&
                dp[x] == dp[x - coins[j]] + 1) {

                cout << coins[j] << " ";
                x -= coins[j];
                break;
            }
        }
    }

    cout << "\nMinimum coins = " << dp[amount] << endl;

    return 0;
}