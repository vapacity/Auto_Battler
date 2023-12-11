#include "Chess.h"
#include "HexGrid.h"
#include "HexCell.h"
USING_NS_CC;

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

bool Chess::init()
{
    if (!Node::init()) {
        return false;
    }
    return true;
}

void Chess::attack()
{
    ;
}

void Chess::grabAndMove()
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
