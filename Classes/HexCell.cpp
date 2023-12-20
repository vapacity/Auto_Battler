#include "HexCell.h"

USING_NS_CC;
#define SCALE 0.31


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

    hexSprite = Sprite::create("hex.png"); // 替换为六边形图片路径
    hexSprite->setOpacity(80);
    //设置缩放比例
    hexSprite->setScale(SCALE);

    this->addChild(hexSprite);

    //初始化棋格显示的宽高和边长
    width = hexSprite->getContentSize().width * SCALE;
    height = hexSprite->getContentSize().height * SCALE;
    length = width / 2;





    return true;
}


void HexCell::turnToSelected() {
    if (this == nullptr)
        return;
    if (this->hexSprite!=nullptr)
        hexSprite->setOpacity(150);
}

void HexCell::turnToNormal() {
    if (this == nullptr)
        return;
    hexSprite->setOpacity(80);
}

Vector<HexCell*> HexCell::GetNeighbors() {
    Vector<HexCell*> tmp;
    if (RightDownNode) {
        if (!tmp.contains(RightDownNode)) {
            tmp.pushBack(RightDownNode);
        }
    }    
    if (RightNode) {
        if (!tmp.contains(RightNode)) {
            tmp.pushBack(RightNode);
        }
    }
    if (RightUpNode) {
        if (!tmp.contains(RightUpNode)) {
            tmp.pushBack(RightUpNode);
        }

    } 
    if (LeftUpNode) {
        if (!tmp.contains(LeftUpNode)) {
            tmp.pushBack(LeftUpNode);
        }

    } 
    if (LeftNode) {
        if (!tmp.contains(LeftNode)) {
            tmp.pushBack(LeftNode);
        }

    } 
    if (LeftDownNode) {
        if (!tmp.contains(LeftDownNode)) {
            tmp.pushBack(LeftDownNode);
        }

    }




   
    return tmp;
}

bool HexCell::CanPass(Chess* InActor) const {
    if (chessInGrid && InActor) {
        if (chessInGrid==InActor)
            return true;
        else
            return false;
    }
    return true;
}


