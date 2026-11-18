/*
 * Program : Matrix Chain Multiplication using Dynamic Programming
 * Purpose : Finds the optimal parenthesization order to multiply a chain of 
 *           matrices with the minimum number of scalar multiplications.
 *           Time Complexity: O(n^3) | Space Complexity: O(n^2)
 */

#include <iostream>
#include <climits> // For INT_MAX
#include <chrono>  // For high-resolution execution timing

using namespace std;

// Computes minimum scalar multiplications for matrices A1...An | Time: O(n^3) | Space: O(n^2)
int matrixChainMultiplication(int p[], int n) {

    // m[i][j] stores minimum cost to multiply matrices Ai through Aj (1-indexed)
    // Diagonal m[i][i] = 0 because multiplying a single matrix costs 0
    int m[10][10] = {0};

    // chainLength = subproblem chain length from 2 up to n matrices
    for (int chainLength = 2; chainLength <= n; ++chainLength) {

        for (int i = 1; i <= n - chainLength + 1; ++i) {

            int j = i + chainLength - 1;
            m[i][j] = INT_MAX;

            // Test every split point k between i and j (i <= k < j)
            for (int k = i; k < j; ++k) {

                // Total cost = left chain cost + right chain cost + cost to multiply resulting two matrices
                int cost = m[i][k]
                         + m[k + 1][j]
                         + p[i - 1] * p[k] * p[j];

                if (cost < m[i][j]) {
                    m[i][j] = cost;
                }
            }
        }
    }

    // ---------------- DISPLAY DP COST TABLE ----------------
    cout << "\n--- DP Table ---\n\n";

    cout << "\t";
    for (int i = 1; i <= n; i++) {
        cout << "A" << i << "\t";
    }
    cout << endl;

    for (int i = 1; i <= n; ++i) {
        cout << "A" << i << "\t";

        for (int j = 1; j <= n; ++j) {
            // Lower triangle (i > j) is unused since subproblems span from i to j
            if (i > j)
                cout << "-\t";
            else
                cout << m[i][j] << "\t";
        }

        cout << endl;
    }

    return m[1][n]; // Minimum multiplications for the full chain A1...An
}

int main() {

    // Dimension array p: Matrix Ai has dimensions p[i-1] x p[i]
    // A1 = 5x10, A2 = 10x3, A3 = 3x12, A4 = 12x5
    int p[] = {5, 10, 3, 12, 5};
    int n = 4; // Number of matrices (always p.length - 1)

    cout << "Matrix Chain Multiplication\n";

    cout << "\nMatrices:\n";
    cout << "A1 = 5 x 10\n";
    cout << "A2 = 10 x 3\n";
    cout << "A3 = 3 x 12\n";
    cout << "A4 = 12 x 5\n";

    // Measure execution time
    auto start = chrono::high_resolution_clock::now();
    int result = matrixChainMultiplication(p, n);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double, nano> duration = end - start;

    // Display final results
    cout << "\n--- Results ---\n";
    cout << "Minimum number of scalar multiplications : " << result << endl;
    cout << "Optimal Parenthesization : ((A1 A2) (A3 A4))" << endl;
    cout << "Execution Time : " << duration.count() << " ns" << endl;

    return 0;
}
