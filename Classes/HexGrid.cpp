#include "HexGrid.h"
#define STARTX 200
#define STARTY 200
USING_NS_CC;

HexGrid* HexGrid::create(int Inline,int Incol) {
    HexGrid* grid = new (std::nothrow) HexGrid();
    if (grid && grid->initWithSize(Inline,Incol)) {
        grid->autorelease();
        return grid;
    }
    CC_SAFE_DELETE(grid);
    return nullptr;
}

bool HexGrid::initWithSize(int Inline,int Incol) {
    if (!Node::init()) {
        return false;
    }

    float hexRadius = 0.0f;
    float hexWidth = sqrt(3) * hexRadius;
    float hexHeight = 2 * hexRadius;
    float gap = 50.0f;

    for (int y = 0; y < Incol; ++y) {
        for (int x = 0; x < Inline; ++x) {
            auto cell = HexCell::create();
            this->GridMap.push_back(cell);
            float posX = Limitx=x * (hexWidth + gap) + (y % 2) * (hexWidth / 2 + gap / 2)+STARTX+ hexWidth + gap;
            float posY = Limity=y * (hexHeight * 0.75f + gap)+STARTY+ hexHeight * 0.75f + gap;
            Limitx += hexWidth+gap;
            Limity += hexHeight*0.75f+gap;
            cell->setPosition(posX, posY);
            this->addChild(cell);
        }
    }

    return true;
}

HexCell* HexGrid::getCellAt(const cocos2d::Vec2& position)
{
    CCLOG("Inposition x:%f,y:%f",position.x, position.y);
    //需先设置鼠标可控范围
    if (position.x >= STARTX && position.x <= Limitx && position.y >= STARTY && position.y <= Limity)
        ;
    else
        return nullptr;
    HexCell* closestCell = nullptr;
    float minDistance = std::numeric_limits<float>::max();//强制转换

    for (auto& cell : GridMap)
    {
        float distance = cell->getPosition().distance(position);
        if (distance < minDistance) {
            minDistance = distance;
            closestCell = cell;
        }
    }
    CCLOG("Outposition x:%f,y:%f", closestCell->getPositionX(), closestCell->getPositionY());
    return closestCell;
}
