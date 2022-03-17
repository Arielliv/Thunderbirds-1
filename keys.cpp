#include "keys.h"

char keyboardDirectionKeys[4] = { 'w','x','a','d'};
int directionKeys[4] = { 0,1,2,3 };

char keyboardSwitchKeys[2] = { 's','b' };
int switchKeys[2] = { 4,5 };

Direction getDirectionByKey(char key) {
    int n = sizeof(keyboardDirectionKeys) / sizeof(keyboardDirectionKeys[0]);
    int index = findInArray(keyboardDirectionKeys, n, key);
    if (index != -1) {
        return (Direction)directionKeys[index];
    }
    return Direction::Right;
}

Keys getKeyByChar(char key) {
    int n = sizeof(keyboardSwitchKeys) / sizeof(keyboardSwitchKeys[0]);
    int index = findInArray(keyboardSwitchKeys, n, key);
    if (index != -1) {
        return (Keys)switchKeys[index];
    }

    return Keys::None;
}