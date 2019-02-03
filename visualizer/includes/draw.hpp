#ifndef DRAW_HPP
# define DRAW_HPP

# include "window.hpp"
# include "parser.hpp"

class Draw{
	public:
		Draw(std::vector<t_turn>, SDL_Window*, unsigned int);
		~Draw(void);
		void	draw(void) const;
		void	pollEvents(void);

	private:
		void	_drawBoard(void) const;
		void	_drawGrid(int, int, int, int, int, int) const;
		void	_drawPiece(void) const;
		void	_drawBar(void) const;
		void	_clear(void) const;

		std::vector<t_turn>	_turns;
		SDL_Renderer*	_renderer;
		unsigned int	_turnIdx;
		unsigned int	_maxTurns;
};

#endif
