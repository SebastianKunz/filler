#include "draw.hpp"

Draw::Draw(SDL_Window* window, t_info info) : _info(info)
{
	_turnIdx = 0;
	_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (_renderer == nullptr)
		throw std::runtime_error(std::string("Failed to create Renderer"));

	if (TTF_Init() < 0)
		std::cerr << "error: " << TTF_GetError() << std::endl;

	_fontPlayer = TTF_OpenFont("visualizer/resources/fonts/PTS75F.ttf", 30);
	_fontInfo = TTF_OpenFont("visualizer/resources/fonts/PTS75F.ttf", 25);
	_fontScore = TTF_OpenFont("visualizer/resources/fonts/PTS75F.ttf", 22);
	if (!_fontPlayer || !_fontInfo || !_fontScore)
		std::cerr << "error: " << TTF_GetError() << std::endl;

	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
		std::cerr << "error: img" << std::endl;

	SDL_Surface* surface = IMG_Load("visualizer/resources/img/InfoBar.png");
	if (!surface)
		std::cerr << "Failed to create surface" << std::endl;
	_infoImg = SDL_CreateTextureFromSurface(_renderer, surface);
	if (!_infoImg)
		std::cerr << "Failed to create texture" << std::endl;
	SDL_FreeSurface(surface);

	_infoSpace = WIN_WIDTH * (1 - B_WIDTH);
	_boardSpace = WIN_WIDTH - _infoSpace;
}

Draw::~Draw(void)
{
	SDL_DestroyRenderer(_renderer);
	TTF_CloseFont(_fontPlayer);
	TTF_CloseFont(_fontScore);
	IMG_Quit();
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
	static bool	flag = true;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
				case SDLK_RIGHT:
						_turnIdx++;
						_turnIdx = _turnIdx >= _info.turnCount ? _info.turnCount - 1 : _turnIdx;
						draw();
					break;
				case SDLK_LEFT:
					_turnIdx = _turnIdx == 0 ? 0 : _turnIdx - 1;
					draw();
					break;
				case SDLK_SPACE:
					flag = !flag;
					while (_turnIdx < _info.turnCount && !flag)
					{
						draw();
						pollEvents();
						_turnIdx++;
						if (_turnIdx == _info.turnCount)
							flag = !flag;
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

int		Draw::_getTextWidth(TTF_Font* font, std::string msg)
{
	t_point	size;
	SDL_Color color = {200, 200, 200, 255};
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, msg.c_str(), color);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(_renderer, textSurface);
	SDL_FreeSurface(textSurface);
	SDL_QueryTexture(textTexture, nullptr, nullptr, &size.x, &size.y);

	return size.x;
}

void	Draw::_drawText(int x, int y, std::string msg, TTF_Font* font)
{
	SDL_Color color = {200, 200, 200, 255};
	SDL_Rect textRect = {x, y, 0, 0};
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, msg.c_str(), color);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(_renderer, textSurface);
	SDL_FreeSurface(textSurface);
	SDL_QueryTexture(textTexture, nullptr, nullptr, &textRect.w, &textRect.h);
	SDL_RenderCopy(_renderer, textTexture, nullptr, &textRect);
}

void	Draw::_drawBoard(void) const
{
	if (_info.turns[_turnIdx].board.map.size() == 0)
		return ;

	int width = (WIN_WIDTH * B_WIDTH) / _info.turns[0].board.size.x;
	int height = WIN_HEIGHT * B_HEIGHT / _info.turns[0].board.size.y;
	SDL_Rect rect;
	rect.h = height < width ? height : width;
	rect.w = rect.h;
	int boardWidth = rect.w * _info.turns[0].board.size.x;
	int offsetX = (_boardSpace - boardWidth) / 2 + _infoSpace;
	int offsetY = (WIN_HEIGHT - rect.h * _info.turns[0].board.size.y) / 2 + WIN_HEIGHT * 0.05;
	SDL_SetRenderDrawColor(_renderer, 75, 75, 75, 255);
	SDL_RenderClear(_renderer);
	for (int y = 0; y < _info.turns[_turnIdx].board.size.y; y++)
	{
		rect.y = rect.h * y + offsetY;
		for (int x = 0; x < _info.turns[_turnIdx].board.size.x; x++)
		{
			rect.x = rect.w * x + offsetX;
			if (_info.turns[_turnIdx].board.map[y][x] == 'O')
				SDL_SetRenderDrawColor(_renderer, 180, 0, 0, 255);
			else if (_info.turns[_turnIdx].board.map[y][x] == 'o')
				SDL_SetRenderDrawColor(_renderer, 230, 0, 0, 255);
			else if (_info.turns[_turnIdx].board.map[y][x] == 'X')
				SDL_SetRenderDrawColor(_renderer, 0, 180, 0, 255);
			else if (_info.turns[_turnIdx].board.map[y][x] == 'x')
				SDL_SetRenderDrawColor(_renderer, 0, 230, 0, 255);
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

void	Draw::_drawImage(int x, int y, int w, int h)
{
	SDL_Rect rect = {x, y, w, h};
	SDL_RenderCopy(_renderer, _infoImg, nullptr, &rect);
}

void	Draw::_drawInfo(void)
{
	SDL_Rect rect = {0, 0, 0, 0};
	int height;

	rect.w = WIN_WIDTH * (1 - B_WIDTH);
	rect.h = WIN_HEIGHT;
	SDL_SetRenderDrawColor(_renderer, 50, 50, 50, 255);
	SDL_RenderFillRect(_renderer, &rect);
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
	SDL_RenderDrawLine(_renderer, rect.w, 0, rect.w, rect.h);
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(_renderer, rect.w * 0.1, rect.h / 10, rect.w - rect.w * 0.1, rect.h / 10);
	_drawText(rect.w / 4, rect.h / 20, "Visualizer by Skunz", _fontInfo);
	height =  WIN_WIDTH * P_WIDTH / _info.maxPiece.x * _info.maxPiece.y + (1 - P_HEIGHT) * WIN_HEIGHT;
	_drawImage(0, height, 383, 331);
}

void	Draw::_drawBar(void)
{
	if (_turnIdx == 0)
		return ;
	SDL_Rect rect;

	rect.w = ceilf(WIN_WIDTH / 2 / static_cast<float>(_info.turnCount));
	rect.h = 50;
	rect.y = WIN_HEIGHT * 0.05;
	int sizeP1 = rect.w * _info.turns[_turnIdx - 1].p1Pieces;
	int sizeP2 = rect.w * _info.turns[_turnIdx - 1].p2Pieces;
	SDL_SetRenderDrawColor(_renderer, 180, 0, 0, 255);
	for (unsigned int i = 0; i < _info.turns[_turnIdx - 1].p1Pieces; i ++)
	{
		rect.x = (_boardSpace / 2 - rect.w * i) - rect.w + _infoSpace;
		if (rect.x < _infoSpace + rect.w)
			break;
		SDL_RenderFillRect(_renderer, &rect);
	}
	SDL_SetRenderDrawColor(_renderer, 0, 180, 0, 255);
	for (unsigned int i = 0; i < _info.turns[_turnIdx - 1].p2Pieces; i ++)
	{
		rect.x = _boardSpace / 2 + rect.w * i + _infoSpace;
		if (rect.x > WIN_WIDTH - rect.w * 2)
			break;
		SDL_RenderFillRect(_renderer, &rect);
	}

	if (_boardSpace / 2 - sizeP1 + _infoSpace < _infoSpace + rect.w)
		sizeP1 = _boardSpace / 2 - rect.w;
	if (sizeP2 > _boardSpace / 2 - rect.w * 2)
		sizeP2 = _boardSpace / 2 - rect.w;
	//grid
	_drawGrid(_boardSpace / 2 - sizeP1 + _infoSpace, rect.y, 1, 1, sizeP1, rect.h);
	_drawGrid(_boardSpace / 2 + _infoSpace, rect.y, 1, 1, sizeP2, rect.h);
	//player text
	int textWidthP1 = _getTextWidth(_fontPlayer, _info.player1.name);
	int textWidthP2 = _getTextWidth(_fontPlayer, _info.player2.name);
	if (_boardSpace / 2 - sizeP1 / 2 + _infoSpace + textWidthP1 < _boardSpace / 2 + sizeP2 / 2 + _infoSpace - textWidthP2 / 2)
	{
		_drawText(_boardSpace / 2 - sizeP1 / 2 + _infoSpace - textWidthP1 / 2, rect.y / 2 - 20, _info.player1.name, _fontPlayer);
		_drawText(_boardSpace / 2 + sizeP2 / 2 + _infoSpace - textWidthP2 / 2, rect.y / 2 - 20, _info.player2.name, _fontPlayer);
	}
	//score
	std::string scoreStrP1 = std::to_string(_info.turns[_turnIdx - 1].p1Pieces);
	std::string scoreStrP2 = std::to_string(_info.turns[_turnIdx - 1].p2Pieces);
	textWidthP1 = _getTextWidth(_fontScore, scoreStrP1);
	textWidthP2 = _getTextWidth(_fontScore, scoreStrP2);
	if (textWidthP1 < sizeP1)
		_drawText(_boardSpace / 2 - sizeP1 / 2 + _infoSpace - textWidthP1 / 2, rect.y + rect.h / 4, scoreStrP1, _fontScore);
	if (textWidthP2 < sizeP2)
	_drawText(_boardSpace / 2 + sizeP2 / 2 + _infoSpace - textWidthP2 / 2, rect.y + rect.h / 4, scoreStrP2, _fontScore);
}

void	Draw::_drawPiece(void)
{
	SDL_Rect rect;

	int height = WIN_WIDTH * P_WIDTH / _info.maxPiece.x;
	int width = WIN_HEIGHT * P_HEIGHT / _info.maxPiece.y;
	rect.h = height < width ? height : width;
	rect.w = rect.h;
	for (int y = 0; y < _info.maxPiece.y; y++)
	{
		rect.y = rect.h * y + WIN_HEIGHT * (1 - P_HEIGHT);
		for (int x = 0; x < _info.maxPiece.x; x++)
		{
			rect.x = rect.w * x + (_infoSpace - rect.w * _info.maxPiece.x) / 2;
			if (_info.turns[_turnIdx].piece.size.x > x && _info.turns[_turnIdx].piece.size.y > y && _info.turns[_turnIdx].piece.map[y][x] == '*')
				SDL_SetRenderDrawColor(_renderer, 200, 200, 0, 255);
			else if (_info.turns[_turnIdx].piece.size.x > x && _info.turns[_turnIdx].piece.size.y > y && _info.turns[_turnIdx].piece.map[y][x] == '.')
				SDL_SetRenderDrawColor(_renderer, 75, 75, 75, 255);
			else
				SDL_SetRenderDrawColor(_renderer, 50, 50, 50, 255);
			SDL_RenderFillRect(_renderer, &rect);
		}
	}
	_drawGrid((_infoSpace - rect.w * _info.maxPiece.x) / 2, (1 - P_HEIGHT) * WIN_HEIGHT,
		_info.maxPiece.x, _info.maxPiece.y, rect.w, rect.h);
}
