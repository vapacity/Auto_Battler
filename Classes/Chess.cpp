
#include "Chess.h"
#include"ChessFactory.h"

USING_NS_CC;
#define MoveTime 1.0f
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

int Chess::getStar()
{
    if (this)
        return this->star;
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




Chess* Chess::createByIdAndStar(int id, int star)
{
    Chess* chess = ChessFactory::createChessById(id);
    while (star > 1)
    {
        chess->upgrade();
        star--;
    }
    return chess;
}

bool Chess::init()
{
    if (!Node::init()) {
        return false;
    }
    return true;
}
//这个函数用于寻找字符串中的一个字符串并将他删除
//我想建一个tool.h和cpp，全局引用
std::string replaceSubstring(const std::string& original, const std::string& toReplace, const std::string& newString) {
    std::string result = original;
    size_t pos = 0;
    while ((pos = result.find(toReplace, pos)) != std::string::npos) {
        result.replace(pos, toReplace.length(), newString);
        // 更新位置，前进新字符串的长度
        pos += newString.length();
    }
    return result;
}
void Chess::upgrade()
{
    if(this->star==1)
        upgradeToSecond(replaceSubstring(name, "1", "2"));
    else if (this->star == 2)
        upgradeToThird(replaceSubstring(name, "2", "3"));
    else
        return;
}

void Chess::upgradeToSecond(const std::string& filename)
{
    this->setTexture(filename);
    price;//钱怎么算？
    name = filename;
    star = 2;
    //在此处更新原先对象的各种数据
}

void Chess::upgradeToThird(const std::string& filename)
{
    this->setTexture(filename);
    price;//钱怎么算？
    name = filename;
    star = 3;
    //在此处更新原先对象的各种数据
}

//Chess* Chess::upgrade()
//{
//    auto upChess = ChessFactory::createChessById(this->getId() + 3);
//    upChess->atGridPosition = atGridPosition;
//    upChess->atSeatPosition = atSeatPosition;
//    //以下部分应该在createChessById中构造完成，此函数应该只用来继承其位置信息
//    upChess->id = id + 3;
//    upChess->setPosition(this->getPosition());
//    this->getParent()->addChild(upChess,1);
//    return upChess;
//}

void Chess::attack()
{
    ;
}

MoveTo* Chess::moveTo(Vec2 position)
{
    auto moveTo = cocos2d::MoveTo::create(MoveTime, position);
    return moveTo;
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
