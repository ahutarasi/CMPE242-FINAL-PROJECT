#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>

using namespace std;

// Global counter to track the number of operations during sorting
int operationCount = 0;

// Swap function to exchange two elements in the array
void swapElements(int &first, int &second) {
    operationCount++; // Count the swap operation
    int temp = first;
    first = second;
    second = temp;
}

// Function to maintain the heap property for heap sort (heapify)
void heapify(vector<int> &arr, int heapSize, int rootIndex) {
    int largest = rootIndex; // Assume the root is the largest
    int leftChild = 2 * rootIndex + 1; // Left child index
    int rightChild = 2 * rootIndex + 2; // Right child index

    operationCount++; // Comparison for left child
    if (leftChild < heapSize && arr[leftChild] > arr[largest]) {
        largest = leftChild;
    }

    operationCount++; // Comparison for right child
    if (rightChild < heapSize && arr[rightChild] > arr[largest]) {
        largest = rightChild;
    }

    // If the largest element is not the root, swap and heapify
    if (largest != rootIndex) {
        swapElements(arr[rootIndex], arr[largest]);
        heapify(arr, heapSize, largest); // Recursively heapify
    }
}

// Function to perform the heapsort algorithm
void heapSort(vector<int> &arr) {
    int arrSize = arr.size();

    // Build max heap
    for (int i = arrSize / 2 - 1; i >= 0; i--) {
        heapify(arr, arrSize, i);
    }

    // Extract elements one by one
    for (int i = arrSize - 1; i > 0; i--) {
        swapElements(arr[0], arr[i]); // Move max to end
        heapify(arr, i, 0); // Heapify reduced heap
    }
}

// Utility function to print array contents
void printArray(const vector<int> &arr) {
    for (int element : arr) {
        cout << element << " ";
    }
    cout << endl;
}

// Generate random integer array
vector<int> generateRandomArray(int size, int range) {
    vector<int> arr(size);
    for (int &num : arr) {
        num = rand() % range;
    }
    return arr;
}

// Task 2: Run complexity experiments and print a formatted table
void runExperiment(const vector<int>& sizes) {
    cout << "\n--- Complexity Experiment Results ---\n";
    cout << left << setw(12) << "Array Size"
         << setw(20) << "Operation Count"
         << setw(15) << "n"
         << setw(15) << "n log n"
         << setw(15) << "n^2"
         << setw(15) << "log n"
         << "\n";

    cout << string(92, '-') << "\n";

    for (int size : sizes) {
        vector<int> testArray = generateRandomArray(size, 1000);
        operationCount = 0;
        heapSort(testArray);

        double n = size;
        double logn = log2(n);
        double nlogn = n * logn;
        double nsquared = n * n;

        cout << left << setw(12) << size
             << setw(20) << operationCount
             << setw(15) << (int)n
             << setw(15) << (int)nlogn
             << setw(15) << (int)nsquared
             << setw(15) << (int)logn
             << "\n";
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed random generator

    // Task 1 – Heapsort Example
    cout << "=========================\n";
    cout << " CMPE242 Term Project 2\n";
    cout << " Task 1 – Heapsort Example\n";
    cout << "=========================\n";

    vector<int> data = generateRandomArray(20, 100);

    cout << "\nOriginal Array:\n";
    printArray(data);

    operationCount = 0;
    heapSort(data);

    cout << "\nSorted Array:\n";
    printArray(data);

    cout << "\nTotal Operations Count (Task 1): " << operationCount << endl;
    cout << "(Includes swaps and comparisons)\n";

    // Task 2 – Complexity Analysis
    cout << "\n=========================\n";
    cout << " Task 2 – Complexity Analysis\n";
    cout << "=========================\n";

    vector<int> sizes = {10, 100, 1000};
    runExperiment(sizes);

    return 0;
}
