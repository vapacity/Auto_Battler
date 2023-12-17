
#include "Chess.h"
#include"ChessFactory.h"

USING_NS_CC;

Chess* Chess::create()
{
    Chess* chessExample = new (std::nothrow) Chess();
    if (chessExample&& chessExample->init()) {
        chessExample->autorelease();
        return chessExample;
    }
    CC_SAFE_DELETE(chessExample);
    return nullptr;
}

Chess* Chess::create(const std::string&filename)
{
    Chess* chessExample = new (std::nothrow) Chess();
    if (chessExample && chessExample->initWithFile(filename)&&chessExample->init()) {
        chessExample->autorelease();
        return chessExample;
    }
    CC_SAFE_DELETE(chessExample);
    return nullptr;
}

void Chess::deleteChess()
{
    if (this)
        this->removeFromParent();
}

int Chess::getId()
{
    if (this)
        return this->id;
  
    return -1;
}

bool Chess::isInGrid()
{
    return (atGridPosition.x>=0&&atGridPosition.y>=0);
}

bool Chess::isAtSeat()
{
    return atSeatPosition>=0;
}




bool Chess::init()
{
    if (!Node::init()) {
        return false;
    }
    return true;
}

Chess* Chess::upgrade()
{
    auto upChess = ChessFactory::createChessById(this->getId() + 3);
    upChess->atGridPosition = atGridPosition;
    upChess->atSeatPosition = atSeatPosition;
    //以下部分应该在createChessById中构造完成，此函数应该只用来继承其位置信息
    upChess->id = id + 3;
    upChess->setPosition(this->getPosition());
    this->getParent()->addChild(upChess,1);
    return upChess;
}

void Chess::attack()
{
    ;
}


void Chess::moveTo()
{
    ;
}

void Chess::getHurt()
{
    ;
}

void Chess::useSkill()
{
    ;
}

void Chess::getSold()
{
    ;
}
