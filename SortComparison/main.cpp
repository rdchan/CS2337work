#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>
#include <list>

using namespace std;

struct AlgoMetaData{
    unsigned int comparisons = 0;
    unsigned int assignments = 0;
};

AlgoMetaData bubbleSort(int* arr, unsigned int length) {
    AlgoMetaData bubbleData;
    bool made_swaps = true;
    while(made_swaps) {
        made_swaps = false;
        for(unsigned int i = 0; i < length-1; i++) {
            bubbleData.comparisons++;
            if(arr[i] > arr[i+1]) {
                //swap
                made_swaps = true;
                bubbleData.assignments++;
                int tmp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = tmp;
            }
        }
    }
    return bubbleData;

}

AlgoMetaData selectionSort(int* arr, unsigned int length) {
    AlgoMetaData selectionData;
    int min_val;
    unsigned int min_index;
    for(unsigned int i = 0; i < length; i++) {
        min_val = arr[i];
        min_index = i;
        for(unsigned int j = i; j < length; j++) {
            selectionData.comparisons++;
            if(arr[j] < min_val) {
                min_val = arr[j];
                min_index = j;
            }
        }
        if(min_index != i) {
            //swap
            selectionData.assignments++;
            int tmp = arr[i];
            arr[i] = arr[min_index];
            arr[min_index] = tmp;
        }
    }

    return selectionData;
}

AlgoMetaData insertionSort(int* arr, unsigned int length) {
    AlgoMetaData insertionData;

    unsigned int i;
    int key, j;
    for (i = 1; i < length; i++)
    {
        key = arr[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are
        greater than key, to one position ahead
        of their current position */
        while (j >= 0 && arr[j] > key)
        {
            insertionData.comparisons++;
            insertionData.assignments++;
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        insertionData.assignments++;
        arr[j + 1] = key;
    }

    return insertionData;
}

int partition(std::list<int> arr, int left, int right, int pivot, AlgoMetaData &quickSortData) {
    while(left <= right) {
        auto left_pointer = arr.begin();
        advance(left_pointer, left);
        while( *(left_pointer) < pivot) {
            quickSortData.comparisons++;
            advance(left_pointer, 1);
            left++;
        }

        auto right_pointer = arr.begin();
        advance(right_pointer, right);
        while( *(right_pointer) > pivot) {
            quickSortData.comparisons++;
            advance(right_pointer, -1);
            right--;
        }

        quickSortData.comparisons++;
        if(left <= right) {
            quickSortData.assignments++;
            int tmp = *(left_pointer);
            *(left_pointer) = *(right_pointer);
            *(right_pointer) = tmp;
            left++;
            advance(left_pointer, 1);
            right--;
            advance(right_pointer, -1);
        }
    }

    return left;
}
AlgoMetaData quickSort(std::list<int> arr, int left, int right) {
    AlgoMetaData quickSortData;

    if(left >= right) {
        return quickSortData;
    }

    auto pivot_pointer = arr.begin();
    advance(pivot_pointer, (left + (right-left)/2));
    int pivot = *(pivot_pointer);
    int index = partition(arr, left, right, pivot, quickSortData);

    AlgoMetaData left_data = quickSort(arr, left, index-1);
    AlgoMetaData right_data = quickSort(arr, index, right);

    quickSortData.assignments += left_data.assignments + right_data.assignments;
    quickSortData.comparisons += left_data.comparisons + right_data.comparisons;

    return quickSortData;
}

AlgoMetaData ListInsertionSort(std::list<int> arr) {
    AlgoMetaData insertionData;

    unsigned int i;
    int key, j;
    auto it = arr.begin();
    advance(it, 1); //set to 1
    for (i = 1; i < arr.size(); i++)
    {
        //instead of i++...
        advance(it, 1);
        key = *(it);
        j = i - 1;

        /* Move elements of arr[0..i-1], that are
        greater than key, to one position ahead
        of their current position */

        auto it_j = arr.begin();
        advance(it_j, j);
        while (j >= 0 && *(it_j) > key)
        {
            insertionData.comparisons++;
            insertionData.assignments++;
            auto next_ptr = arr.begin();
            advance(next_ptr, j+1);
            *(next_ptr) = *(it_j);
            j = j - 1;
            advance(it_j, -1);
        }
        insertionData.assignments++;
        auto next_ptr = arr.begin();
        advance(next_ptr, j+1);
        *(next_ptr) = key;
    }

    return insertionData;
}

/*
AlgoMetaData merge(std::list<int> arr, int left, int middle, int right, AlgoMetaData &mergeData) {
   int i, j, k, nl, nr;
   //size of left and right sub-arrays
   nl = m-l+1; nr = r-m;
   int larr[nl], rarr[nr];
   //fill left and right sub-arrays
   auto left_pointer = arr.begin();

   for(i = 0; i<nl; i++)
      larr[i] = array[l+i];
   for(j = 0; j<nr; j++)
      rarr[j] = array[m+1+j];
   i = 0; j = 0; k = l;
   //marge temp arrays to real array
   while(i < nl && j<nr) {
      if(larr[i] <= rarr[j]) {
         array[k] = larr[i];
         i++;
      }else{
         array[k] = rarr[j];
         j++;
      }
      k++;
   }
   while(i<nl) {       //extra element in left array
      array[k] = larr[i];
      i++; k++;
   }
   while(j<nr) {     //extra element in right array
      array[k] = rarr[j];
      j++; k++;
   }
}
void mergeSort(std::list<int> arr, int left, int right) {
   int middle;
   if(left < right) {
      middle = left + (right - l)/2;
      // Sort first and second arrays
      mergeSort(arr, left, middle);
      mergeSort(arr, middle+1, right);
      merge(arr, left, middle, right);
   }
}
*/

int main()
{
    cout << "Hello world!" << endl;
    int arr1[5000], arr2[5000], arr3[5000];
    std::list<int> list1, list2, list3;

    std::srand(std::time(nullptr));
    for(int i = 0; i < 5000; i++) {
        int data = (std::rand() % 10000 + 1);
        arr1[i] = data;
        arr2[i] = data;
        arr3[i] = data;
        list1.emplace(list1.begin(), data);
        list2.emplace(list2.begin(), data);
        list3.emplace(list3.begin(), data);
    }

    AlgoMetaData bubbleData = bubbleSort(arr1, 5000);
    cout << "bubble assignments :" << bubbleData.assignments << ": comparisons :" << bubbleData.comparisons << ":" << endl;

    AlgoMetaData selectionData = selectionSort(arr2, 5000);
    cout << "selection assignments :" << selectionData.assignments << ": comparisons :" << selectionData.comparisons << ":" << endl;

    AlgoMetaData insertionData = insertionSort(arr3, 5000);
    cout << "insertion assignments :" << insertionData.assignments << ": comparisons :" << insertionData.comparisons << ":" << endl;

    AlgoMetaData quickData = quickSort(list1, 0, 5000);
    cout << "quick assignments :" << quickData.assignments << ": comparisons :" << quickData.comparisons << ":" << endl;

    AlgoMetaData listInsertionData = ListInsertionSort(list2);
    cout << "insertion(list) assignments :" << listInsertionData.assignments << ": comparisons :" << listInsertionData.comparisons << ":" << endl;


    return 0;
}
