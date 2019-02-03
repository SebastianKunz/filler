#include "window.hpp"

Window::Window(const std::string title, unsigned int width, unsigned int height) :
	_title(title), _width(width), _height(height)
{
	_window = nullptr;
	try
	{
		init();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		_closed = true;
	}
}

Window::~Window(void)
{
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

bool	Window::isClosed(void) const
{
	return _closed;
}

SDL_Window*	Window::getWindow(void) const
{
	return _window;
}

void	Window::init(void)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		throw std::runtime_error(std::string("Failed to initalize!"));

	_window = SDL_CreateWindow(
		_title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		_width, _height,
		0
	);

	if (_window == nullptr)
		throw std::runtime_error(std::string("Failed to create Window"));
}

