#include "GridMap.h"
//最左下角棋格的初始坐标
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
    // 禁用鼠标监听器
    mouseListener->setEnabled(false);
}

void GridMap::enableMouseListener() {
    // 启用鼠标监听器
    mouseListener->setEnabled(true);
}

//创建棋格对象并添加到棋盘的对应位置
bool GridMap::init(std::map<Vec2, Chess*, Vec2Compare>playerChessMap) {
    if (!Node::init()) {
        return false;
    }


    //监听鼠标移动
    mouseListener = EventListenerMouse::create();
    mouseListener->onMouseMove = CC_CALLBACK_1(GridMap::selectGrid, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    float gapX = 3.75f;//表示六边形之间的间隔
    float gapY = 7.5f;

    //创建指定个数的棋格，并添加到棋盘的对应位置
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

    //遍历棋格，存储棋格的相邻棋格信息
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

//将myChessMap中的棋子显示出来
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

//获取鼠标悬停位置属于哪一个棋格，不在棋格上则返回空
HexCell* GridMap::mouseInWhichCell(const cocos2d::Vec2& position)
{
 //   CCLOG("Inposition x:%f,y:%f",position.x, position.y);

    HexCell* closestCell = nullptr;
    float minDistance = std::numeric_limits<float>::max();//强制转换


    for (auto& node : nodeMap)
    {
        auto cell = node.second;
        //Node类型默认锚点居中
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

//鼠标移动事件的回调函数
void GridMap::selectGrid(Event* event)
{
    // 获取鼠标事件
    EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);

    // 获取鼠标位置
    Vec2 mousePosition = mouseEvent->getLocationInView();
    static HexCell* lastCell = nullptr;
    auto currentCell = mouseInWhichCell(mousePosition);
    //log("%f,%f\n", currentCell->getPositionX(), currentCell->getPositionY());

    if (currentCell != lastCell) {
        if (currentCell) {
            currentCell->turnToSelected();// 新的棋格增加透明度
        }
        //测试用
        if (lastCell && !lastCell->isSelected) {
            lastCell->turnToNormal();// 前一个棋格恢复透明度
        }
        lastCell = currentCell;
    }

    //log("%f,%f\n", mousePosition.x, mousePosition.y);
}

bool GridMap::FindPath(Vector<HexCell*>& path, Chess* InActor, HexCell* FromNode, HexCell* ToNode, int StopSteps)
{
    path.clear();
    //安全判断
    if (!FromNode || !ToNode)
        return false;
    if (nodeMap.find(FromNode->coordinateInBoard)==nodeMap.end() || nodeMap.find(ToNode->coordinateInBoard) == nodeMap.end())
        return false;

    //获取实际所有终点
    Vector<HexCell*> ToNodes = GetNodeNeighbors(ToNode, StopSteps);
    for (int i = ToNodes.size()-1; i >= 0; i--)
    {
        if (!ToNodes.at(i)->CanPass(InActor))
            ToNodes.erase(i);
    }
    //判断起点终点是否存在
    if (!FromNode->CanPass(InActor))
        return false;
    if (ToNodes.size() == 0)
        return false;
    //判断是否已经到达终点
    if (ToNodes.contains(FromNode))
        return true;

    //将要遍历的路点
    Vector<HexCell*> openList;
    //已经完成遍历的路点
    Vector<HexCell*> closeList;
    //当前所在路点
    HexCell* nowNode;
    nowNode = FromNode;
    openList.pushBack(nowNode);
    bool bFinded = false;
    //A*寻路
    while (!bFinded)
    {
        //移除openList，加入closeList
        openList.eraseObject(nowNode);
        closeList.pushBack(nowNode);
        //获取相邻路点
        Vector<HexCell*> neighbors = nowNode->GetNeighbors();
        for (auto neighbor : neighbors)
        {
            if (!neighbor)
                continue;
            //判断相邻路点是否为终点
            if (ToNodes.contains(neighbor))
            {
                bFinded = true;
                ToNode = neighbor;
                neighbor->preNode = nowNode;
            }
            //如果在closeList或不能通行则跳过
            if (closeList.contains(neighbor) || !neighbor->CanPass(InActor))
                continue;
            //如果不在openlist，则加入openlist的队尾，以备后用
            if (!openList.contains(neighbor))
            {
                openList.pushBack(neighbor);
                neighbor->preNode = nowNode;
            }
        }
        //取出队首的路点，设置为下次循环遍历的路点
        if (openList.size() <= 0)
            break;
        else
            nowNode = openList.at(0);
    }
    openList.empty();
    closeList.empty();
    //找到了路径
    if (bFinded)
    {
        HexCell* tNode = ToNode;
        while (tNode != FromNode)
        {
            path.pushBack(tNode);
            tNode = tNode->preNode;
        }
        //获取的路径时从终点->起点的路径，需要反转回起点->终点的路径
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

    //使用While，向外层层判断
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

//向指定棋格添加棋子。暂不改变棋子对象的显示位置。将要显示的棋子存入myChessMap。
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
