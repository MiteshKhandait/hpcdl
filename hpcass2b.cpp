#include<bits/stdc++.h>
#include <omp.h>
using namespace std;

void merge(int arr[], int left[], int leftSize, int right[], int rightSize) {
    int i = 0, j = 0, k = 0;
    int* merged = new int[leftSize + rightSize];

    while (i < leftSize && j < rightSize) {
        if (left[i] <= right[j]) {
            merged[k] = left[i];
            i++;
        } else {
            merged[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < leftSize) {
        merged[k] = left[i];
        i++;
        k++;
    }

    while (j < rightSize) {
        merged[k] = right[j];
        j++;
        k++;
    }

    // Copy the merged array back to the original array
    for (i = 0; i < leftSize + rightSize; i++) {
        arr[i] = merged[i];
    }

    delete[] merged;
}

void mergeSort(int arr[], int size) {
    if (size < 2) {
        return;
    }

    int mid = size / 2;
    int* left = new int[mid];
    int* right = new int[size - mid];

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            mergeSort(arr, mid);
        }
        #pragma omp section
        {
            mergeSort(arr + mid, size - mid);
        }
    }

    merge(arr, arr, mid, arr + mid, size - mid);

    delete[] left;
    delete[] right;
}

int main()
{
     int arr[] = {9, 2, 7, 1, 5, 6, 8, 4, 3};
    int size = sizeof(arr) / sizeof(arr[0]);

    std::cout << "Original array: ";
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    // bubble(arr, size);

    // std::cout << "Sorted array:(bubble) ";
    // for (int i = 0; i < size; i++) {
    //     std::cout << arr[i] << " ";
    // }
    std::cout << std::endl;
    mergeSort(arr, size);
    std::cout << "Sorted array:(merge) ";
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }

    return 0;
}