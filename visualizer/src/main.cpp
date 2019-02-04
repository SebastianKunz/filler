#include "window.hpp"
#include "parser.hpp"
#include "draw.hpp"

int main()
{
	Window	window("Skunz Filler", WIN_WIDTH, WIN_HEIGHT);
	Parser	parser;

	parser.readInput();
	Draw draw(window.getWindow(), parser.getInfo());
	draw.draw();
	while(!window.isClosed())
	{
		draw.pollEvents();
	}
}


