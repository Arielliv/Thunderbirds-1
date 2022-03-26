#include "utils.h"

int findInArray(const char arr[], const int n, const char c){
    for (int i = 0; i < n; i++) {
        if (arr[i] == c) {
            return i;
        }
    }
    return -1;
}