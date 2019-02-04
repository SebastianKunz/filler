#ifndef PARSER_HPP
# define PARSER_HPP

# include <iostream>
# include <string>
# include <vector>
# include <sstream>

typedef struct	s_point {
	int			x;
	int			y;
}				t_point;

typedef struct	s_board {
	std::vector<std::string>	map;
	t_point		size;
}				t_board;

typedef struct	s_turn {
	t_board		board;
	t_board		piece;
	unsigned int p1Pieces;
	unsigned int p2Pieces;
}				t_turn;

typedef struct	s_player {
	std::string	name;
	char		sign;
}				t_player;

typedef struct	s_info {
	t_player	player1;
	t_player	player2;
	std::vector<t_turn>	turns;
	unsigned int		turnCount;
	t_point		maxPiece;
}				t_info;

class Parser{

	public:
		Parser(void);
		~Parser(void);

		t_info	getInfo(void) const;

		void	readInput(void);

	private:
		void	_getSize(t_point *size, std::string line);
		void	_getPlayers(void);

		t_info	_info;
		t_turn	_curTurn;
};

#endif