
#include "Chess.h"
#include"ChessFactory.h"

USING_NS_CC;
#define MoveTime 1.0f
#define ATTACK_MOVE 10
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
//�����������Ѱ���ַ����е�һ���ַ���������ɾ��
//���뽨һ��tool.h��cpp��ȫ������
std::string replaceSubstring(const std::string& original, const std::string& toReplace, const std::string& newString) {
    std::string result = original;
    size_t pos = 0;
    while ((pos = result.find(toReplace, pos)) != std::string::npos) {
        result.replace(pos, toReplace.length(), newString);
        // ����λ�ã�ǰ�����ַ����ĳ���
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
    price;//Ǯ��ô�㣿
    name = filename;
    star = 2;
    //�ڴ˴�����ԭ�ȶ���ĸ�������
}

void Chess::upgradeToThird(const std::string& filename)
{
    this->setTexture(filename);
    price;//Ǯ��ô�㣿
    name = filename;
    star = 3;
    //�ڴ˴�����ԭ�ȶ���ĸ�������
}

//Chess* Chess::upgrade()
//{
//    auto upChess = ChessFactory::createChessById(this->getId() + 3);
//    upChess->atGridPosition = atGridPosition;
//    upChess->atSeatPosition = atSeatPosition;
//    //���²���Ӧ����createChessById�й�����ɣ��˺���Ӧ��ֻ�����̳���λ����Ϣ
//    upChess->id = id + 3;
//    upChess->setPosition(this->getPosition());
//    this->getParent()->addChild(upChess,1);
//    return upChess;
//}

int Chess::attack(Chess* attackedChess)
{
    attackTrigTimes++;
    if (attackTrigTimes % (10 - this->attackSpeed) != 0)
    {
        auto delay = DelayTime::create(MoveTime);
        this->actions.pushBack(delay);
        return 0;
    }

    //���Ŀ��λ�ú��Լ���λ��֮�����������
    Vec2 position = attackedChess->getPosition() - this->getPosition();
    position = Vec2(position.x / ATTACK_MOVE, position.y / ATTACK_MOVE);
    //��Ŀ�����ӵķ����ƶ�
    auto moveBackAction = MoveBy::create(0.1f, position);  
    auto moveBackReverseAction = moveBackAction->reverse();  // �ƻ�ԭʼλ��
    this->actions.pushBack(moveBackAction);
    this->actions.pushBack(moveBackReverseAction);
    attackedChess->getHurt(this->ATK);//�öԷ������ӵ�Ѫ
    return this->ATK;
}

MoveTo* Chess::moveTo(Vec2 position)
{
    auto moveTo = cocos2d::MoveTo::create(MoveTime, position);
    return moveTo;
}


void Chess::getHurt(int ATK)
{
    this->health-=ATK;
}

void Chess::useSkill()
{
    ;
}

void Chess::getSold()
{
    ;
}
