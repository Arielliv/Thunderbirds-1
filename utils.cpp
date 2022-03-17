#include "utils.h"

int findInArray(char arr[],int n, char c){
    for (int i = 0; i < n; i++) {
        if (arr[i] == c) {
            return i;
        }
    }
    return -1;
}

int binarySearch(char arr[], int l, int r, char x)
{
    if (r >= l) {
        int mid = l + (r - l) / 2;


        if (arr[mid] == x)
            return mid;


        if (arr[mid] > x) {
            return binarySearch(arr, l, mid - 1, x);
        }


        return binarySearch(arr, mid + 1, r, x);
    }


    return -1;
}
