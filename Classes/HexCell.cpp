#include "HexCell.h"

USING_NS_CC;

HexCell* HexCell::create() {
    HexCell* cell = new (std::nothrow) HexCell();
    if (cell && cell->init()) {
        cell->autorelease();
        return cell;
    }
    CC_SAFE_DELETE(cell);
    return nullptr;
}


bool HexCell::init() {
    if (!Node::init()) {
        return false;
    }

    hexSprite = Sprite::create("hex.png"); // Ìæ»»ÎªÁù±ßÐÎÍ¼Æ¬Â·¾¶
    hexSprite->setOpacity(80);
    //ÉèÖÃËõ·Å±ÈÀý
    hexSprite->setScale(0.3);
    this->addChild(hexSprite);

    return true;
}

void HexCell::changeOpacity(int Opacity)
{
    if (this == nullptr)
        return;
    hexSprite->setOpacity(Opacity);
}
