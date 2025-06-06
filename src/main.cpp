#include "libftpp/algorithm.hpp"
#include <iostream>
#include <ncurses.h>

extern "C" {
#include "libft/ft_printf.h"
#include "libft/libft.h"
}

int main()
{
	ft_printf("hello from libft: %d\n", (int)ft_max(0, 42));
	std::cout << "hello from libftpp: " << ft::max(0, 42) << '\n';
}
