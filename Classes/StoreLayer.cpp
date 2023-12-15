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

    std::string newLabel = "COST:" + std::to_string(layerId / 3 + 1);
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
        Vec2 origin = getPosition() - Vec2(layerImage->getContentSize().width / 2, layerImage->getContentSize().height / 2);
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

