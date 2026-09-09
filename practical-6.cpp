// TIME & SPACE COMPLEXITY SUMMARY
// Method                        Time        Space
// Matrix Chain Multiplication  O(n^3)      O(n^2)
// DP Table                     O(n^2)      O(n^2)

#include <iostream>
#include <climits>
#include <chrono>

using namespace std;

// Function for Matrix Chain Multiplication
int matrixChainMultiplication(int p[], int n) {

    // m[i][j] stores minimum multiplication cost
    // from matrix Ai to Aj
    int m[10][10] = {0};

    // chainLength = number of matrices in the chain
    for (int chainLength = 2; chainLength <= n; ++chainLength) {

        for (int i = 1; i <= n - chainLength + 1; ++i) {

            int j = i + chainLength - 1;

            m[i][j] = INT_MAX;

            // Try every possible splitting position
            for (int k = i; k < j; ++k) {

                int cost = m[i][k]
                         + m[k + 1][j]
                         + p[i - 1] * p[k] * p[j];

                if (cost < m[i][j]) {
                    m[i][j] = cost;
                }
            }
        }
    }

    // Display DP Table
    cout << "\n--- DP Table ---\n\n";

    // Column headings
    cout << "\t";
    for (int i = 1; i <= n; i++) {
        cout << "A" << i << "\t";
    }
    cout << endl;

    // Table values
    for (int i = 1; i <= n; ++i) {

        cout << "A" << i << "\t";

        for (int j = 1; j <= n; ++j) {

            if (i > j)
                cout << "-\t";
            else
                cout << m[i][j] << "\t";
        }

        cout << endl;
    }

    return m[1][n];
}

int main() {

    // Matrix Dimensions
    // A1 = 5 x 10
    // A2 = 10 x 3
    // A3 = 3 x 12
    // A4 = 12 x 5

    int p[] = {5, 10, 3, 12, 5};

    int n = 4;

    cout << "Matrix Chain Multiplication\n";

    // Display matrices
    cout << "\nMatrices:\n";
    cout << "A1 = 5 x 10\n";
    cout << "A2 = 10 x 3\n";
    cout << "A3 = 3 x 12\n";
    cout << "A4 = 12 x 5\n";

    // Start execution time
    auto start = chrono::high_resolution_clock::now();

    int result = matrixChainMultiplication(p, n);

    // End execution time
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double, nano> duration = end - start;

    // Display final results
    cout << "\n--- Results ---\n";

    cout << "Minimum number of scalar multiplications : "
         << result << endl;

    cout << "Optimal Parenthesization : "
         << "((A1 A2) (A3 A4))" << endl;

    cout << "Execution Time : "
         << duration.count() << " ns" << endl;

    return 0;
}