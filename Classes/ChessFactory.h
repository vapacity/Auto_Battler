#ifndef CHESSFACTORY_H
#define CHESSFACTORY_H

#include "cocos2d.h"
#include "Chess.h"
#include "Yevee.h"
#include "Charmander.h"
#include "Squirtle.h"
USING_NS_CC;
class ChessFactory
{
public:
	static Chess* createChessById(int id);
};

#endif