#include <iostream>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

//----------------------------------------------------------
// Function : Iterative Factorial
// Time Complexity : O(n)
// Space Complexity: O(1)
//----------------------------------------------------------
unsigned long long factorialIterative(int n)
{
    unsigned long long result = 1;

    for (int i = 1; i <= n; i++)
    {
        result *= i;
    }

    return result;
}

//----------------------------------------------------------
// Function : Recursive Factorial
// Time Complexity : O(n)
// Space Complexity: O(n)
//----------------------------------------------------------
unsigned long long factorialRecursive(int n)
{
    if (n <= 1)
        return 1;

    return n * factorialRecursive(n - 1);
}

int main()
{
    char choice;

    cout << fixed << setprecision(2);

    do
    {
        int n;

        cout << "\n=====================================================\n";
        cout << "        FACTORIAL PERFORMANCE ANALYSIS";
        cout << "\n=====================================================\n";

        cout << "Enter a non-negative integer : ";

        if (!(cin >> n))
        {
            cout << "\nInvalid Input! Please enter only integers.\n";
            return 1;
        }

        if (n < 0)
        {
            cout << "\nFactorial is not defined for negative numbers.\n";
            continue;
        }

        //----------------------------------------------------------
        // Overflow Warning
        //----------------------------------------------------------
        if (n > 20)
        {
            cout << "\nWarning : Values greater than 20! exceed the capacity "
                 << "of unsigned long long.\n";
            cout << "The displayed result may not be correct.\n\n";
        }

        //----------------------------------------------------------
        // Measure Iterative Execution Time
        //----------------------------------------------------------
        auto startIter = high_resolution_clock::now();

        unsigned long long iterativeResult = factorialIterative(n);

        auto endIter = high_resolution_clock::now();

        duration<double, nano> iterativeTime = endIter - startIter;

        //----------------------------------------------------------
        // Measure Recursive Execution Time
        //----------------------------------------------------------
        auto startRec = high_resolution_clock::now();

        unsigned long long recursiveResult = factorialRecursive(n);

        auto endRec = high_resolution_clock::now();

        duration<double, nano> recursiveTime = endRec - startRec;

        //----------------------------------------------------------
        // Display Results
        //----------------------------------------------------------
        cout << "\n================== RESULTS ==================\n";

        cout << "Iterative Factorial : " << iterativeResult << endl;
        cout << "Recursive Factorial : " << recursiveResult << endl;

        //----------------------------------------------------------
        // Verify Correctness
        //----------------------------------------------------------
        if (iterativeResult == recursiveResult)
            cout << "Verification        : Both methods produced SAME result.\n";
        else
            cout << "Verification        : Results are DIFFERENT.\n";

        //----------------------------------------------------------
        // Display Execution Time
        //----------------------------------------------------------
        cout << "\n=============== EXECUTION TIME ===============\n";

        cout << "Iterative Time : "
             << iterativeTime.count()
             << " ns\n";

        cout << "Recursive Time : "
             << recursiveTime.count()
             << " ns\n";

        //----------------------------------------------------------
        // Performance Analysis
        //----------------------------------------------------------
        cout << "\n============= PERFORMANCE ANALYSIS =============\n";

        if (iterativeTime.count() < recursiveTime.count())
        {
            cout << "Faster Method : Iterative\n";
            cout << "Difference    : "
                 << recursiveTime.count() - iterativeTime.count()
                 << " ns\n";
        }
        else if (recursiveTime.count() < iterativeTime.count())
        {
            cout << "Faster Method : Recursive\n";
            cout << "Difference    : "
                 << iterativeTime.count() - recursiveTime.count()
                 << " ns\n";
        }
        else
        {
            cout << "Both methods took almost the same time.\n";
        }

        //----------------------------------------------------------
        // Algorithm Analysis
        //----------------------------------------------------------
        cout << "\n============= COMPLEXITY ANALYSIS =============\n";

        cout << "Iterative -> Time : O(n)"
             << "   Space : O(1)\n";

        cout << "Recursive -> Time : O(n)"
             << "   Space : O(n)\n";

        //----------------------------------------------------------
        // Program Information
        //----------------------------------------------------------
        cout << "\n=================== NOTE ======================\n";
        cout << "Recursive method uses extra memory because of\n";
        cout << "function call stack.\n";

        cout << "Iterative method is generally preferred for\n";
        cout << "large values because it uses constant memory.\n";

        //----------------------------------------------------------
        // Continue
        //----------------------------------------------------------
        cout << "\nDo you want to test another number? (Y/N): ";

        cin >> choice;

    } while (choice == 'Y' || choice == 'y');

    cout << "\n=========================================\n";
    cout << "Thank You!\n";
    cout << "=========================================\n";

    return 0;
}