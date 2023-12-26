#include "cocos2d.h"
#include "Chess.h"
#include"ChessFactory.h"
#include "GridMap.h"
USING_NS_CC; 
#define MoveTime 1.0f
#define ATTACK_MOVE 5
Chess* Chess::create()
{
    Chess* chessExample = new (std::nothrow) Chess();
    if (chessExample && chessExample->init()) {
        chessExample->autorelease();
        return chessExample;
    }
    CC_SAFE_DELETE(chessExample);
    return nullptr;
}

Chess* Chess::create(const std::string& filename)
{
    Chess* chessExample = new (std::nothrow) Chess();
    if (chessExample && chessExample->initWithFile(filename) && chessExample->init()) {
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
    return (atGridPosition.x >= 0 && atGridPosition.y >= 0);
}

bool Chess::isAtSeat()
{
    return atSeatPosition >= 0;
}

Chess* Chess::createByIdAndStar(int id, int star)
{
    Chess* chess = ChessFactory::createChessById(id);
    while (star > 1)
    {
        chess->upgrade();
        star--;//////////////////////
    }
    chess->maxHP = chess->health;
    chess->initHealthBar();
    chess->initBlueBar();
    return chess;
}

bool Chess::init()
{
    if (!Node::init()) {
        return false;
    }
    //this->initHealthBar();
    //this->initBlueBar();
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
    if (this->star == 1)
        upgradeToSecond(replaceSubstring(name, "1", "2"));
    else if (this->star == 2)
        upgradeToThird(replaceSubstring(name, "2", "3"));
    else
        return;
}

void Chess::upgradeToSecond(const std::string& filename)
{
    this->setTexture(filename);
    this->setScale(SET_SCALE * 1.25);
    price=price*3-1;//钱
    name = filename;
    star = 2;
    //在此处更新原先对象的各种数据
    ATK += growATK;
    health += growHP;
}

void Chess::upgradeToThird(const std::string& filename)
{
    this->setTexture(filename);
    this->setScale(SET_SCALE * 1.5);
    price = price * 3 - 1;//钱
    name = filename;
    star = 3;
    //在此处更新原先对象的各种数据
    ATK += growATK;
    health += growHP;
}


void Chess::reverseImg()
{
    this->setScaleX(this->getScaleX() * -1);
}

void Chess::moveAction(GridMap* gridMap)
{
    HexCell* fromCell = gridMap->getCellAtPosition(atGridPosition);
    HexCell* toCell = gridMap->FindBattle(this, fromCell);
    //获得路径
    Vector<HexCell*> movePath;
    gridMap->FindPath(movePath, this, fromCell, toCell, attackRange);
    if (movePath.size() <= 0)
        return;
    //让开始的移动位置停止被预定，移动路上的棋子开始被预定
    fromCell->isBooked = false;
    movePath.at(0)->isBooked = true;
    auto targetPosition = movePath.at(0)->getPosition();
    auto distance = targetPosition.distance(this->getPosition());

    auto move_Action = MoveTo::create(distance / (moveSpeed * 100), targetPosition);
    auto callback = CallFunc::create([=]() {
        // 动画完成后的回调,将棋子放置到新的位置
        gridMap->addChessToGrid(this, movePath.at(0));
        gridMap->removeChessOfGrid(fromCell);
        //注意回调函数中需要重新设置book的位置
        fromCell->isBooked = false;
        movePath.at(0)->isBooked = true;
        isAnimationPlaying = false;
        this->changeState(Idle); // 或其他状态
        });

    auto sequence = Sequence::create(move_Action, callback, nullptr);
    this->runAction(sequence);
    isAnimationPlaying = true;
}

void Chess::attackAction(GridMap* gridMap)
{
    //先获得攻击对象
            //HexCell* toCell = gridMap->FindBattle(this, gridMap->getCellAtPosition(atGridPosition));
    Vector<HexCell*>enemyChessAround;
    bool findEnemy = isEnemyInAttackRange(gridMap, enemyChessAround);
    int enemyChess = enemyChessAround.size();//enemyChessAround这是获得了所有的攻击范围内的敌方棋子
    //用一个Vector存储所有的敌方棋子是便于后续群体攻击
    //为空说明对面死完了
    if (enemyChess == 0)
    {
        changeState(Idle);
        return;
    }
    Chess* attackObject = enemyChessAround.at(0)->chessInGrid;
    //当前能释放技能
    if (this->enable_skill) {
        useSkill();
    }
    
    //回调函数对目标产生伤害
    auto callback = CallFunc::create([=]() {
        // 动画完成后的回调,对目标实际造成伤害
        attackObject->getHurt(ATK);
        if (attackObject->health <= 0) 
            attackObject->changeState(Dead);
        //蓝条,放技能时不变
        if(!enable_skill)
        {
            this->currentBlueBar += 5;
            float percentage_blue = 100.0 * currentBlueBar / this->blueBar;
            if (currentBlueBar > this->blueBar)
            {
                this->enable_skill = true;
                percentage_blue = 100.0f;
            }
            bluebar->setPercentage(percentage_blue);
        }

        isAnimationPlaying = false;
        this->changeState(Idle); // 或其他状态
        });
    //回调函数对目标产生伤害

    if(isMelee==1){
        //播放对攻击对象,设想是顶一下,远程目标需要修改
        Vec2 position = attackObject->getPosition() - this->getPosition();
        position = Vec2(position.x / ATTACK_MOVE, position.y / ATTACK_MOVE);

        float attackDuration = 1.0f / (10 * attackSpeed);
        auto moveBackAction = MoveBy::create(attackDuration, position);
        auto moveBackReverseAction = moveBackAction->reverse();  // 移回原始位置
        auto sequence1 = Sequence::create(moveBackAction, moveBackReverseAction, callback, nullptr);
        this->runAction(sequence1);
    }
    else {
        auto bullet = Sprite::create();
        bullet->setTexture("SliderNode_Normal.png");
        this->getParent()->addChild(bullet);
        bullet->setPosition(this->getPosition());
        bullet->setScale(0.5);
        bullet->setZOrder(2);
        Vec2 position = attackObject->getPosition() - this->getPosition();
        float attackDuration = 1.0f / (10 * attackSpeed);
        auto moveBackAction = MoveBy::create(attackDuration, position);
        auto fadeOut = FadeOut::create(0.0001f);
        auto sequence2 = Sequence::create(moveBackAction, fadeOut, callback, nullptr);
        bullet->runAction(sequence2);
    }
    isAnimationPlaying = true;
    
}

void Chess::deadAction(GridMap* gridMap)
{
    if (isAnimationPlaying) {
        this->stopAllActions();
    }

    // 处理死亡逻辑
    auto fadeOut = FadeOut::create(0.3f);

    // 创建Sequence动作，包含淡出动作和回调函数（移除节点的逻辑）
    auto sequence = Sequence::create(
        fadeOut,
        CallFunc::create([this, gridMap]() {
            //this->removeFromParentAndCleanup(true); // 移除并执行清理操作
            }),
        nullptr
                );

    // 对角色、血条和蓝条分别应用独立的Sequence动作
    this->runAction(fadeOut);
    //this->healthBar->runAction(fadeOut);
    //this->bluebar->runAction(fadeOut);
    gridMap->removeChessOfGrid(gridMap->getCellAtPosition(this->atGridPosition));
    this->removeFromParentAndCleanup(true);
}


void Chess::getBlood()
{

}


void Chess::getHurt(int ATK)
{
    this->health -= ATK;
    float percentage_health = 100.0 * health / maxHP;
    if (percentage_health < 0)
        percentage_health = 0;
    healthBar->setPercentage(percentage_health);

    if(!enable_skill)
    {
        this->currentBlueBar += 5;
        float percentage_blue = 100.0 * currentBlueBar / this->blueBar;
        if (currentBlueBar > this->blueBar)
        {
            this->enable_skill = true;
            percentage_blue = 100.0f;
        }
        bluebar->setPercentage(percentage_blue);
    }
    // 可创建掉血动画，但不必要 
}

void Chess::useSkill()
{
    CCLOG("USESKILL");

}

void Chess::updateInBattle(float dt, GridMap* gridMap)
{
    switch (currentState) {
    case Idle: {
        //检查是否有可攻击的敌人//////////////////
        Vector<HexCell*>a;
        if (isEnemyInAttackRange(gridMap, a))
            // 如果有，切换到攻击状态
            changeState(Attacking);
        else
            // 如果没有，尝试移动
            changeState(Moving);
        break;
    }
    case Moving: {
        // 执行移动逻辑
        // 到达目的地后，切换到空闲或攻击状态

        if (!isAnimationPlaying) {//执行move逻辑的前提是不能播放动画
            moveAction(gridMap);
        }
        break;
    }
    case Attacking: {
        if (!isAnimationPlaying)//只有在非播放动画时调用
        {
            //攻击动作
            attackAction(gridMap);
        }
        break;
    }
    case Dead: {
        deadAction(gridMap);

        break;
    }
    }
}

void Chess::changeState(State newState)
{
    if (currentState == newState) return; // 状态未改变
    currentState = newState;
}
Vector<HexCell*> getNeighbors(HexCell* cell, GridMap* gridMap) {
    Vector<HexCell*> neighbors;
    int x = cell->coordinateInBoard.x;
    int y = cell->coordinateInBoard.y;

    // 这些是偶数行的相邻格子
    Vec2 evenOffsets[6] = { {+1,  0}, { 0, -1}, {-1, -1},
                           {-1,  0}, {-1, +1}, { 0, +1} };
    // 这些是奇数行的相邻格子
    Vec2 oddOffsets[6] = { {+1,  0}, {+1, -1}, { 0, -1},
                           {-1,  0}, { 0, +1}, {+1, +1} };

    for (int i = 0; i < 6; ++i) {
        Vec2 offset = (y % 2 == 0) ? evenOffsets[i] : oddOffsets[i];
        Vec2 neighborCoord = Vec2(x + offset.x, y + offset.y);
        if (neighborCoord.x >= 0 && neighborCoord.x < NUM_COLUMN && neighborCoord.y >= 0 && neighborCoord.y < NUM_LINE)
            neighbors.pushBack(gridMap->getCellAtPosition(neighborCoord));
    }

    return neighbors;
}

bool Chess::isEnemyInAttackRange(GridMap* gridMap, Vector<HexCell*>& enemyChessAround) {
    std::set<Vec2> checkedCells; // 用于避免重复检查
    std::queue<Vec2> cellsToCheck; // 用于保存待检查的格子坐标
    cellsToCheck.push(atGridPosition); // 当前棋子所在的格子
    checkedCells.insert(atGridPosition);

    int boolFlag = 0;
    int currentRange = 1;
    while (!cellsToCheck.empty() && currentRange <= attackRange) {
        int size = cellsToCheck.size();
        for (int i = 0; i < size; ++i) {
            Vec2 currentCellCoord = cellsToCheck.front();
            cellsToCheck.pop();

            HexCell* currentCell = gridMap->getCellAtPosition(currentCellCoord);
            Vector<HexCell*> neighbors = getNeighbors(currentCell, gridMap); // 获取邻居的函数

            for (auto& neighbor : neighbors) {
                Vec2 coord = neighbor->coordinateInBoard;
                if (checkedCells.find(coord) == checkedCells.end()) {
                    if (neighbor->chessInGrid && neighbor->chessInGrid->playerNumber != playerNumber) {
                        enemyChessAround.pushBack(neighbor);
                        boolFlag++; // 找到敌方棋子
                    }
                    cellsToCheck.push(coord);
                    checkedCells.insert(coord);
                }
            }
        }
        currentRange++;
    }
    return boolFlag;
}

void Chess::initHealthBar()
{
    healthBar = HealthBar::create("Blood1.png", "Blood2.png", 100.0f);
    healthBar->setScale(3);
    healthBar->setPosition(Vec2(100, 450));
    this->addChild(healthBar);
}

void Chess::initBlueBar()
{
    bluebar = BlueBar::create("Blood1.png", "Blue2.png", 0.0f);
    bluebar->setScale(3);
    bluebar->setPosition(Vec2(100, 350));
    this->addChild(bluebar);
}



