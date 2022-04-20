#include "boardUtils.h"

char getValueByIndex(const Point p, const vector<vector<char>>& boardGame) {
    return boardGame[p.getXPoint()][p.getYPoint()];
}

void updateValueByPoints(const vector<Point> points, const int size, const char cellType, vector<vector<char>>& boardGame) {
    for (int i = 0; i < size; i++) {
        setValueByIndex(points[i], cellType, boardGame);
    }
}

void setValueByIndex(const Point p, const char boardCellType, vector<vector<char>>& boardGame) {
    boardGame[p.getYPoint()][p.getXPoint()] = (char)boardCellType;
}