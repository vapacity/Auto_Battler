#include "ChessFactory.h"

Chess* ChessFactory::createChessById(int id)
{
	Chess* chess = nullptr;
	switch (id)
	{
	case 0:
		chess = Yevee1::create("Yevee1-back-left.png");
		break;
	case 1:
		chess = Charmander1::create("Charmander1-back-left.png");
		break;
	case 2:
		chess = Squirtle1::create("Squirtle1-back-left.png");
		break;


	case 3:
		chess = Yevee2::create("Yevee1-front-left.png");
		break;
	case 4:
		chess = Charmander2::create("Charmander1-front-left.png");
		break;
	case 5:
		chess = Squirtle2::create("Squirtle1-front-left.png");
		break;


	case 6:
		chess = Yevee3::create("Yevee1-front-right.png");
		break;
	case 7:
		chess = Charmander3::create("Charmander1-front-right.png");
		break;
	case 8:
		chess = Squirtle3::create("Squirtle1-front-right.png");
		break;

	default:
		chess = Chess::create("defualt.png");
		break;
	}
	return chess;
}
