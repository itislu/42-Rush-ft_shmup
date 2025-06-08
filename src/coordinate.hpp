#pragma once

struct coordinate {
	int x;
	int y;

	bool operator==(const coordinate& other)
	{
		return x == other.x && y == other.y;
	}

	coordinate operator+(const coordinate& other) const
	{
		return {x + other.x, y + other.y};
	}

	coordinate operator-(const coordinate& other) const
	{
		return {x - other.x, y - other.y};
	}

	coordinate& operator+=(const coordinate& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	coordinate& operator-=(const coordinate& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}
};
