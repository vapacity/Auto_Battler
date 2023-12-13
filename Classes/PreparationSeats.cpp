#include <PreparationSeats.h>
USING_NS_CC;


PreparationSeats* PreparationSeats::create()
{
    PreparationSeats* p = new (std::nothrow) PreparationSeats();
    if (p && p->init()) {
        p->autorelease();
        return p;
    }
    CC_SAFE_DELETE(p);
    return nullptr;
}

//加个出售鼠标拿起的棋子


void PreparationSeats::addChessToSeat(Chess* chess, Seat* seat)
{
    if (!chess || !seat)
        return;
    seat->chessInSeat = chess;
    chess->setPosition(seat->getPosition());
    chess->atSeat = seat;
    chess->atCell = nullptr;
    //seatsNum++;
    renewLatestSeat();
    seat->turnToSelected();


}

void PreparationSeats::removeChessOfSeat( Seat* seat)
{
    if (!seat)
        return;
    seat->chessInSeat = nullptr;
   // seatsNum--;
    renewLatestSeat();
}

void PreparationSeats::addOrRemove(Chess* chess, Seat* seat)
{
    if (!chess || !seat)
        return;
    if (seat && chess) {
        if (!seat->chessInSeat) {
            addChessToSeat(chess, seat);
        }
        else
            removeChessOfSeat(seat);
    }

}



void PreparationSeats::renewLatestSeat()
{
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
    if (seatsNum == SEATS_NUM)
        return true;
    else
        return false;
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

bool PreparationSeats::init()
{
    if (!Node::init()) {
        return false;
    }

    EventListenerMouse* mouseListener = EventListenerMouse::create();
    mouseListener->onMouseMove = CC_CALLBACK_1(PreparationSeats::selectSeat, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
    mouseListener->setEnabled(true);

    EventListenerMouse* testUp = EventListenerMouse::create();
    testUp->onMouseUp = CC_CALLBACK_1(PreparationSeats::testClickUp, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(testUp, this);
    testUp->setEnabled(true);



    for (int i = 0; i < SEATS_NUM; i++) {
        Seat* s = Seat::create();
        float x = SEAT_STARTX + i * (s->width + seatGap);
        s->setPosition(x, SEAT_STARTY);
        seatsArray.pushBack(s);
        this->addChild(s);
    }


    latestSeat = seatsArray.at(0);
}


void PreparationSeats::testClickUp(Event* event)
{
    
    // 获取鼠标事件
    auto mouseEvent = static_cast<EventMouse*>(event);
    // 获取鼠标位置
    Vec2 mousePosition = mouseEvent->getLocationInView();
    if (auto seat = mouseInWhichSeat(mousePosition)) {
        if (TEST)
            ;
           //chessWithMouse = Chess::create();
       // addOrRemove(chessWithMouse, seat);
    }
}

