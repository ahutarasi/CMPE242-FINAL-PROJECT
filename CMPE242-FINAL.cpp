#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

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
void heapify(std::vector<int> &arr, int heapSize, int rootIndex) {
    int largest = rootIndex; // Assume the root is the largest
    int leftChild = 2 * rootIndex + 1; // Left child index
    int rightChild = 2 * rootIndex + 2; // Right child index

    operationCount++; // Count the comparison for the left child
    if (leftChild < heapSize && arr[leftChild] > arr[largest]) {
        largest = leftChild; // Left child is larger
    }

    operationCount++; // Count the comparison for the right child
    if (rightChild < heapSize && arr[rightChild] > arr[largest]) {
        largest = rightChild; // Right child is larger
    }

    // If the largest element is not the root, swap and heapify the affected subtree
    if (largest != rootIndex) {
        swapElements(arr[rootIndex], arr[largest]);
        heapify(arr, heapSize, largest); // Recursively heapify the affected subtree
    }
}

// Function to perform the heapsort algorithm
void heapSort(std::vector<int> &arr) {
    int arrSize = arr.size();

    // Build the heap (rearrange the array to satisfy the heap property)
    for (int i = arrSize / 2 - 1; i >= 0; i--) {
        heapify(arr, arrSize, i); // Build the heap from the bottom up
    }

    // Extract elements one by one from the heap and rebuild the heap
    for (int i = arrSize - 1; i > 0; i--) {
        swapElements(arr[0], arr[i]); // Swap the root (largest element) with the last element
        heapify(arr, i, 0); // Heapify the reduced heap to maintain the heap property
    }
}

// Utility function to print the contents of the array
void printArray(const std::vector<int> &arr) {
    for (int element : arr) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

// Utility function to generate a random integer array
std::vector<int> generateRandomArray(int size, int range) {
    std::vector<int> arr(size);
    for (int &num : arr) {
        num = rand() % range; // Fill with random numbers
    }
    return arr;
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // Initialize random seed

    // Generate an array of random integers
    std::vector<int> data = generateRandomArray(20, 100);

    std::cout << "Original Array:\n";
    printArray(data); // Display the original array

    operationCount = 0; // Reset the operation counter
    heapSort(data); // Sort the array using heap sort

    std::cout << "Sorted Array:\n";
    printArray(data); // Display the sorted array

    std::cout << "Total Operations Count: " << operationCount << std::endl; // Display the operation count

    return 0;
}