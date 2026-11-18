/*
 * Program : Performance Comparison of Max Heap Sort vs. Min Heap Sort
 * Purpose : Sorts identical random datasets using Max Heap and Min Heap,
 *           verifies correctness, and compares execution times.
 *           Time Complexity: O(n log n) | Auxiliary Space: O(1) (In-place)
 */

#include <iostream>
#include <vector>
#include <algorithm> // For std::swap, std::reverse, std::is_sorted
#include <chrono>    // For high-resolution execution timing
#include <random>    // For mt19937 random number generator
#include <ctime>     // For time() seed

using namespace std;
using namespace chrono;

// Prints array elements (used only when n <= 20 to avoid console clutter)
void printArray(const vector<int>& arr)
{
    for (int num : arr)
        cout << num << " ";
    cout << endl;
}

// Restores Max Heap property for subtree rooted at index i | Time: O(log n)
void maxHeapify(vector<int>& arr, int n, int i)
{
    int largest = i;
    int leftChild = 2 * i + 1;
    int rightChild = 2 * i + 2;

    if (leftChild < n && arr[leftChild] > arr[largest])
        largest = leftChild;

    if (rightChild < n && arr[rightChild] > arr[largest])
        largest = rightChild;

    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        maxHeapify(arr, n, largest); // Recursively heapify affected subtree
    }
}

// Sorts array in ascending order using Max Heap | Time: O(n log n) | Space: O(1)
void maxHeapSort(vector<int>& arr)
{
    int n = arr.size();

    // Step 1: Build Max Heap starting from last non-leaf node (n/2 - 1) | O(n)
    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(arr, n, i);

    // Step 2: Move root (largest) to end and reduce heap size | O(n log n)
    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        maxHeapify(arr, i, 0);
    }
}

// Restores Min Heap property for subtree rooted at index i | Time: O(log n)
void minHeapify(vector<int>& arr, int n, int i)
{
    int smallest = i;
    int leftChild = 2 * i + 1;
    int rightChild = 2 * i + 2;

    if (leftChild < n && arr[leftChild] < arr[smallest])
        smallest = leftChild;

    if (rightChild < n && arr[rightChild] < arr[smallest])
        smallest = rightChild;

    if (smallest != i)
    {
        swap(arr[i], arr[smallest]);
        minHeapify(arr, n, smallest); // Recursively heapify affected subtree
    }
}

// Sorts array in ascending order using Min Heap | Time: O(n log n) | Space: O(1)
void minHeapSort(vector<int>& arr)
{
    int n = arr.size();

    // Step 1: Build Min Heap starting from last non-leaf node
    for (int i = n / 2 - 1; i >= 0; i--)
        minHeapify(arr, n, i);

    // Step 2: Extract smallest elements to end (produces descending order)
    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        minHeapify(arr, i, 0);
    }

    // Step 3: Reverse array to get ascending order | Time: O(n)
    reverse(arr.begin(), arr.end());
}

int main()
{
    int n;

    cout << "=====================================\n";
    cout << "      HEAP SORT COMPARISON\n";
    cout << "=====================================\n";

    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> original(n);

    // Generate uniform random integers between 1 and 100,000
    mt19937 rng(time(nullptr));
    uniform_int_distribution<int> dist(1, 100000);

    for (int i = 0; i < n; i++)
        original[i] = dist(rng);

    // Create identical copies so both algorithms sort the exact same input
    vector<int> maxHeapArray = original;
    vector<int> minHeapArray = original;

    if (n <= 20)
    {
        cout << "\nOriginal Array:\n";
        printArray(original);
    }

    // Measure Max Heap Sort execution time
    auto maxStartTime = high_resolution_clock::now();
    maxHeapSort(maxHeapArray);
    auto maxEndTime = high_resolution_clock::now();

    // Measure Min Heap Sort execution time
    auto minStartTime = high_resolution_clock::now();
    minHeapSort(minHeapArray);
    auto minEndTime = high_resolution_clock::now();

    // Verify both arrays are sorted in ascending order
    bool maxSorted = is_sorted(maxHeapArray.begin(), maxHeapArray.end());
    bool minSorted = is_sorted(minHeapArray.begin(), minHeapArray.end());

    // Convert durations into multiple time units
    auto maxNano = duration_cast<nanoseconds>(maxEndTime - maxStartTime);
    auto maxMicro = duration_cast<microseconds>(maxEndTime - maxStartTime);
    auto maxMilli = duration_cast<milliseconds>(maxEndTime - maxStartTime);
    duration<double> maxSecond = maxEndTime - maxStartTime;

    auto minNano = duration_cast<nanoseconds>(minEndTime - minStartTime);
    auto minMicro = duration_cast<microseconds>(minEndTime - minStartTime);
    auto minMilli = duration_cast<milliseconds>(minEndTime - minStartTime);
    duration<double> minSecond = minEndTime - minStartTime;

    if (n <= 20)
    {
        cout << "\nSorted Array using Max Heap Sort:\n";
        printArray(maxHeapArray);

        cout << "\nSorted Array using Min Heap Sort:\n";
        printArray(minHeapArray);
    }

    // Display Max Heap Sort results
    cout << "\n=====================================\n";
    cout << "         MAX HEAP SORT\n";
    cout << "=====================================\n";

    cout << "Sorting Status : " << (maxSorted ? "SUCCESS\n" : "FAILED\n");
    cout << "Execution Time\n";
    cout << "Nanoseconds  : " << maxNano.count() << " ns\n";
    cout << "Microseconds : " << maxMicro.count() << " us\n";
    cout << "Milliseconds : " << maxMilli.count() << " ms\n";
    cout << "Seconds      : " << maxSecond.count() << " s\n";

    // Display Min Heap Sort results
    cout << "\n=====================================\n";
    cout << "         MIN HEAP SORT\n";
    cout << "=====================================\n";

    cout << "Sorting Status : " << (minSorted ? "SUCCESS\n" : "FAILED\n");
    cout << "Execution Time\n";
    cout << "Nanoseconds  : " << minNano.count() << " ns\n";
    cout << "Microseconds : " << minMicro.count() << " us\n";
    cout << "Milliseconds : " << minMilli.count() << " ms\n";
    cout << "Seconds      : " << minSecond.count() << " s\n";

    // Display theoretical complexity & performance summary
    cout << "\n=====================================\n";
    cout << "      ALGORITHM COMPLEXITY\n";
    cout << "=====================================\n";

    cout << "Max Heap Sort Time Complexity : O(n log n)\n";
    cout << "Min Heap Sort Time Complexity : O(n log n)\n";
    cout << "Space Complexity              : O(1)\n";

    cout << "\n=====================================\n";
    cout << "     PERFORMANCE COMPARISON\n";
    cout << "=====================================\n";

    if (maxNano.count() < minNano.count())
    {
        cout << "Max Heap Sort is Faster.\n";
    }
    else if (maxNano.count() > minNano.count())
    {
        cout << "Min Heap Sort is Faster.\n";
    }
    else
    {
        cout << "Both algorithms took the same time.\n";
    }

    cout << "\nExperiment Completed Successfully.\n";

    return 0;
}
