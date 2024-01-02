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
        // �����쳣ʱ�Ĵ����߼�
        CCLOG("Exception caught: %s", e.what());
    }
    return nullptr;
}


bool HexCell::init() {
    if (!Node::init()) {
        throw std::runtime_error("HexCell initialization failed: Node initialization failed");
    }

    hexSprite = Sprite::create("hex.png"); // �滻Ϊ������ͼƬ·��
    hexSprite->setOpacity(80);
    //�������ű���
    hexSprite->setScale(SCALE);

    this->addChild(hexSprite);

    //��ʼ�������ʾ�Ŀ�ߺͱ߳�
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
        //�������ϵ����Ӿ���Ҫ���������ӣ�����ͨ��
        if (chessInGrid == InActor)
            return true;
        else//�������ϵ����Ӳ���Ҫ���������ӣ�������ͨ��
            return false;
    }
    return true;//�����û�����ӣ���ͨ��
}

