#pragma once
#pragma once

#include "color.h"
#include "point.h"
#include "constants.h"
#include "boardUtils.h"
#include "utils.h"
#include <vector>

class BoardGameTool
{
	Point startPoint = Point(1, 1);
	char figure;
	Color color;
	vector<Point> body;
	bool isWithColors = false;
	bool isSilnet = false;
public:
	BoardGameTool() {};
	~BoardGameTool();
	BoardGameTool(char figure, Color color, Point startPoint, bool isWithColors, bool isSilnet);
	virtual BoardGameTool& operator=(const BoardGameTool& b);
	virtual const Point& getCurrentPoint() const;
	virtual const vector<Point>& getCurrentBodyPoints() const;
	virtual void move(const Direction direction, vector<vector<char>>& boardGame);
	virtual void draw(vector<vector<char>>& boardGame) const;
	virtual bool isValidMove(const Direction dir, const vector<vector<char>>& boardGame) const;
	virtual char getFigure() const;
	virtual int getSize() const;
	bool getIsWithColors() const;
	Color getColor() const;
	void pushToBody(Point p);
	const vector<Point>& getBody() const;
	Point getStartPoint() const;
	void setBodyAt(Point p, int index);
};