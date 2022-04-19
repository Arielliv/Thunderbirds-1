#include "utils.h"

int findInArray(const char arr[], const int n, const char c){
    for (int i = 0; i < n; i++) {
        if (arr[i] == c) {
            return i;
        }
    }
    return -1;
}

int parseCharToInt(char c) {
    return c - '0';
}

char parseIntToChar(int i) {
    return i + '0';
}