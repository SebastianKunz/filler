#include "window.hpp"
#include "parser.hpp"
#include "draw.hpp"

int main()
{
	Window	window("Skunz Filler", WIN_WIDTH, WIN_HEIGHT);
	Parser	parser;

	parser.readInput();
	Draw draw(parser.getTurns(), window.getWindow(), parser.getTurnCount());
	draw.draw();
	while(!window.isClosed())
	{
		// window.pollEvents();
		draw.pollEvents();
		// draw.draw();
		// SDL_Delay(5000);
	}
}


