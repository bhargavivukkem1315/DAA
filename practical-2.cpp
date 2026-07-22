#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;

//  Linear Search 
int linearSearch(const vector<int> &numbers, int searchKey)
{
    for (int i = 0; i < numbers.size(); i++)
    {
        if (numbers[i] == searchKey)
        {
            return i;
        }
    }

    return -1;
}

//  Binary Search 
int binarySearch(const vector<int> &numbers, int searchKey)
{
    int low = 0;
    int high = numbers.size() - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (numbers[mid] == searchKey)
        {
            return mid;
        }
        else if (numbers[mid] < searchKey)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return -1;
}

int main()
{
    const int size = 100000;

    vector<int> numbers(size);
    for (int i = 0; i < size; i++)
    {
        numbers[i] = i + 1;
    }

    int searchKey;

    cout << "Enter element to search: ";
    cin >> searchKey;

    int position;
    //  Linear Search 
    auto start = high_resolution_clock::now();

    position = linearSearch(numbers, searchKey);

    auto stop = high_resolution_clock::now();
    
    cout << " \nLinear Search\n ";

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
    // Binary Search 
    start = high_resolution_clock::now();

    position = binarySearch(numbers, searchKey);

    stop = high_resolution_clock::now();
    
    cout << " \n binary Search\n ";
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


