#pragma once

#include <vector>

template <typename T>
class Pattern {
public:
	explicit Pattern<T>(const std::vector<T>& pattern)
	    : _pattern(pattern)
	{}

	T next() const
	{
		auto cur_i = _i;
		_i = (_i + 1) % _pattern.size();
		return _pattern[cur_i];
	}

	void reset() const { _i = 0; }

private:
	std::vector<T> _pattern;
	mutable std::vector<T>::size_type _i = 0;
};
