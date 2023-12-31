#include <PreparationSeats.h>
USING_NS_CC;

//显示mySeats中棋子
void PreparationSeats::updateForPlayer()
{//把我方备战席上的棋子坐标设置为备战席的坐标
    for (int i = 0; i < SEATS_NUM; i++) {
        if (mySeats[i]) {
            mySeats[i]->setPosition(seatsArray.at(i)->getPosition());
        }
    }

    renewLatestSeat();
}

PreparationSeats* PreparationSeats::create(Chess* playerSeats[SEATS_NUM])
{
    try {
        PreparationSeats* p = new PreparationSeats();
        if (p && p->init(playerSeats)) {
            p->autorelease();
            return p;
        }
        CC_SAFE_DELETE(p);
    }
    catch (const std::exception& e) {
        // 捕获到异常时的处理逻辑
        CCLOG("Exception caught: %s", e.what());
    }
    return nullptr;
}

//放棋子
void PreparationSeats::addChessToSeat(Chess* chess, Seat* seat)
{
    if (!chess || !seat)
        return;
    seat->chessInSeat = chess;
    chess->atSeatPosition = seat->number;
    chess->atGridPosition = Vec2(-1,-1);

    seat->turnToSelected();

    mySeats[seat->number] = chess;
}

//拿走棋子
void PreparationSeats::removeChessOfSeat( Seat* seat)
{
    if (!seat)
        return;    
    seat->chessInSeat = nullptr;
    mySeats[seat->number] = nullptr;
    seat->turnToNormal();
}

//更新最左侧棋子
void PreparationSeats::renewLatestSeat()
{
    if (seatsArray.size() <= 0)
        return;
    for (auto s : seatsArray) {
        if (!s->chessInSeat) {
            latestSeat = s;
            break;
        }
    }

    //测试返回最左侧位置
    for (int i = 0; i < seatsNum; i++) {
        if(seatsArray.at(i)==latestSeat)
            log("%d\n", i);
    }


}

bool PreparationSeats::isFull()
{
    int seatedSeats = 0;
    for (auto s : seatsArray)
    {
        if (s->chessInSeat)
            seatedSeats++;
    }
    return !(SEATS_NUM - seatedSeats);
}

void PreparationSeats::selectSeat(Event* event)
{
    // 获取鼠标事件
    EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);

    // 获取鼠标位置
    Vec2 mousePosition = mouseEvent->getLocationInView();
    static Seat* lastSeat = nullptr;
    auto currentSeat = mouseInWhichSeat(mousePosition);


    if (currentSeat != lastSeat) {
        if (currentSeat) {
            currentSeat->turnToSelected();// 新的棋格增加透明度         
        }
        if (lastSeat) {
            lastSeat->turnToNormal();// 前一个棋格恢复透明度
        }
        lastSeat = currentSeat;
    }
}

Seat* PreparationSeats::mouseInWhichSeat(const cocos2d::Vec2& position)
{

    float width = this->seatsArray.at(0)->width;
    if (position.x >= STARTX - width / 2 && position.x < STARTX + (width + seatGap) * SEATS_NUM - width / 2) {
        int index = (position.x - STARTX + width / 2) / (width + seatGap);

        Seat* s = this->seatsArray.at(index);
        // 获取精灵的显示区域

        Rect globalBoundingBox = s->seatImage->getBoundingBox();
        Vec2 originInWorld = s->seatImage->getParent()->convertToWorldSpaceAR(globalBoundingBox.origin);
        Rect spriteInWorld = Rect(originInWorld, globalBoundingBox.size);


        // 判断鼠标是否在精灵的显示区域内
        if (spriteInWorld.containsPoint(position))
            return s;
    }
    return nullptr;
}

bool PreparationSeats::init(Chess* playerSeats[SEATS_NUM])
{
    if (!Node::init()) {
        throw std::runtime_error("PreparationSeats initialization failed: Node initialization failed");
    }

    //读取playerSeats
    mySeats = playerSeats;

    //依次创建8个备战席
    for (int i = 0; i < SEATS_NUM; i++) {
        Seat* s = Seat::create();
        float x = SEAT_STARTX + i * (s->width + seatGap);
        s->setPosition(x, SEAT_STARTY);
        s->number = i;
        seatsArray.pushBack(s);
        if (s->getParent())
            this->removeFromParent();
        this->addChild(s);
    }

    EventListenerMouse* mouseListener = EventListenerMouse::create();
    mouseListener->onMouseMove = CC_CALLBACK_1(PreparationSeats::selectSeat, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
    mouseListener->setEnabled(true);


    schedule(CC_CALLBACK_0(PreparationSeats::updateForPlayer, this), 0.0f, "updateSeats");

}

Seat* PreparationSeats::getSeatAtPosition(int position)
{
    if (position >= 0 && position <= SEATS_NUM)
        return seatsArray.at(position);
    return nullptr;
}

