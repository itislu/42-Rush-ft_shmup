#pragma once

struct Coordinate {
	int x;
	int y;

	bool operator==(const Coordinate& other)
	{
		return x == other.x && y == other.y;
	}

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
