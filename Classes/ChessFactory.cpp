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
	case 3:
		chess = Yevee::create("Yevee1-front-left.png");
	case 4:
		chess = Charmander::create("Charmander1-front-left.png");
	case 5:
		chess = Squirtle::create("Squirtle1-front-left.png");
	default:
		chess = Chess::create("defualt.png");
		break;
	}
	return chess;
}
