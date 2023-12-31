#include "HexCell.h"

USING_NS_CC;
#define SCALE 0.31


HexCell* HexCell::create() {
    try {
        HexCell* cell = new HexCell();
        if (cell && cell->init()) {
            cell->autorelease();
            return cell;
        }
        CC_SAFE_DELETE(cell);
    }
    catch (const std::exception& e) {
        // 捕获到异常时的处理逻辑
        CCLOG("Exception caught: %s", e.what());
    }
    return nullptr;
}


bool HexCell::init() {
    if (!Node::init()) {
        throw std::runtime_error("HexCell initialization failed: Node initialization failed");
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
    hexSprite->setOpacity(200);
}
void HexCell::turnToSeen()
{
    if (this == nullptr)
        return;
    hexSprite->setOpacity(100);
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
        //如果棋格上的棋子就是要经过的棋子，可以通行
        if (chessInGrid == InActor)
            return true;
        else//如果棋格上的棋子不是要经过的棋子，不可以通行
            return false;
    }
    return true;//棋格上没有棋子，可通行
}

