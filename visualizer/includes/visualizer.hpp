#ifndef VISUALIZER_HPP
# define VISUALIZER_HPP

#include <vector>

typedef struct	s_point {
	int			x;
	int			y;
}				t_point;

typedef struct	s_filler {
	std::string name;
	char		sign;
}				t_filler;

typedef struct	s_board {
	std::vector<std::string>	map;
	t_point		size;
}				t_board;

typedef struct	s_turn {
	t_board		board;
	t_board		piece;
}				t_turn;

#endif