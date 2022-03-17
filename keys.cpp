#include "keys.h"

char keyboardKeys[6] = { 'w','x','a','d','s','b' };

int keys[6] = { 0,1,2,3,4,5 };

Direction getDirectionByKey(char key) {
    int index = binarySearch(keyboardKeys, 0, 5, key);
    if (index != -1) {
        return (Direction)keys[index];
    }
    return Direction::Right;
}