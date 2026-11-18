/*
 * Program : Performance Comparison of Linear Search vs. Binary Search
 * Purpose : Searches for a target key in a sorted array of 100,000 elements
 *           and compares the execution time of both searching algorithms.
 */

#include <iostream>
#include <vector>
#include <chrono> // For high-resolution execution timing
using namespace std;
using namespace std::chrono;

// Sequentially checks every element until match is found | Time: O(n) | Space: O(1)
int linearSearch(const vector<int> &numbers, int searchKey)
{
    for (int i = 0; i < numbers.size(); i++)
    {
        if (numbers[i] == searchKey)
        {
            return i; // Return index if element is found
        }
    }

    return -1; // Return -1 if element is not present
}

// Repeatedly halves the sorted search space | Time: O(log n) | Space: O(1)
int binarySearch(const vector<int> &numbers, int searchKey)
{
    int low = 0;
    int high = numbers.size() - 1;

    while (low <= high)
    {
        // Avoids integer overflow compared to (low + high) / 2
        int mid = low + (high - low) / 2;

        if (numbers[mid] == searchKey)
        {
            return mid; // Key found at mid
        }
        else if (numbers[mid] < searchKey)
        {
            low = mid + 1; // Search right half
        }
        else
        {
            high = mid - 1; // Search left half
        }
    }

    return -1; // Key not found
}

int main()
{
    const int size = 100000;

    // Populate vector with sorted numbers from 1 to 100,000 (required for Binary Search)
    vector<int> numbers(size);
    for (int i = 0; i < size; i++)
    {
        numbers[i] = i + 1;
    }

    int searchKey;
    cout << "Enter element to search: ";
    cin >> searchKey;

    int position;

    // ---------------- 1. LINEAR SEARCH TIMING ----------------
    auto start = high_resolution_clock::now();
    position = linearSearch(numbers, searchKey);
    auto stop = high_resolution_clock::now();
    
    cout << "\nLinear Search\n";
    if (position != -1)
    {
        cout << "Element found at index: " << position << endl;
    }
    else
    {
        cout << "Element not found." << endl;
    }

    cout << "Time Taken : "
         << duration_cast<microseconds>(stop - start).count()
         << " microseconds\n";

    // ---------------- 2. BINARY SEARCH TIMING ----------------
    start = high_resolution_clock::now();
    position = binarySearch(numbers, searchKey);
    stop = high_resolution_clock::now();
    
    cout << "\nBinary Search\n";
    if (position != -1)
    {
        cout << "Element found at index: " << position << endl;
    }
    else
    {
        cout << "Element not found." << endl;
    }

    cout << "Time Taken : "
         << duration_cast<microseconds>(stop - start).count()
         << " microseconds\n";

    return 0;
}
