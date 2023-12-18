#include"Store.h"
#include"StoreLayer.h"
//include"card.h"
USING_NS_CC;

//storelayer添加在卡槽左下角

void StoreLayer::refreshWithId(int id)
{
    layerId = id;

    if (layerId == -2) {
        layerImage->setTexture("captureFailed.jpg");
        layerImage->setContentSize(Size(pictureSize, pictureSize));
        std::string newLabel = "";
        costLabel->setString(newLabel);
        return;
    }
    if (layerId == -1) {
        layerImage->setTexture("03.jpg");
        layerImage->setContentSize(Size(pictureSize, pictureSize));
        std::string newLabel = "";
        costLabel->setString(newLabel);
        return;
    }
    //须改
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

    std::string newLabel = "COST:" + std::to_string(calCostFromId(layerId));
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

Rect StoreLayer::getBoundingBox() const {
    if (layerImage) {
        Vec2 origin = getPosition() ;
        return Rect(origin.x, origin.y, layerImage->getContentSize().width, layerImage->getContentSize().height);
    }
    else {
        // 如果没有 layerImage，返回一个默认的边界框
        return Rect(getPosition().x, getPosition().y, 0, 0);
    }
}

bool StoreLayer::init(int id) {


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

int StoreLayer::calCostFromId(int id)
{
    if (id < COST1_Amount)
        return 1;
    id -= COST1_Amount;
    if (id < COST2_Amount)
        return 2;
    id -= COST2_Amount;
    if (id < COST3_Amount)
        return 3;
    return 0;
}

