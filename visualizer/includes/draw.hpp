#ifndef DRAW_HPP
# define DRAW_HPP

# include "window.hpp"
# include "parser.hpp"
# include <SDL_ttf.h>

# define B_WIDTH 0.8
# define B_HEIGHT 0.8
# define P_WIDTH 0.1
# define P_HEIGHT 0.5

class Draw {
	public:
		Draw(SDL_Window*, t_info);
		~Draw(void);
		void	draw(void);
		void	pollEvents(void);

	private:
		void	_drawText(int, int, std::string);

		void	_drawBoard(void) const;
		void	_drawGrid(int, int, int, int, int, int) const;
		void	_drawInfo(void) const;
		void	_drawPiece(void) const;
		void	_drawBar(void);

		SDL_Renderer*	_renderer;
		TTF_Font*		_font;
		unsigned int	_turnIdx;
		t_info			_info;

		int				_boardSpace;
		int				_infoSpace;
};

#endif
