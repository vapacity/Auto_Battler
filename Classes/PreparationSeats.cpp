#include <PreparationSeats.h>
USING_NS_CC;

//显示mySeats中棋子
void PreparationSeats::updateForPlayer()
{
    for (int i = 0; i < SEATS_NUM; i++) {
        if (mySeats[i]) {
            mySeats[i]->setPosition(seatsArray.at(i)->getPosition());
        }
    }

    renewLatestSeat();
}

PreparationSeats* PreparationSeats::create(Chess* playerSeats[SEATS_NUM])
{
    PreparationSeats* p = new (std::nothrow) PreparationSeats();
    if (p && p->init(playerSeats)) {
        p->autorelease();
        return p;
    }
    CC_SAFE_DELETE(p);
    return nullptr;
}

//加个出售鼠标拿起的棋子

//放棋子,更新最左侧的空位位置
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

//拿走棋子,更新最左侧的空位位置
void PreparationSeats::removeChessOfSeat( Seat* seat)
{
    if (!seat)
        return;    
    seat->chessInSeat = nullptr;
    mySeats[seat->number] = nullptr;
    seat->turnToNormal();
}


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
        return false;
    }

    //读取playerSeats
    mySeats = playerSeats;


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

