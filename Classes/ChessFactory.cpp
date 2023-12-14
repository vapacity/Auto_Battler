#include "ChessFactory.h"

Chess* ChessFactory::createChessById(int id)
{
	Chess* chess = nullptr;
	switch (id)
	{
	case 0:
		chess = Yevee::create("Yevee1-back-left.png");
		break;
	case 1:
		chess = Charmander::create("Charmander1-back-left.png");
		break;
	case 2:
		chess = Squirtle::create("Squirtle1-back-left.png");
		break;
	default:
		chess = Chess::create("defualt.png");
		break;
	}
	return chess;
}
