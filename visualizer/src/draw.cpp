#include "draw.hpp"

Draw::Draw(std::vector<t_turn> turns, SDL_Window* window, unsigned int turnCount) :
	_turns(turns), _maxTurns(turnCount)
{
	_turnIdx = 0;
	_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (_renderer == nullptr)
		throw std::runtime_error(std::string("Failed to create Renderer"));
}

Draw::~Draw(void)
{
	SDL_DestroyRenderer(_renderer);
}

void	Draw::draw(void) const
{
	_drawBoard();
	// _drawPiece();
	_drawBar();
	SDL_RenderPresent(_renderer);
}

void	Draw::pollEvents(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
				case SDLK_RIGHT:
					if (_turnIdx < _maxTurns) // fix this please
					{
						// std::cout << _turnIdx << std::endl;
						_turnIdx = _turnIdx == 0 ? 1 : _turnIdx;
						draw();
						_turnIdx++;
					}
					break;
				case SDLK_LEFT:
					// std::cout << _turnIdx << std::endl;
						_turnIdx = _turnIdx == 0 ? 0 : _turnIdx - 1;
						draw();
					break;
				case SDLK_SPACE:
					while (_turnIdx < _maxTurns)
					{
						draw();
						_turnIdx++;
					}
					break;
				case SDLK_r:
					_turnIdx = 0;
					draw();
					break;

				case SDLK_ESCAPE: exit(0);

				default: break;
			}
		}
		else if (event.type == SDL_QUIT)
			exit(0);
	}
}

void	Draw::_drawBoard(void) const
{
	if (_turns[_turnIdx].board.map.size() == 0) // draw board
		return ;

	SDL_Rect rect;
	int height = (WIN_WIDTH * B_WIDTH) / _turns[0].board.size.x;
	int width = WIN_HEIGHT * B_HEIGHT / _turns[0].board.size.y;
	rect.h = height < width ? height : width;
	rect.w = rect.h;
	int offsetY = WIN_HEIGHT * 0.95 - rect.h * _turns[_turnIdx].board.size.y;
	int offsetX = WIN_WIDTH * 0.95 - rect.w * _turns[_turnIdx].board.size.x;
	SDL_SetRenderDrawColor(_renderer, 100, 100, 100, 255);
	SDL_RenderClear(_renderer);
	for (int y = 0; y < _turns[_turnIdx].board.size.y; y++)
	{
		rect.y = rect.h * y + offsetY;
		for (int x = 0; x < _turns[_turnIdx].board.size.x; x++)
		{
			rect.x = rect.w * x + offsetX;
			if (_turns[_turnIdx].board.map[y][x] == 'O')
				SDL_SetRenderDrawColor(_renderer, 200, 0, 0, 255);
			else if (_turns[_turnIdx].board.map[y][x] == 'o')
				SDL_SetRenderDrawColor(_renderer, 250, 0, 0, 255);
			else if (_turns[_turnIdx].board.map[y][x] == 'X')
				SDL_SetRenderDrawColor(_renderer, 0, 200, 0, 255);
			else if (_turns[_turnIdx].board.map[y][x] == 'x')
				SDL_SetRenderDrawColor(_renderer, 0, 250, 0, 255);
			else
				SDL_SetRenderDrawColor(_renderer, 50, 50, 50, 255);
			SDL_RenderFillRect(_renderer, &rect);
		}
	}
	_drawGrid(offsetX, offsetY,
		_turns[_turnIdx].board.size.x, _turns[_turnIdx].board.size.y, rect.w, rect.h);
}

void	Draw::_drawGrid(int startX, int startY, int sizeX, int sizeY, int padW, int padH) const
{
	int initialX = startX;
	int initialY = startY;
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
	for (int x = 0; x < sizeX + 1; x++)
	{
		startX = initialX + padW * x;
		SDL_RenderDrawLine(_renderer, startX, startY, startX, startY + padH * sizeY);
	}
	for (int y = 0; y < sizeY + 1; y++)
	{
		startY = initialY + padH * y;
		SDL_RenderDrawLine(_renderer, initialX, startY, initialX + padW * sizeX, startY);
	}
}

void	Draw::_drawBar(void) const
{
	if (_turnIdx == 0)
		return ;
	SDL_Rect rect;

	rect.w = ceilf(WIN_WIDTH / 2 / static_cast<float>(_maxTurns));
	rect.h = rect.w * 10;
	rect.x = 0;
	rect.y = WIN_HEIGHT * 0.05;
	std::cout << "P1 placed: " << _turns[_turnIdx].p1Pieces << std::endl;
	std::cout << "P2 placed: " << _turns[_turnIdx].p2Pieces << std::endl;
	SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
	for (unsigned int i = 0; i < _turns[_turnIdx - 1].p1Pieces; i ++)
	{
		rect.x = (WIN_WIDTH / 2 - rect.w * i) - rect.w;
		SDL_RenderFillRect(_renderer, &rect);
	}
	SDL_SetRenderDrawColor(_renderer, 0, 255, 0, 255);
	for (unsigned int i = 0; i < _turns[_turnIdx - 1].p2Pieces; i ++)
	{
		rect.x = WIN_WIDTH / 2 + rect.w * i;
		SDL_RenderFillRect(_renderer, &rect);
	}
}

void	Draw::_drawPiece(void) const
{
	SDL_Rect rect;

	rect.w = WIN_WIDTH * P_WIDTH / _turns[_turnIdx].piece.size.x;
	// rect.h = WIN_HEIGHT * P_HEIGHT / _turns[_turnIdx].piece.size.y;
	rect.h = rect.w;
	for (int y = 0; y < _turns[_turnIdx].piece.size.y; y++)
	{
		rect.y = rect.h * y + WIN_HEIGHT * P_HEIGHT / 2;
		for (int x = 0; x < _turns[_turnIdx].piece.size.x; x++)
		{
			rect.x = rect.w * x + WIN_WIDTH * P_WIDTH / 2;
			if (_turns[_turnIdx].piece.map[y][x] == '*')
				SDL_SetRenderDrawColor(_renderer, 250, 250, 66, 255);
			else
				SDL_SetRenderDrawColor(_renderer, 0, 255, 255, 255);
			SDL_RenderFillRect(_renderer, &rect);
		}
	}
	_drawGrid(WIN_WIDTH * P_WIDTH / 2, WIN_HEIGHT * P_HEIGHT / 2,
		_turns[_turnIdx].piece.size.x, _turns[_turnIdx].piece.size.y, rect.w, rect.h);
}

void	Draw::_clear(void) const
{
	SDL_SetRenderDrawColor(_renderer, 100, 100, 100, 255);
	SDL_RenderClear(_renderer);
}