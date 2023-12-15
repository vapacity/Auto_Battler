
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
        this->removeFromParentAndCleanup(1);
}

int Chess::getId()
{
    if (this)
        return this->id;
  
    return -1;
}


bool Chess::init()
{
    if (!Node::init()) {
        return false;
    }
    return true;
}

void Chess::upgrade()
{
    auto upChess = ChessFactory::createChessById(this->getId() + 3);
    upChess->atCell = atCell;
    upChess->atGridPosition = atGridPosition;
    upChess->atSeat = atSeat;
    //���²���Ӧ����createChessById�й�����ɣ��˺���Ӧ��ֻ�����̳���λ����Ϣ
    upChess->id = id + 3;
    upChess->setPosition(this->getPosition());
    this->getParent()->addChild(upChess,1);

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
