#include "GridMap.h"
//�����½����ĳ�ʼ����
#define STARTX 200
#define STARTY 320
USING_NS_CC;



GridMap* GridMap::create(std::map<Vec2, Chess*, Vec2Compare>myChessMap) {
    GridMap* grid = new (std::nothrow) GridMap();
    if (grid && grid->init(myChessMap)) {
        grid->autorelease();
        return grid;
    }
    CC_SAFE_DELETE(grid);
    return nullptr;
}

void GridMap::disableMouseListener() {
    // ������������
    mouseListener->setEnabled(false);
}

void GridMap::enableMouseListener() {
    // ������������
    mouseListener->setEnabled(true);
}

//������������ӵ����̵Ķ�Ӧλ��
bool GridMap::init(std::map<Vec2, Chess*, Vec2Compare>playerChessMap) {
    if (!Node::init()) {
        return false;
    }


    //��������ƶ�
    mouseListener = EventListenerMouse::create();
    mouseListener->onMouseMove = CC_CALLBACK_1(GridMap::selectGrid, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    float gapX = 3.75f;//��ʾ������֮��ļ��
    float gapY = 7.5f;

    //����ָ����������񣬲���ӵ����̵Ķ�Ӧλ��
    for (int y = 0; y < NUM_LINE; ++y) {
        for (int x = 0; x < NUM_COLUMN; ++x) {
            auto cell = HexCell::create();
            nodeMap.insert(std::make_pair(Vec2(x, y), cell));
            
            cell->coordinateInBoard = Vec2(x, y);
            float posX = x * (cell->width + gapX) + (y % 2) * (cell->width / 2 + gapX / 2) + STARTX;
            float posY = y * (cell->length * 1.5 + gapY) + STARTY;
            cell->setPosition(posX, posY);
            this->addChild(cell);

        }
    }

    //������񣬴洢�������������Ϣ
    for (auto tNode : nodeMap) {
        if (!tNode.second)
            continue;
        bool isEvenLine = int((tNode.first).y) % 2 == 0;

        Vec2 tRightUp = tNode.first + Vec2(!isEvenLine, 1);
        if (isInBoard(tRightUp))
            tNode.second->RightUpNode = nodeMap.at(tRightUp);

        Vec2 tRight = tNode.first + Vec2(1, 0);
        if(isInBoard(tRight))
            tNode.second->RightNode = nodeMap.at(tRight);

        Vec2 tRightDown = tNode.first + Vec2(-isEvenLine, -1);
        if (isInBoard(tRightDown))
            tNode.second->RightDownNode = nodeMap.at(tRightDown);

        Vec2 tLeft = tNode.first + Vec2(-1, 0);
        if (isInBoard(tLeft))
            tNode.second->LeftNode = nodeMap.at(tLeft);

        Vec2 tLeftUp = tNode.first + Vec2(-isEvenLine, 1);
        if (isInBoard(tLeftUp))
            tNode.second->LeftUpNode = nodeMap.at(tLeftUp);

        Vec2 tLeftDown = tNode.first + Vec2(-isEvenLine, -1);
        if (isInBoard(tLeftDown))
            tNode.second->LeftDownNode = nodeMap.at(tLeftDown);

     

    }

    myChessMap = playerChessMap;
    for (auto a : myChessMap) {
        nodeMap.at(a.first)->chessInGrid = a.second;
    }

    schedule(CC_CALLBACK_0(GridMap::updateForPlayer, this),0.0f,"updateMap");
    return true;
}

//��myChessMap�е�������ʾ����
void GridMap::updateForPlayer()
{
    for (auto a : myChessMap) {
        a.second->setPosition(nodeMap.at(a.first)->getPosition());
    }

}


bool GridMap::isInBoard(Vec2 coor) {
    if (coor.x >= 0 && coor.x < NUM_COLUMN && coor.y >= 0 && coor.y < NUM_LINE)
        return 1;
    return 0;
}

//��ȡ�����ͣλ��������һ����񣬲���������򷵻ؿ�
HexCell* GridMap::mouseInWhichCell(const cocos2d::Vec2& position)
{
 //   CCLOG("Inposition x:%f,y:%f",position.x, position.y);

    HexCell* closestCell = nullptr;
    float minDistance = std::numeric_limits<float>::max();//ǿ��ת��


    for (auto& node : nodeMap)
    {
        auto cell = node.second;
        //Node����Ĭ��ê�����
        float distanceX = abs(cell->getPositionX() - position.x);
        float distanceY = abs(cell->getPositionY() - position.y);
        if (distanceX > cell->length || distanceY > sqrt(3) * 0.5 * cell->length)
            continue;
        if (cell->length - distanceX > distanceY / sqrt(3))
        {
            closestCell = cell;
            break;
        }

    }
    //if (closestCell)
        //CCLOG("Outposition x:%f,y:%f", closestCell->getPositionX(), closestCell->getPositionY());
    return closestCell;
}

//����ƶ��¼��Ļص�����
void GridMap::selectGrid(Event* event)
{
    // ��ȡ����¼�
    EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);

    // ��ȡ���λ��
    Vec2 mousePosition = mouseEvent->getLocationInView();
    static HexCell* lastCell = nullptr;
    auto currentCell = mouseInWhichCell(mousePosition);
    //log("%f,%f\n", currentCell->getPositionX(), currentCell->getPositionY());

    if (currentCell != lastCell) {
        if (currentCell) {
            currentCell->turnToSelected();// �µ��������͸����
        }
        //������
        if (lastCell && !lastCell->isSelected) {
            lastCell->turnToNormal();// ǰһ�����ָ�͸����
        }
        lastCell = currentCell;
    }

    //log("%f,%f\n", mousePosition.x, mousePosition.y);
}

bool GridMap::FindPath(Vector<HexCell*>& path, Chess* InActor, HexCell* FromNode, HexCell* ToNode, int StopSteps)
{
    path.clear();
    //��ȫ�ж�
    if (!FromNode || !ToNode)
        return false;
    if (nodeMap.find(FromNode->coordinateInBoard)==nodeMap.end() || nodeMap.find(ToNode->coordinateInBoard) == nodeMap.end())
        return false;

    //��ȡʵ�������յ�
    Vector<HexCell*> ToNodes = GetNodeNeighbors(ToNode, StopSteps);
    for (int i = ToNodes.size()-1; i >= 0; i--)
    {
        if (!ToNodes.at(i)->CanPass(InActor))
            ToNodes.erase(i);
    }
    //�ж�����յ��Ƿ����
    if (!FromNode->CanPass(InActor))
        return false;
    if (ToNodes.size() == 0)
        return false;
    //�ж��Ƿ��Ѿ������յ�
    if (ToNodes.contains(FromNode))
        return true;

    //��Ҫ������·��
    Vector<HexCell*> openList;
    //�Ѿ���ɱ�����·��
    Vector<HexCell*> closeList;
    //��ǰ����·��
    HexCell* nowNode;
    nowNode = FromNode;
    openList.pushBack(nowNode);
    bool bFinded = false;
    //A*Ѱ·
    while (!bFinded)
    {
        //�Ƴ�openList������closeList
        openList.eraseObject(nowNode);
        closeList.pushBack(nowNode);
        //��ȡ����·��
        Vector<HexCell*> neighbors = nowNode->GetNeighbors();
        for (auto neighbor : neighbors)
        {
            if (!neighbor)
                continue;
            //�ж�����·���Ƿ�Ϊ�յ�
            if (ToNodes.contains(neighbor))
            {
                bFinded = true;
                ToNode = neighbor;
                neighbor->preNode = nowNode;
            }
            //�����closeList����ͨ��������
            if (closeList.contains(neighbor) || !neighbor->CanPass(InActor))
                continue;
            //�������openlist�������openlist�Ķ�β���Ա�����
            if (!openList.contains(neighbor))
            {
                openList.pushBack(neighbor);
                neighbor->preNode = nowNode;
            }
        }
        //ȡ�����׵�·�㣬����Ϊ�´�ѭ��������·��
        if (openList.size() <= 0)
            break;
        else
            nowNode = openList.at(0);
    }
    openList.empty();
    closeList.empty();
    //�ҵ���·��
    if (bFinded)
    {
        HexCell* tNode = ToNode;
        while (tNode != FromNode)
        {
            path.pushBack(tNode);
            tNode = tNode->preNode;
        }
        //��ȡ��·��ʱ���յ�->����·������Ҫ��ת�����->�յ��·��
        std::reverse(path.begin(),path.end());

        return true;
    }

    return false;

}

Vector<HexCell*> GridMap::GetNodeNeighbors(HexCell* inNode,int stepRange) {

    Vector<HexCell*> nowCheckList;
    Vector<HexCell*> nextCheckList;
    Vector<HexCell*> findList;

    if (!nextCheckList.contains(inNode)) {
        nextCheckList.pushBack(inNode);
    }
    if (!findList.contains(inNode)) {
        findList.pushBack(inNode);
    }

    //ʹ��While���������ж�
    while (stepRange > 0)
    {
        nowCheckList = nextCheckList;
        nextCheckList.empty();
        for (HexCell* a : nowCheckList)
        {
            if (!a)
                continue;
            Vector<HexCell*> neighbors = a->GetNeighbors();
            for (HexCell* b : neighbors)
            {
                if (findList.contains(b))
                    continue;
                if (!findList.contains(b)) {
                    findList.pushBack(b);
                }
                if (!nextCheckList.contains(b)) {
                    nextCheckList.pushBack(b);
                }
            }
        }
        stepRange -= 1;
    }

    return findList;
}

//��ָ�����������ӡ��ݲ��ı����Ӷ������ʾλ�á���Ҫ��ʾ�����Ӵ���myChessMap��
void GridMap::addChessToGrid(Chess* Inchess, HexCell* Incell)
{
    if (!Inchess ||!Incell)
        return;
   // chessAmount++;
    Incell->chessInGrid = Inchess;
    //Inchess->setPosition(Incell->getPosition());
    Inchess->atCell = Incell;
    Inchess->atSeat = nullptr;
 
    myChessMap.insert(std::make_pair(Incell->coordinateInBoard, Inchess));
}

void GridMap::removeChessOfGrid(HexCell* Incell)
{
    if (!Incell)
        return;
    Incell->chessInGrid = nullptr;
    myChessMap.erase(Incell->coordinateInBoard);
    //chessAmount--;
}
