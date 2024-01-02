#include "cocos2d.h"
#include "Chess.h"
#include"ChessFactory.h"
#include "GridMap.h"
USING_NS_CC; 
#define MoveTime 1.0f
#define ATTACK_MOVE 5
Chess* Chess::create()
{
    try {//����� new Chess() �� chessExample->init() �Ĺ������׳��쳣����ô�쳣��Ϣ��������ͨ�� CCLOG �����
        Chess* chessExample = new Chess();
        if (chessExample && chessExample->init()) {
            chessExample->autorelease();
            return chessExample;
        }
        CC_SAFE_DELETE(chessExample);
    }
    catch (const std::exception& e) {
        // �����쳣ʱ�Ĵ����߼�
        CCLOG("Exception caught: %s", e.what());
    }
    return nullptr;
}

Chess* Chess::create(const std::string& filename)
{
    try {
        Chess* chessExample = new Chess();
        if (chessExample && chessExample->initWithFile(filename) && chessExample->init()) {
            chessExample->autorelease();
            return chessExample;
        }
        CC_SAFE_DELETE(chessExample);
    }
    catch (const std::exception& e) {
        // �����쳣ʱ�Ĵ����߼�
        CCLOG("Exception caught: %s", e.what());
    }
    return nullptr;
}

bool Chess::init()
{
    if (!Node::init()) {
        throw std::runtime_error("Chess initialization failed: Node initialization failed");
        return false;
    }
    return true;
}
void Chess::deleteChess()
{
    if (this)
        this->removeFromParent();
}

int Chess::getId()const
{
    if (this)
        return this->id;

    return -1;
}

int Chess::getStar()const
{
    if (this)
        return this->star;
    return -1;
}

bool Chess::isInGrid()const
{
    return (atGridPosition.x >= 0 && atGridPosition.y >= 0);
}

bool Chess::isAtSeat() const
{
    return atSeatPosition >= 0;
}

Chess* Chess::createByIdAndStar(int id, int star)//�����star���βΣ���ʾ�������������ı仯��Ӱ������ʵ���Ǽ�
{
    Chess* chess = ChessFactory::createChessById(id);//�˷����������ӣ���ʼʵ���Ǽ�Ϊ1
    while (star > 1)//�������Ǽ���2������һ�Σ��Ǽ���3����������
    {
        chess->upgrade();
        star--;
    }
    chess->maxHP = chess->health;
    chess->initHealthBar();
    chess->initBlueBar();
    return chess;
}

//�����������Ѱ���ַ����е�һ���ַ����������滻
//original��ԭ�ַ�����toReplace�Ǳ��滻���ַ�����newString���滻����ַ���
std::string replaceSubstring(const std::string& original, const std::string& toReplace, const std::string& newString) {
    std::string result = original;
    size_t pos = 0;
    //���ҵ���toReplace�ַ���������ѭ��
    while ((pos = result.find(toReplace, pos)) != std::string::npos) {
        result.replace(pos, toReplace.length(), newString);//ִ���滻
        
        pos += newString.length();// ����λ�ã�ǰ�����ַ����ĳ���
    }
    return result;
}

void Chess::upgrade()
{   
    if (this->star == 1)//�����star������ʵ���Ǽ�
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
    maxHP += growHP;
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
    maxHP += growHP;
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

    //�����ӵ�ǰλ��Ϊ��㣬Ŀ��λ��Ϊ�յ㣬����ʱ��Ϊ��������ƶ��ٶ�
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

    //��ǰ���ͷż���
    if (this->enable_skill) {
        useSkill();
    }
    
    //�ص�������Ŀ������˺�
    auto callback = CallFunc::create([=]() {
        // ������ɺ�Ļص�,��Ŀ��ʵ������˺�
        if (attackObject) {
            attackObject->getHurt(ATK);
            if (attackObject->health <= 0)
                attackObject->changeState(Dead);
        }
        //����,�ż���ʱ����
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
        this->changeState(Idle); // ������״̬
        });
    //�ص�������Ŀ������˺�

    //��ս����
    if(isMelee==1){
        //���ŶԹ�������,�����Ƕ�һ��,Զ��Ŀ����Ҫ�޸�
        Vec2 position = attackObject->getPosition() - this->getPosition();
        position = Vec2(position.x / ATTACK_MOVE, position.y / ATTACK_MOVE);

        float attackDuration = 1.0f / (10 * attackSpeed);
        auto moveBackAction = MoveBy::create(attackDuration, position);
        auto moveBackReverseAction = moveBackAction->reverse();  // �ƻ�ԭʼλ��
        auto sequence1 = Sequence::create(moveBackAction, moveBackReverseAction, callback, nullptr);
        this->runAction(sequence1);
    }
    //Զ�̹�������������
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

    // ���������߼�
    auto fadeOut = FadeOut::create(0.3f);

    // ����Sequence�������������������ͻص��������Ƴ��ڵ���߼���
    auto sequence = Sequence::create(
        fadeOut,
        CallFunc::create([this, gridMap]() {
            this->removeFromParentAndCleanup(true); // �Ƴ���ִ���������
            }),
        nullptr
                );

    // �Խ�ɫ��Ѫ���������ֱ�Ӧ�ö�����Sequence����
    this->runAction(sequence);
    //this->healthBar->runAction(fadeOut);
    //this->bluebar->runAction(fadeOut);
    gridMap->removeChessOfGrid(gridMap->getCellAtPosition(this->atGridPosition));
    //this->removeFromParentAndCleanup(true);
}


void Chess::getHurt(int ATK)
{
    //Ѫ������
    this->health -= ATK;
    float percentage_health = 100.0 * health / maxHP;
    if (percentage_health < 0)
        percentage_health = 0;
    healthBar->setPercentage(percentage_health);

    //��������
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
    // �ɴ�����Ѫ������������Ҫ 
}

void Chess::useSkill()
{
    CCLOG("USESKILL");

}
//dt��ÿһ֮֡���ʱ��ʵʱ����״̬
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
        default:
            break;
    }
}

void Chess::changeState(State newState)
{
    if (currentState == newState) return; // ״̬δ�ı�
    currentState = newState;
}

Vector<HexCell*> getNeighbors(HexCell* cell, GridMap* gridMap) {
    //�������ڸ�������
    Vector<HexCell*> neighbors;
    //Ŀ�����λ��
    int x = cell->coordinateInBoard.x;
    int y = cell->coordinateInBoard.y;

    // ��Щ��ż���е����ڸ���
    Vec2 evenOffsets[6] = { {+1,  0}, { 0, -1}, {-1, -1},
                           {-1,  0}, {-1, +1}, { 0, +1} };
    // ��Щ�������е����ڸ���
    Vec2 oddOffsets[6] = { {+1,  0}, {+1, -1}, { 0, -1},
                           {-1,  0}, { 0, +1}, {+1, +1} };

    //�����ж���Χ�����������Ƿ������̺Ϸ���Χ������������
    for (int i = 0; i < 6; ++i) {
        Vec2 offset = (y % 2 == 0) ? evenOffsets[i] : oddOffsets[i];
        Vec2 neighborCoord = Vec2(x + offset.x, y + offset.y);
        if (neighborCoord.x >= 0 && neighborCoord.x < NUM_COLUMN && neighborCoord.y >= 0 && neighborCoord.y < NUM_LINE)
            neighbors.pushBack(gridMap->getCellAtPosition(neighborCoord));
    }

    return neighbors;
}

//enemyChessAround���湥����Χ�ĵз�����
bool Chess::isEnemyInAttackRange(GridMap* gridMap, Vector<HexCell*>& enemyChessAround) {
    std::set<Vec2> checkedCells; // ���ڱ����ظ����
    std::queue<Vec2> cellsToCheck; // ���ڱ�������ĸ�������
    cellsToCheck.push(atGridPosition); // ��ǰ�������ڵĸ���
    checkedCells.insert(atGridPosition);

    int boolFlag = 0;
    int currentRange = 1;
    //�����������
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
    healthBar->setScale(3);//����
    healthBar->setPosition(Vec2(100, 450));//λ��
    this->addChild(healthBar);
}

void Chess::initBlueBar()
{
    bluebar = BlueBar::create("Blood1.png", "Blue2.png", 0.0f);
    bluebar->setScale(3);
    bluebar->setPosition(Vec2(100, 350));
    this->addChild(bluebar);
}



