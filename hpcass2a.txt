#include<bits/stdc++.h>
#include <omp.h>

using namespace std;

void bubble(int arr[],int n)
{
    for(int i = 0;i<n-1;i++)
    {
        int flg = 0;
        #pragma omp parallel for shared(arr,flg)
        for(int j = 0;j<n-i-1;j++)
        {
            if (arr[j] > arr[j + 1]) {
                // Swap elements if they are in the wrong order
                std::swap(arr[j], arr[j + 1]);
                flg = 1;
            }    
        }
        if(flg == 0)
            break;
    }
}

int main()
{
     int arr[] = {5, 6, 1, 4};
    int size = sizeof(arr) / sizeof(arr[0]);

    std::cout << "Original array: ";
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    bubble(arr, size);

    std::cout << "Sorted array:(bubble) ";
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
//     mergeSort(arr, size);
//     std::cout << "Sorted array:(merge) ";
//     for (int i = 0; i < size; i++) {
//         std::cout << arr[i] << " ";
//     }

    return 0;
}