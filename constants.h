#pragma once
enum class BoardCellType {
	Empty = '0',
	Wall = '1',
	SmallShip = '2',
	BigShip = '3',
	Exit = '4',
	SmallBlock = '5',
	BigBlock = '6',
	Ghost = '7'
};

enum Bounderies {
	rows = 23,
	cols = 80
};
