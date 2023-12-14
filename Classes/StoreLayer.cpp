#include"Store.h"
#include"StoreLayer.h"
//include"card.h"
USING_NS_CC;

//storelayer添加在卡槽左下角

void StoreLayer::refreshWithId(int id)
{
    layerId = id;

    if (layerId == -1) {
        layerImage->setTexture("03.jpg");
        layerImage->setContentSize(Size(pictureSize, pictureSize));
        std::string newLabel = "";
        costLabel->setString(newLabel);
        return;
    }
    else if (layerId % 3 == 0) {
        layerImage->setTexture("Yevee-card.png");
        layerImage->setContentSize(Size(pictureSize, pictureSize));
    }
    else if (layerId % 3 == 1) {
        layerImage->setTexture("Charmander-card.png");
        layerImage->setContentSize(Size(pictureSize, pictureSize));
    }
    else if (layerId % 3 == 2) {
        layerImage->setTexture("Squirtle-card.png");
        layerImage->setContentSize(Size(pictureSize, pictureSize));
    }

    std::string newLabel = "COST " + layerId / 3 + 1;
    costLabel->setString(newLabel);
}

StoreLayer* StoreLayer::create(int id) {
	StoreLayer* layer = new (std::nothrow) StoreLayer();
	if (layer && layer->init(id)) {
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return nullptr;
}


//void StoreLayer::showStore() {//显示商店数据及卡牌数据
//    clearCard();
//
//
//    for (int i = 0; i < 5; i++) {
//
//        StoreCard* storeCard = StoreCard::create(layerId[i]);
//        if (storeCard) {
//            storeCard->setPosition(Vec2(i * 200 + 200, pictureSize / 2));
//            addChild(storeCard);
//            cardArray.push_back(storeCard);
//        }
//    }
//}


bool StoreLayer::init(int id) {

    //// 创建文本标签
    //moneyLabel = Label::createWithTTF("NULL", "fonts/arial.ttf", 24);
    //levelAndExpLabel = Label::createWithTTF("NULL", "fonts/arial.ttf", 20);
    //label1 = Label::createWithTTF("REFRESH", "fonts/arial.ttf", 24);
    //label2 = Label::createWithTTF("BUYEXP", "fonts/arial.ttf", 24);
    //// 设置文本标签的位置
    //moneyLabel->setPosition(Vec2(0, 175));
    //levelAndExpLabel->setPosition(Vec2(1170, 40));
    //label1->setPosition(Vec2(1170, 160));
    //label2->setPosition(Vec2(1170, 100));
    //// 设置文本颜色
    //moneyLabel->setColor(Color3B::RED);
    //levelAndExpLabel->setColor(Color3B::RED);
    //label1->setColor(Color3B::BLUE);
    //label2->setColor(Color3B::BLUE);
    //// 将文本标签添加到场景
    //this->addChild(moneyLabel);
    //this->addChild(levelAndExpLabel);
    //this->addChild(label1);
    //this->addChild(label2);
    //updateMoneyLabel();
    //updateLevelLabel();

    //StoreLayerMouseListener = EventListenerMouse::create();
    //StoreLayerMouseListener->onMouseDown = [this](EventMouse* event) {
    //    // 判断只处理左键点击事件
    //    if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
    //        // 处理左键点击的逻辑，可以调用 selectStore 或其他处理函数
    //        selectStore(event);
    //    }
    //};
    //_eventDispatcher->addEventListenerWithSceneGraphPriority(StoreLayerMouseListener, this);


    if (!Node::init())
        return false;

    layerImage = Sprite::create();
    layerImage->setPosition(pictureSize / 2, pictureSize / 2);
    this->addChild(layerImage);


    costLabel = Label::create();
    costLabel = Label::createWithTTF("", "fonts/arial.ttf", 24);
    costLabel->setColor(Color3B::BLACK);
    costLabel->setPosition(pictureSize / 2, pictureSize);
    this->addChild(costLabel);


    refreshWithId(id);

	return true;
}

