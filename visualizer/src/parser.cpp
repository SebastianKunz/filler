#include "parser.hpp"

Parser::Parser(void)
{
	_info.turnCount = 0;
	_curTurn.p1Pieces = 0;
	_curTurn.p2Pieces = 0;
	_info.maxPiece.x = 0;
	_info.maxPiece.y = 0;
}

Parser::~Parser(void){}

t_info	Parser::getInfo(void) const
{
	return _info;
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
		{
			_getSize(&_curTurn.piece.size, line);
			if (_curTurn.piece.size.x > _info.maxPiece.x)
				_info.maxPiece.x = _curTurn.piece.size.x;
			if (_curTurn.piece.size.y > _info.maxPiece.y)
				_info.maxPiece.y = _curTurn.piece.size.y;
		}
		else if (line.at(0) == '.' || line.at(0) == '*')
			_curTurn.piece.map.push_back(line);
		else if (line.find("<got") != std::string::npos)
		{
			if (line.find(_info.player1.sign) != std::string::npos)
				_curTurn.p1Pieces++;
			else
				_curTurn.p2Pieces++;
			_info.turns.push_back(_curTurn);
			_curTurn.piece.map.clear();
			_curTurn.board.map.clear();
			_info.turnCount++;
		}
		else if (line.find("==") != std::string::npos)
		{
			_info.turns.push_back(_curTurn);
			_curTurn.piece.map.clear();
			_curTurn.board.map.clear();
			_info.turnCount++;
			break;
		}
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
			_info.player1.name = line.substr(line.find_last_of('/') + 1);
			_info.player1.name.pop_back();
			_info.player1.sign = 'O';
		}
		if (line.find("p2") != std::string::npos)
		{
			_info.player2.name = line.substr(line.find_last_of('/') + 1);
			_info.player2.name.pop_back();
			_info.player2.sign = 'X';
			break;
		}
	}
}