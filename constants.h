#pragma once
enum class BoardCellType {
	Empty = '0',
	Wall = 'W',
	SmallShip = '@',
	BigShip = '#',
	Exit = '^',
	HorizontalGhost = '$',
	VerticalGhost = '!'
};

enum Bounderies {
	rows = 23,
	cols = 80
};
