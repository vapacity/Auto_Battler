#include"Store.h"
#include"StoreLayer.h"
//include"card.h"
USING_NS_CC;
const int pictureSize = 150;
//storelayer添加在卡槽左下角

void StoreLayer::refreshWithId(int id)
{
    layerId = id;

    //捕获失败
    if (layerId == -2) {
        layerImage->setTexture("capture_failed.png");
        layerImage->setContentSize(Size(pictureSize, pictureSize));
        std::string newLabel = "";
        costLabel->setString(newLabel);
        return;
    }

    //已购买
    if (layerId == -1) {
        layerImage->setTexture("03.jpg");
        layerImage->setContentSize(Size(pictureSize, pictureSize));
        std::string newLabel = "";
        costLabel->setString(newLabel);
        return;
    }

    //一费
    else if (layerId == 11) {
        layerImage->setTexture("Magikarp-card.png");
        layerImage->setContentSize(Size(pictureSize, pictureSize));
    }
    else if (layerId == 12) {
        layerImage->setTexture("Buneary-card.png");
        layerImage->setContentSize(Size(pictureSize, pictureSize));
    }
    else if (layerId == 13) {
        layerImage->setTexture("Jigglypuff-card.png");
        layerImage->setContentSize(Size(pictureSize, pictureSize));
    }

    //二费
    else if (layerId == 21) {
        layerImage->setTexture("Yevee-card.png");
        layerImage->setContentSize(Size(pictureSize, pictureSize));
    }
    else if (layerId == 22) {
        layerImage->setTexture("Squirtle-card.png");
        layerImage->setContentSize(Size(pictureSize, pictureSize));
    }
    else if (layerId == 23) {
        layerImage->setTexture("Charmander-card.png");
        layerImage->setContentSize(Size(pictureSize, pictureSize));
    }
    else if (layerId == 24) {
        layerImage->setTexture("Bulbasaur-card.png");
        layerImage->setContentSize(Size(pictureSize, pictureSize));
    }
    else if (layerId == 25) {
        layerImage->setTexture("Pikachu-card.png");
        layerImage->setContentSize(Size(pictureSize, pictureSize));
    }

    //三费
    else if (layerId == 31) {
        layerImage->setTexture("Snorlax-card.png");
        layerImage->setContentSize(Size(pictureSize, pictureSize));
    }
    else if (layerId == 32) {
        layerImage->setTexture("Mewtwo-card.png");
        layerImage->setContentSize(Size(pictureSize, pictureSize));
    }
    else if (layerId == 33) {
        layerImage->setTexture("Rugia-card.png");
        layerImage->setContentSize(Size(pictureSize, pictureSize));
    }

    //价格标签
    std::string newLabel = "COST:" + std::to_string(calCostFromId(layerId));
    //不同颜色区分费用
    if (layerId / 10 == 1)
        costLabel->setColor(Color3B::WHITE);
    else if (layerId / 10 == 2)
        costLabel->setColor(Color3B::YELLOW);
    else if (layerId / 10 == 3)
        costLabel->setColor(Color3B::ORANGE);
    costLabel->setString(newLabel);
}

StoreLayer* StoreLayer::create(int id) {
    try {
        StoreLayer* layer = new StoreLayer();
        if (layer && layer->init(id)) {
            layer->autorelease();
            return layer;
        }
        CC_SAFE_DELETE(layer);
    }
    catch (const std::exception& e) {
        // 捕获到异常时的处理逻辑
        CCLOG("Exception caught: %s", e.what());
    }
	return nullptr;
}

Rect StoreLayer::getBoundingBox() const {
    if (layerImage) {
        const Vec2 origin = getPosition() ;
        return Rect(origin.x, origin.y, layerImage->getContentSize().width, layerImage->getContentSize().height);
    }
    else {
        // 如果没有 layerImage，返回一个默认的边界框
        return Rect(getPosition().x, getPosition().y, 0, 0);
    }
}

bool StoreLayer::init(int id) {


    if (!Node::init())
        throw std::runtime_error("StoreLayer initialization failed: Node initialization failed");

    //卡槽
    layerImage = Sprite::create();
    layerImage->setPosition(pictureSize / 2, pictureSize / 2);
    this->addChild(layerImage);

    //标签
    costLabel = Label::create();
    costLabel = Label::createWithTTF("", "fonts/arial.ttf", 24);
    costLabel->setColor(Color3B::BLACK);
    costLabel->setPosition(pictureSize / 2, pictureSize);
    this->addChild(costLabel);

    //刷新卡槽显示
    refreshWithId(id);

	return true;
}

int StoreLayer::calCostFromId(int id)
{
    return id / 10;
}

