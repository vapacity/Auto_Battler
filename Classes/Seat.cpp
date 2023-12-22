#include <Seat.h>
USING_NS_CC;


Seat* Seat::create()
{
    Seat* seat = new (std::nothrow) Seat();
    if (seat && seat->init()) {
        seat->autorelease();
        return seat;
    }
    CC_SAFE_DELETE(seat);
    return nullptr;
}

bool Seat::init()
{
    if (!Node::init()) {
        return false;
    }

    seatImage = Sprite::create("seatImage.png");
    seatImage->setScale(SEAT_SCALE);
    this->addChild(seatImage);

    this->turnToNormal();
    width = seatImage->getContentSize().width * SEAT_SCALE;
    return true;
}

void Seat::turnToSelected()
{
    if (this == nullptr)
        return;
    seatImage->setOpacity(150);
}

void Seat::turnToNormal()
{
    if (this == nullptr)
        return;
    if (!this->chessInSeat)
        seatImage->setOpacity(80);
}

