#ifndef WINDOW_HPP
# define WINDOW_HPP

# include <iostream>
# include <SDL.h>
# include <stdexcept>

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

# define B_WIDTH 0.7
# define B_HEIGHT 0.8
# define P_WIDTH 0.1
# define P_HEIGHT 0.5

class Window{
	public:
		Window(const std::string, unsigned int, unsigned int);
		~Window(void);

		bool	isClosed(void) const;
		void	init(void);
		void	clear(void) const;

		SDL_Window*	getWindow(void) const;

	private:
		std::string		_title;
		bool			_closed;
		unsigned int	_width;
		unsigned int	_height;

		SDL_Window		*_window;
};

#endif
