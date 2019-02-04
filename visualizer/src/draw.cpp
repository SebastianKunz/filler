#include "draw.hpp"

Draw::Draw(SDL_Window* window, t_info info) : _info(info)
{
	_turnIdx = 0;
	_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (_renderer == nullptr)
		throw std::runtime_error(std::string("Failed to create Renderer"));

	if (TTF_Init() < 0)
		std::cerr << "error: " << TTF_GetError() << std::endl;

	_font = TTF_OpenFont("fonts/Arial.ttf", 50);
	if (!_font)
		std::cerr << "error: " << TTF_GetError() << std::endl;

	_infoSpace = WIN_WIDTH * (1 - B_WIDTH);
	_boardSpace = WIN_WIDTH - _infoSpace;
}

Draw::~Draw(void)
{
	SDL_DestroyRenderer(_renderer);
}


void	Draw::draw(void)
{
	_drawBoard();
	_drawInfo();
	_drawPiece();
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
					if (_turnIdx < _info.turnCount) // fix this please
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
					while (_turnIdx < _info.turnCount)
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

void	Draw::_drawText(int x, int y, std::string msg)
{
	SDL_Rect	rect;
	SDL_Color color = {255, 255, 255, 255};
	rect.x = x;
	rect.y = y;
	SDL_Surface* textSurface = TTF_RenderText_Blended(_font, msg.c_str(), color);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(_renderer, textSurface);
	SDL_QueryTexture(textTexture, nullptr, nullptr, &rect.w, &rect.h);
	SDL_RenderCopy(_renderer, textTexture, nullptr, &rect);
}

void	Draw::_drawBoard(void) const
{
	if (_info.turns[_turnIdx].board.map.size() == 0) // draw board
		return ;

	int height = (WIN_WIDTH * B_WIDTH) / _info.turns[0].board.size.x;
	int width = WIN_HEIGHT * B_HEIGHT / _info.turns[0].board.size.y;
	SDL_Rect rect;
	rect.h = height < width ? height : width;
	rect.w = rect.h;
	int boardWidth = rect.w * _info.turns[0].board.size.x;
	int offsetX = (_boardSpace - boardWidth) / 2 + _infoSpace;
	int offsetY = (WIN_HEIGHT - rect.h * _info.turns[0].board.size.y) / 2 + WIN_HEIGHT * 0.05;
	SDL_SetRenderDrawColor(_renderer, 100, 100, 100, 255);
	SDL_RenderClear(_renderer);
	for (int y = 0; y < _info.turns[_turnIdx].board.size.y; y++)
	{
		rect.y = rect.h * y + offsetY;
		for (int x = 0; x < _info.turns[_turnIdx].board.size.x; x++)
		{
			rect.x = rect.w * x + offsetX;
			if (_info.turns[_turnIdx].board.map[y][x] == 'O')
				SDL_SetRenderDrawColor(_renderer, 200, 0, 0, 255);
			else if (_info.turns[_turnIdx].board.map[y][x] == 'o')
				SDL_SetRenderDrawColor(_renderer, 250, 0, 0, 255);
			else if (_info.turns[_turnIdx].board.map[y][x] == 'X')
				SDL_SetRenderDrawColor(_renderer, 0, 200, 0, 255);
			else if (_info.turns[_turnIdx].board.map[y][x] == 'x')
				SDL_SetRenderDrawColor(_renderer, 0, 250, 0, 255);
			else
				SDL_SetRenderDrawColor(_renderer, 50, 50, 50, 255);
			SDL_RenderFillRect(_renderer, &rect);
		}
	}
	_drawGrid(offsetX, offsetY,
		_info.turns[_turnIdx].board.size.x, _info.turns[_turnIdx].board.size.y, rect.w, rect.h);
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

void	Draw::_drawInfo(void) const
{
	SDL_Rect rect;

	rect.w = WIN_WIDTH * (1 - B_WIDTH);
	rect.h = WIN_HEIGHT;
	rect.x = 0;
	rect.y = 0;
	SDL_SetRenderDrawColor(_renderer, 50, 50, 50, 255);
	SDL_RenderFillRect(_renderer, &rect);
}

void	Draw::_drawBar(void)
{
	if (_turnIdx == 0)
		return ;
	SDL_Rect rect;

	rect.w = ceilf(WIN_WIDTH / 2 / static_cast<float>(_info.turnCount));
	rect.h = 50; //dynamic plz
	rect.y = WIN_HEIGHT * 0.05;
	int sizeP1 = rect.w * _info.turns[_turnIdx - 1].p1Pieces;
	int sizeP2 = rect.w * _info.turns[_turnIdx - 1].p2Pieces;
	SDL_SetRenderDrawColor(_renderer, 200, 0, 0, 255);
	for (unsigned int i = 0; i < _info.turns[_turnIdx - 1].p1Pieces; i ++)
	{
		rect.x = (_boardSpace / 2 - rect.w * i) - rect.w + _infoSpace;
		SDL_RenderFillRect(_renderer, &rect);
	}
	SDL_SetRenderDrawColor(_renderer, 0, 200, 0, 255);
	for (unsigned int i = 0; i < _info.turns[_turnIdx - 1].p2Pieces; i ++)
	{
		rect.x = _boardSpace / 2 + rect.w * i + _infoSpace;
		SDL_RenderFillRect(_renderer, &rect);
	}
	_drawGrid(_boardSpace / 2 - sizeP1 + _infoSpace, rect.y, 1, 1, sizeP1, rect.h);
	_drawText(_boardSpace / 2 - sizeP1 + _infoSpace, 0, _info.player1.name);
	_drawText(_boardSpace / 2 + _infoSpace, rect.y, std::to_string(_info.turns[_turnIdx].p1Pieces));
	_drawGrid(_boardSpace / 2 + _infoSpace, rect.y, 1, 1, sizeP2, rect.h);
	_drawText(_boardSpace / 2 + _infoSpace, 0, _info.player2.name);
	_drawText(_boardSpace / 2 + _infoSpace, rect.y, std::to_string(_info.turns[_turnIdx].p2Pieces));
}

void	Draw::_drawPiece(void) const
{
	SDL_Rect rect;

	int height = (WIN_WIDTH * P_WIDTH) / _info.maxPiece.x;
	int width = WIN_HEIGHT * P_HEIGHT / _info.maxPiece.y;
	rect.h = height < width ? height : width;
	rect.w = rect.h;
	for (int y = 0; y < _info.maxPiece.y; y++)
	{
		rect.y = rect.h * y + WIN_HEIGHT * P_HEIGHT / 2;
		for (int x = 0; x < _info.maxPiece.x; x++)
		{
			rect.x = rect.w * x + WIN_WIDTH * P_WIDTH / 2;
			if (_info.turns[_turnIdx].piece.size.x > x && _info.turns[_turnIdx].piece.size.y > y && _info.turns[_turnIdx].piece.map[y][x] == '*')
				SDL_SetRenderDrawColor(_renderer, 250, 250, 66, 255);
			else if (_info.turns[_turnIdx].piece.size.x > x && _info.turns[_turnIdx].piece.size.y > y && _info.turns[_turnIdx].piece.map[y][x] == '.')
				SDL_SetRenderDrawColor(_renderer, 0, 255, 255, 255);
			else
				SDL_SetRenderDrawColor(_renderer, 125, 125, 125, 255);
			SDL_RenderFillRect(_renderer, &rect);
		}
	}
	_drawGrid(WIN_WIDTH * P_WIDTH / 2, WIN_HEIGHT * P_HEIGHT / 2,
		_info.maxPiece.x, _info.maxPiece.y, rect.w, rect.h);
}
