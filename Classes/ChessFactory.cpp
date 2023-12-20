#include "ChessFactory.h"

Chess* ChessFactory::createChessById(int id)
{
	Chess* chess = nullptr;
	switch (id)
	{
	case 0:
		chess = Yevee::create("Yevee-left-1.png");
		break;
	case 1:
		chess = Charmander::create("Charmander-left-1.png");
		break;
	case 2:
		chess = Squirtle::create("Squirtle-left-1.png");
		break;

	default:
		chess = Chess::create("defualt.png");
		break;
	}
	return chess;
}
