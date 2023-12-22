#ifndef CHESSFACTORY_H
#define CHESSFACTORY_H

#include "cocos2d.h"
#include "Chess.h"
#include "Yevee.h"
#include "Charmander.h"
#include "Squirtle.h"
#include "Bulbasaur.h"
#include "Jigglypuff.h"
#include "Magikarp.h"//
#include "Mewtwo.h"//
#include "Pikachu.h"//
#include "Rabbit.h"//
#include "Rugia.h"//
#include "Snorlax.h"
USING_NS_CC;
class ChessFactory
{
public:
	static Chess* createChessById(int id);
};

#endif