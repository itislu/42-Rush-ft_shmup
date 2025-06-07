#pragma once

struct Coordinate {
	int x = 0;
	int y = 0;

	Coordinate operator+(const Coordinate& other) const
	{
		return {x + other.x, y + other.y};
	}

	Coordinate operator-(const Coordinate& other) const
	{
		return {x - other.x, y - other.y};
	}

	Coordinate& operator+=(const Coordinate& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	Coordinate& operator-=(const Coordinate& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}
};
