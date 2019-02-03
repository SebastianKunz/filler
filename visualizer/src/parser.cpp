#include "parser.hpp"

Parser::Parser(void)
{
	_turnCount = 0;
	_curTurn.p1Pieces = 0;
	_curTurn.p2Pieces = 0;
}

Parser::~Parser(void){}

std::vector<t_turn>	Parser::getTurns(void) const
{
	return _turns;
}

unsigned int	Parser::getTurnCount(void) const
{
	return _turnCount;
}

void	Parser::printData(void)
{
	std::cout << _player1.name << std::endl;
	std::cout << _player2.name << std::endl;
	for (unsigned int k = 0; k < _turns.size(); k++)
	{
		std::cout << _turns[k].piece.size.y << "," << _turns[k].piece.size.x << std::endl;
		for (unsigned int i = 0; i < _turns[k].piece.map.size(); i++)
			std::cout << _turns[k].piece.map[i] << std::endl;
		std::cout << _turns[k].board.size.y << "," << _turns[k].board.size.x << std::endl;
		for (unsigned int i = 0; i < _turns[k].board.map.size(); i++)
			std::cout << _turns[k].board.map[i] << std::endl;
	}
	std::cout << "Turncount: " << _turnCount << std::endl;
}

void	Parser::readInput(void)
{
	std::string line;

	_getPlayers();
	while (std::getline(std::cin, line))
	{
		if (isdigit(line.at(0)))
			_curTurn.board.map.push_back(line.substr(4));
		else if (line.find("Plateau") != std::string::npos)
			_getSize(&_curTurn.board.size, line);
		else if (line.find("Piece") != std::string::npos)
			_getSize(&_curTurn.piece.size, line);
		else if (line.at(0) == '.' || line.at(0) == '*')
			_curTurn.piece.map.push_back(line);
		else if (line.find("<got") != std::string::npos)
		{
			if (line.find(_player1.sign) != std::string::npos)
				_curTurn.p1Pieces++;
			else
				_curTurn.p2Pieces++;
			_turns.push_back(_curTurn);
			_curTurn.piece.map.clear();
			_curTurn.board.map.clear();
			_turnCount++;
		}
		else if (line.find("==") != std::string::npos)
			break;
	}
}

void	Parser::_getSize(t_point *size, std::string line)
{
	std::vector<std::string> elements;
	std::string elem;

	std::istringstream f(line);
	while (std::getline(f, elem, ' '))
		elements.push_back(elem);
	size->y = atoi(elements[1].c_str());
	size->x = atoi(elements[2].c_str());
	elements.clear();
}

void	Parser::_getPlayers(void)
{
	std::string line;

	while (std::getline(std::cin, line))
	{
		if (line.find("p1") != std::string::npos)
		{
			_player1.name = line.substr(line.find('/'));
			_player1.name.pop_back();
			_player1.sign = 'O';
		}
		if (line.find("p2") != std::string::npos)
		{
			_player2.name = line.substr(line.find('/'));
			_player2.name.pop_back();
			_player2.sign = 'O';
			break;
		}
	}
}