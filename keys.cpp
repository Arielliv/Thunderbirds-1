#include "keys.h"

const char keyboardDirectionKeys[4] = { 'w','x','a','d'};
const int directionKeys[4] = { 0,1,2,3 };

const char keyboardSwitchKeys[2] = { 's','b' };
const int switchKeys[2] = { 4,5 };

Direction getDirectionByKey(const char key) {
    int n = sizeof(keyboardDirectionKeys) / sizeof(keyboardDirectionKeys[0]);
    int index = findInArray(keyboardDirectionKeys, n, tolower(key));
    if (index != -1) {
        return (Direction)directionKeys[index];
    }
    return Direction::Right;
}

Keys getKeyByChar(const char key) {
    int n = sizeof(keyboardSwitchKeys) / sizeof(keyboardSwitchKeys[0]);
    int index = findInArray(keyboardSwitchKeys, n, tolower(key));
    if (index != -1) {
        return (Keys)switchKeys[index];
    }

    return Keys::None;
}