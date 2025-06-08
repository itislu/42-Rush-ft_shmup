#pragma once

#include <sys/time.h>
#include <time.h>

inline long get_current_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

inline long get_current_time_in_seconds(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec);
}
