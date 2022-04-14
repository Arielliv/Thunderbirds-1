#pragma once
enum class BoardCellType {
	Empty = '0',
	Wall = 'W',
	SmallShip = '@',
	BigShip = '#',
	Exit = '^',
	SmallBlock = '!',
	BigBlock = '~',
	Ghost = '$'
};

enum Bounderies {
	rows = 23,
	cols = 80
};
