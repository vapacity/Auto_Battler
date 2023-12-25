
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
        star--;
    }
    chess->maxHP = chess->health;
    chess->initHealthBar();
    return chess;
}

bool Chess::init()
{
    if (!Node::init()) {
        return false;
    }
    //this->initHealthBar();
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
    price=price*3-1;//Ǯ
    name = filename;
    star = 2;
    //�ڴ˴�����ԭ�ȶ���ĸ�������
    ATK += growATK;
    health += growHP;
}

void Chess::upgradeToThird(const std::string& filename)
{
    this->setTexture(filename);
    this->setScale(SET_SCALE * 1.5);
    price = price * 3 - 1;//Ǯ
    name = filename;
    star = 3;
    //�ڴ˴�����ԭ�ȶ���ĸ�������
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
    //���·��
    Vector<HexCell*> movePath;
    gridMap->FindPath(movePath, this, fromCell, toCell, attackRange);
    if (movePath.size() <= 0)
        return;
    //�ÿ�ʼ���ƶ�λ��ֹͣ��Ԥ�����ƶ�·�ϵ����ӿ�ʼ��Ԥ��
    fromCell->isBooked = false;
    movePath.at(0)->isBooked = true;
    auto targetPosition = movePath.at(0)->getPosition();
    auto distance = targetPosition.distance(this->getPosition());

    auto move_Action = MoveTo::create(distance / (moveSpeed * 100), targetPosition);
    auto callback = CallFunc::create([=]() {
        // ������ɺ�Ļص�,�����ӷ��õ��µ�λ��
        gridMap->addChessToGrid(this, movePath.at(0));
        gridMap->removeChessOfGrid(fromCell);
        //ע��ص���������Ҫ��������book��λ��
        fromCell->isBooked = false;
        movePath.at(0)->isBooked = true;
        isAnimationPlaying = false;
        this->changeState(Idle); // ������״̬
        });

    auto sequence = Sequence::create(move_Action, callback, nullptr);
    this->runAction(sequence);
    isAnimationPlaying = true;
}

void Chess::attackAction(GridMap* gridMap)
{
    //�Ȼ�ù�������
            //HexCell* toCell = gridMap->FindBattle(this, gridMap->getCellAtPosition(atGridPosition));
    Vector<HexCell*>enemyChessAround;
    bool findEnemy = isEnemyInAttackRange(gridMap, enemyChessAround);
    int enemyChess = enemyChessAround.size();//enemyChessAround���ǻ�������еĹ�����Χ�ڵĵз�����
    //��һ��Vector�洢���еĵз������Ǳ��ں���Ⱥ�幥��
    //Ϊ��˵������������
    if (enemyChess == 0)
    {
        changeState(Idle);
        return;
    }
    Chess* attackObject = enemyChessAround.at(0)->chessInGrid;
    //���ŶԹ�������,�����Ƕ�һ��
    //���ŶԹ�������,�����Ƕ�һ��,Զ��Ŀ����Ҫ�޸�
    Vec2 position = attackObject->getPosition() - this->getPosition();
    position = Vec2(position.x / ATTACK_MOVE, position.y / ATTACK_MOVE);

    float attackDuration = 1.0f /(10*attackSpeed);
    auto moveBackAction = MoveBy::create(attackDuration, position);
    auto moveBackReverseAction = moveBackAction->reverse();  // �ƻ�ԭʼλ��
    //�ص�������Ŀ������˺�
    auto callback = CallFunc::create([=]() {
        // ������ɺ�Ļص�,��Ŀ��ʵ������˺�
        attackObject->getHurt(ATK);
        if (attackObject->health <= 0)
            attackObject->changeState(Dead);
        isAnimationPlaying = false;
        this->changeState(Idle); // ������״̬
        });
    //�ص�������Ŀ������˺�
    auto sequence = Sequence::create(moveBackAction, moveBackReverseAction, callback, nullptr);
    this->runAction(sequence);
    isAnimationPlaying = true;
}

void Chess::deadAction(GridMap* gridMap)
{
    if (isAnimationPlaying) {
        //���˵�ʱ�򣬾��������ƶ��������ڹ�������Ҫֱ��ͣ��
        this->stopAllActions();
    }
    // ���������߼�
    auto fadeOut = FadeOut::create(0.3f);//�ص�������Ŀ������˺�
    auto callback = CallFunc::create([=]() {
        healthBar->setOpacity(0);
        });
    auto sequence = Sequence::create(fadeOut, callback, nullptr);
    runAction(sequence);
    gridMap->removeChessOfGrid(gridMap->getCellAtPosition(this->atGridPosition));//���ܷ��ڻص������У���Ϊ����������Ҫֱ������
}

void Chess::getBlood()
{

}


void Chess::getHurt(int ATK)
{
    this->health -= ATK;
    float percentage = 1.0 * health / maxHP;
    if (percentage < 0)
        percentage = 0;
    healthBar->setPercentage(percentage);
    // �ɴ�����Ѫ������������Ҫ 
}

void Chess::useSkill()
{
    ;
}

void Chess::updateInBattle(float dt, GridMap* gridMap)
{
    switch (currentState) {
    case Idle: {
        //����Ƿ��пɹ����ĵ���
        Vector<HexCell*>a;
        if (isEnemyInAttackRange(gridMap, a))
            // ����У��л�������״̬
            changeState(Attacking);
        else
            // ���û�У������ƶ�
            changeState(Moving);
        break;
    }
    case Moving: {
        // ִ���ƶ��߼�
        // ����Ŀ�ĵغ��л������л򹥻�״̬

        if (!isAnimationPlaying) {//ִ��move�߼���ǰ���ǲ��ܲ��Ŷ���
            moveAction(gridMap);
        }
        break;
    }
    case Attacking: {
        if (!isAnimationPlaying)//ֻ���ڷǲ��Ŷ���ʱ����
        {
            //��������
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
    if (currentState == newState) return; // ״̬δ�ı�
    currentState = newState;
}
Vector<HexCell*> getNeighbors(HexCell* cell, GridMap* gridMap) {
    Vector<HexCell*> neighbors;
    int x = cell->coordinateInBoard.x;
    int y = cell->coordinateInBoard.y;

    // ��Щ��ż���е����ڸ���
    Vec2 evenOffsets[6] = { {+1,  0}, { 0, -1}, {-1, -1},
                           {-1,  0}, {-1, +1}, { 0, +1} };
    // ��Щ�������е����ڸ���
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
    std::set<Vec2> checkedCells; // ���ڱ����ظ����
    std::queue<Vec2> cellsToCheck; // ���ڱ�������ĸ�������
    cellsToCheck.push(atGridPosition); // ��ǰ�������ڵĸ���
    checkedCells.insert(atGridPosition);

    int boolFlag = 0;
    int currentRange = 1;
    while (!cellsToCheck.empty() && currentRange <= attackRange) {
        int size = cellsToCheck.size();
        for (int i = 0; i < size; ++i) {
            Vec2 currentCellCoord = cellsToCheck.front();
            cellsToCheck.pop();

            HexCell* currentCell = gridMap->getCellAtPosition(currentCellCoord);
            Vector<HexCell*> neighbors = getNeighbors(currentCell, gridMap); // ��ȡ�ھӵĺ���

            for (auto& neighbor : neighbors) {
                Vec2 coord = neighbor->coordinateInBoard;
                if (checkedCells.find(coord) == checkedCells.end()) {
                    if (neighbor->chessInGrid && neighbor->chessInGrid->playerNumber != playerNumber) {
                        enemyChessAround.pushBack(neighbor);
                        boolFlag++; // �ҵ��з�����
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
    healthBar->setPosition(Vec2(25, 150));
    this->addChild(healthBar);
}



