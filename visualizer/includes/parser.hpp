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
	unsigned int p1Pieces;
	unsigned int p2Pieces;
}				t_turn;

class Parser{

	public:
		Parser(void);
		~Parser(void);

		std::vector<t_turn>	getTurns(void) const;

		void	readInput(void);
		void	printData(void);
		unsigned int	getTurnCount(void) const;

	private:
		void	_getSize(t_point *size, std::string line);
		void	_getPlayers(void);

		t_filler			_player1;
		t_filler			_player2;
		t_turn				_curTurn;
		std::vector<t_turn>	_turns;
		unsigned int		_turnCount;
};

#endif