#include "GridMap.h"
//最左下角棋格的初始坐标
#define STARTX 200
#define STARTY 300
USING_NS_CC;

void GridMap::selectSchedule(bool select)
{
    if (select) {
        schedule(CC_CALLBACK_0(GridMap::updateForPlayer, this), 0.0f, "updateMap");
    }
    else {
        updateForPlayer();
    }
}
GridMap* GridMap::create(std::map<Vec2, Chess*, Vec2Compare>myChessMap) {
    try {
        GridMap* grid = new GridMap();
        if (grid &&  grid->init(myChessMap)) {
            grid->autorelease();
            return grid;
        }
        CC_SAFE_DELETE(grid);
    }
    catch (const std::exception& e) {
        // 捕获到异常时的处理逻辑
        CCLOG("Exception caught: %s", e.what());
    }
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
        throw std::runtime_error("GridMap initialization failed: Node initialization failed");
    }

    mouseListener = EventListenerMouse::create();
    mouseListener->onMouseMove = CC_CALLBACK_1(GridMap::selectGrid, this);//当鼠标移动时，将调用selectGrid 方法
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    float gapX = 3.75f;//表示六边形之间的间隔
    float gapY = 7.5f;

    //创建指定个数的棋格，并添加到棋盘的对应位置
    for (int y = 0; y < NUM_LINE; ++y) {
        for (int x = 0; x < NUM_COLUMN; ++x) {
            //创建一个棋格并加入整个棋盘nodemap
            auto cell = HexCell::create();
            nodeMap.insert(std::make_pair(Vec2(x, y), cell));

            if (y < NUM_LINE / 2)
                cell->isMine = true;//我方棋盘

            //棋格在棋盘上的相对位置
            cell->coordinateInBoard = Vec2(x, y);

            //棋格在窗口的实际位置
            float posX = x * (cell->width + gapX) + (y % 2) * (cell->width / 2 + gapX / 2) + STARTX;
            float posY = y * (cell->length * 1.5 + gapY) + STARTY;
            cell->setPosition(posX, posY);
            this->addChild(cell);

        }
    }

    //遍历棋格，如果棋格存在相邻棋格，则存储相邻棋格信息
    for (auto tNode : nodeMap) {
        if (!tNode.second)
            continue;
        bool isEvenLine = int((tNode.first).y) % 2 == 0;//是否是偶数行（从0开始，从下往上

        Vec2 tRightUp = tNode.first + Vec2(!isEvenLine, 1);//偶数行的棋格的右上邻居跟它在同一列，!isEvenLine=0
        if (isInBoard(tRightUp))
            tNode.second->RightUpNode = nodeMap.at(tRightUp);//map.at(key)查找键对应的值

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
    return true;
}

//将myChessMap中的棋子显示出来
void GridMap::updateForPlayer()
{   //遍历我方棋子
    for (auto a : myChessMap) {
        a.second->setPosition(nodeMap.at(a.first)->getPosition()); // 棋子的位置即它所在棋格的位置
    }

}


bool GridMap::isInBoard(Vec2 coor)const {
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

    //遍历棋格，找到和鼠标最接近的一个
    for (auto& node : nodeMap)
    {
        auto cell = node.second;
        //Node类型默认锚点居中
        //计算鼠标位置与棋格的距离
        float distanceX = abs(cell->getPositionX() - position.x);
        float distanceY = abs(cell->getPositionY() - position.y);

        //如果鼠标位置超出了棋格的边界，则跳过当前棋格
        if (distanceX > cell->length || distanceY > sqrt(3) * 0.5 * cell->length)
            continue;

        if (cell->length - distanceX > distanceY / sqrt(3))
        {
            closestCell = cell;
            break;
        }

    }
    if (closestCell)
        CCLOG("Outposition x:%f,y:%f", closestCell->getPositionX(), closestCell->getPositionY());
    return closestCell;
}

//鼠标移动事件的回调函数
void GridMap::selectGrid(Event* event)
{
    // 获取鼠标事件
    EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);

    // 获取鼠标位置
    Vec2 mousePosition = mouseEvent->getLocationInView();
    auto currentCell = mouseInWhichCell(mousePosition);

    if (currentCell != lastCell) {//若切换棋格
        if (currentCell) {
            currentCell->turnToSelected();// 新的棋格增加透明度
        }
        //测试用
        if (lastCell && !lastCell->isSelected) {
            lastCell->turnToNormal();// 前一个棋格恢复透明度
        }
        lastCell = currentCell;//更新上一个棋格
    }

}

bool GridMap::FindPath(Vector<HexCell*>& path, Chess* InActor, HexCell* FromNode, HexCell* ToNode, int StopSteps)
{
    path.clear();
    //安全判断
    if (!FromNode || !ToNode)
        return false;
    if (nodeMap.find(FromNode->coordinateInBoard) == nodeMap.end() || nodeMap.find(ToNode->coordinateInBoard) == nodeMap.end())
        return false;

    //获取实际所有终点
    Vector<HexCell*> ToNodes = GetNodeNeighbors(ToNode, StopSteps);
    for (int i = ToNodes.size() - 1; i >= 0; i--)
    {
        if (!ToNodes.at(i)->CanPass(InActor))//若某棋格不能通行，删去
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
            if (!neighbor || neighbor->isBooked) {
                continue;
            }
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
        std::reverse(path.begin(), path.end());

        return true;
    }

    return false;

}

HexCell* GridMap::FindBattle(Chess* InActor, HexCell* FromNode)
{
    CCLOG("PathFrom: %d,%d", FromNode->coordinateInBoard.x, FromNode->coordinateInBoard.y);
    //安全判断
    if (!FromNode)
        return false;
    if (nodeMap.find(FromNode->coordinateInBoard) == nodeMap.end())
        return false;

    //判断起点终点是否存在
    if (!FromNode->CanPass(InActor))
        return false;
    //判断是否已经到达终点

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
    HexCell* ToNode;
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
            if (neighbor->chessInGrid && neighbor->chessInGrid->playerNumber != InActor->playerNumber)
            {
                bFinded = true;
                ToNode = neighbor;
                neighbor->preNode = nowNode;
                break;
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
        /*while (tNode != FromNode)
        {
            path.pushBack(tNode);
            tNode = tNode->preNode;

        }*/
        //获取的路径时从终点->起点的路径，需要反转回起点->终点的路径
        CCLOG("PathFrom: %f,%f", FromNode->coordinateInBoard.x, FromNode->coordinateInBoard.y);
        CCLOG("PathTo: %f,%f", ToNode->coordinateInBoard.x, ToNode->coordinateInBoard.y);

        return ToNode;
    }

    return nullptr;

}

Vector<HexCell*> GridMap::GetNodeNeighbors(HexCell* inNode, int stepRange) {

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


void GridMap::addChessToGrid(Chess* Inchess, HexCell* Incell)
{
    if (!Inchess ||!Incell)
        return;
    chessAmount++;//棋子总数+1
    Incell->chessInGrid = Inchess;//把棋子添加到棋格上
    Inchess->atGridPosition = Incell->coordinateInBoard;//棋子的棋盘坐标为棋格的棋盘坐标

    Inchess->atSeatPosition = -1;//棋子离开备战席

    myChessMap.insert(std::make_pair(Incell->coordinateInBoard, Inchess));//把棋子加入我的棋盘
}

void GridMap::removeChessOfGrid(HexCell* Incell)
{
    if (!Incell)
        return;
    Incell->chessInGrid = nullptr;//去掉棋格上的棋子
    myChessMap.erase(Incell->coordinateInBoard);//把棋子从我的棋盘上去掉
    chessAmount--;//棋子总数-1
}

HexCell* GridMap::getCellAtPosition(Vec2 position)
{
    if (position.x >= 0 && position.y >= 0)
        return nodeMap[position];
    return nullptr;
}
