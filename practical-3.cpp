#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <ctime>

using namespace std;
using namespace chrono;

//----------------------------------------------------
// Function to print array (only for small inputs)
//----------------------------------------------------
void printArray(const vector<int>& arr)
{
    for (int num : arr)
        cout << num << " ";
    cout << endl;
}

//----------------------------------------------------
// MAX HEAPIFY
//----------------------------------------------------
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

        // Recursively fix affected subtree
        maxHeapify(arr, n, largest);
    }
}

//----------------------------------------------------
// MAX HEAP SORT
//----------------------------------------------------
void maxHeapSort(vector<int>& arr)
{
    int n = arr.size();

    // Build Max Heap
    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(arr, n, i);

    // Extract one element at a time
    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        maxHeapify(arr, i, 0);
    }
}

//----------------------------------------------------
// MIN HEAPIFY
//----------------------------------------------------
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

        // Recursively fix affected subtree
        minHeapify(arr, n, smallest);
    }
}

//----------------------------------------------------
// MIN HEAP SORT
//----------------------------------------------------
void minHeapSort(vector<int>& arr)
{
    int n = arr.size();

    // Build Min Heap
    for (int i = n / 2 - 1; i >= 0; i--)
        minHeapify(arr, n, i);

    // Extract elements
    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        minHeapify(arr, i, 0);
    }

    // Reverse to get ascending order
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

    // Modern Random Number Generator
    mt19937 rng(time(nullptr));
    uniform_int_distribution<int> dist(1, 100000);

    for (int i = 0; i < n; i++)
        original[i] = dist(rng);

    vector<int> maxHeapArray = original;
    vector<int> minHeapArray = original;
        //----------------------------------------------------
    // Print Original Array (Only for Small Inputs)
    //----------------------------------------------------
    if (n <= 20)
    {
        cout << "\nOriginal Array:\n";
        printArray(original);
    }

    //----------------------------------------------------
    // MAX HEAP SORT TIMING
    //----------------------------------------------------
    auto maxStartTime = high_resolution_clock::now();

    maxHeapSort(maxHeapArray);

    auto maxEndTime = high_resolution_clock::now();

    //----------------------------------------------------
    // MIN HEAP SORT TIMING
    //----------------------------------------------------
    auto minStartTime = high_resolution_clock::now();

    minHeapSort(minHeapArray);

    auto minEndTime = high_resolution_clock::now();

    //----------------------------------------------------
    // Verify Sorting
    //----------------------------------------------------
    bool maxSorted = is_sorted(maxHeapArray.begin(), maxHeapArray.end());
    bool minSorted = is_sorted(minHeapArray.begin(), minHeapArray.end());

    //----------------------------------------------------
    // Time Calculations
    //----------------------------------------------------
    auto maxNano = duration_cast<nanoseconds>(maxEndTime - maxStartTime);
    auto maxMicro = duration_cast<microseconds>(maxEndTime - maxStartTime);
    auto maxMilli = duration_cast<milliseconds>(maxEndTime - maxStartTime);
    duration<double> maxSecond = maxEndTime - maxStartTime;

    auto minNano = duration_cast<nanoseconds>(minEndTime - minStartTime);
    auto minMicro = duration_cast<microseconds>(minEndTime - minStartTime);
    auto minMilli = duration_cast<milliseconds>(minEndTime - minStartTime);
    duration<double> minSecond = minEndTime - minStartTime;

    //----------------------------------------------------
    // Display Sorted Arrays
    //----------------------------------------------------
    if (n <= 20)
    {
        cout << "\nSorted Array using Max Heap Sort:\n";
        printArray(maxHeapArray);

        cout << "\nSorted Array using Min Heap Sort:\n";
        printArray(minHeapArray);
    }

    //----------------------------------------------------
    // MAX HEAP RESULTS
    //----------------------------------------------------
    cout << "\n=====================================\n";
    cout << "         MAX HEAP SORT\n";
    cout << "=====================================\n";

    cout << "Sorting Status : ";
    if (maxSorted)
        cout << "SUCCESS\n";
    else
        cout << "FAILED\n";

    cout << "Execution Time\n";
    cout << "Nanoseconds  : " << maxNano.count() << " ns\n";
    cout << "Microseconds : " << maxMicro.count() << " us\n";
    cout << "Milliseconds : " << maxMilli.count() << " ms\n";
    cout << "Seconds      : " << maxSecond.count() << " s\n";
        //----------------------------------------------------
    // MIN HEAP RESULTS
    //----------------------------------------------------
    cout << "\n=====================================\n";
    cout << "         MIN HEAP SORT\n";
    cout << "=====================================\n";

    cout << "Sorting Status : ";
    if (minSorted)
        cout << "SUCCESS\n";
    else
        cout << "FAILED\n";

    cout << "Execution Time\n";
    cout << "Nanoseconds  : " << minNano.count() << " ns\n";
    cout << "Microseconds : " << minMicro.count() << " us\n";
    cout << "Milliseconds : " << minMilli.count() << " ms\n";
    cout << "Seconds      : " << minSecond.count() << " s\n";

    //----------------------------------------------------
    // Complexity Information
    //----------------------------------------------------
    cout << "\n=====================================\n";
    cout << "      ALGORITHM COMPLEXITY\n";
    cout << "=====================================\n";

    cout << "Max Heap Sort Time Complexity : O(n log n)\n";
    cout << "Min Heap Sort Time Complexity : O(n log n)\n";
    cout << "Space Complexity              : O(1)\n";

    //----------------------------------------------------
    // Performance Comparison
    //----------------------------------------------------
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