#include <Seat.h>
USING_NS_CC;


Seat* Seat::create()
{
    try {
        Seat* seat = new Seat();
        if (seat && seat->init()) {
            seat->autorelease();
            return seat;
        }
        CC_SAFE_DELETE(seat);
    }
    catch (const std::exception& e) {
        // 捕获到异常时的处理逻辑
        CCLOG("Exception caught: %s", e.what());
    }
}

bool Seat::init()
{
    if (!Node::init()) {
        throw std::runtime_error("Seat initialization failed: Node initialization failed");
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
        if (seatImage)
            seatImage->setOpacity(80);
}


