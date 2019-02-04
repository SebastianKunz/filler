#ifndef WINDOW_HPP
# define WINDOW_HPP

# include <iostream>
# include <SDL.h>
# include <stdexcept>

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

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
