#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Iterative Factorial
unsigned long long factorialIterative(int n)
{
    unsigned long long fact = 1;

    for (int i = 1; i <= n; i++)
    {
        fact = fact * i;
    }

    return fact;
}

// Recursive Factorial
unsigned long long factorialRecursive(int n)
{
    if (n == 0 || n == 1)
    {
        return 1;
    }

    return n * factorialRecursive(n - 1);
}

int main()
{
    int n;

    cout << "Enter a number: ";
    cin >> n;

    if (n < 0)
    {
        cout << "Factorial is not defined for negative numbers.";
        return 0;
    }

    // Iterative Time Calculation
    auto start1 = high_resolution_clock::now();
    unsigned long long ans1 = factorialIterative(n);
    auto stop1 = high_resolution_clock::now();

    auto duration1 = duration_cast<nanoseconds>(stop1 - start1);

    // Recursive Time Calculation
    auto start2 = high_resolution_clock::now();
    unsigned long long ans2 = factorialRecursive(n);
    auto stop2 = high_resolution_clock::now();

    auto duration2 = duration_cast<nanoseconds>(stop2 - start2);

    cout << "\nFactorial using Iteration = " << ans1 << endl;
    cout << "Execution Time = " << duration1.count() << " ns" << endl;

    cout << "\nFactorial using Recursion = " << ans2 << endl;
    cout << "Execution Time = " << duration2.count() << " ns" << endl;

    return 0;
}