#include "ChessFactory.h"

Chess* ChessFactory::createChessById(int id)
{
	Chess* chess = nullptr;
	switch (id)
	{
	case 11:
		chess = Yevee::create("Yevee-left-1.png");
		break;
	case 12:
		chess = Charmander::create("Charmander-left-1.png");
		break;
	case 13:
		chess = Squirtle::create("Squirtle-left-1.png");
		break;

	default:
		chess = Chess::create("defualt.png");
		break;
	}
	return chess;
}
