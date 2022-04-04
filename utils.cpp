#include "utils.h"

int findInArray(const char arr[], const int n, const char c){
    for (int i = 0; i < n; i++) {
        if (arr[i] == c) {
            return i;
        }
    }
    return -1;
}

BoardCellType getValueByIndex(const Point p, const char(&boardGame)[Bounderies::rows][Bounderies::cols]) {
    return (BoardCellType)boardGame[p.getXPoint()][p.getYPoint()];
}