#include "utils.h"

int binarySearch(char arr[], int l, int r, char x)
{
    if (r >= l) {
        int mid = l + (r - l) / 2;


        if (arr[mid] == x)
            return mid;


        if (arr[mid] > x)
            return binarySearch(arr, l, mid - 1, x);


        return binarySearch(arr, mid + 1, r, x);
    }


    return -1;
}
