#include"Store.h"
#include"StoreLayer.h"
//include"card.h"
USING_NS_CC;
const int pictureSize = 150;
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
    else if (layerId == 11) {
        layerImage->setTexture("Yevee-card.png");
        layerImage->setContentSize(Size(pictureSize, pictureSize));
    }
    else if (layerId == 12) {
        layerImage->setTexture("Charmander-card.png");
        layerImage->setContentSize(Size(pictureSize, pictureSize));
    }
    else if (layerId == 13) {
        layerImage->setTexture("Squirtle-card.png");
        layerImage->setContentSize(Size(pictureSize, pictureSize));
    }
    else if (layerId == 14) {
        layerImage->setTexture("Squirtle-card.png");
        layerImage->setContentSize(Size(pictureSize, pictureSize));
    }

    else if (layerId == 21) {
        layerImage->setTexture("Squirtle-card.png");
        layerImage->setContentSize(Size(pictureSize, pictureSize));
    }
    else if (layerId == 22) {
        layerImage->setTexture("Squirtle-card.png");
        layerImage->setContentSize(Size(pictureSize, pictureSize));
    }
    else if (layerId == 23) {
        layerImage->setTexture("Squirtle-card.png");
        layerImage->setContentSize(Size(pictureSize, pictureSize));
    }
    else if (layerId == 24) {
        layerImage->setTexture("Squirtle-card.png");
        layerImage->setContentSize(Size(pictureSize, pictureSize));
    }
    else if (layerId == 25) {
        layerImage->setTexture("Squirtle-card.png");
        layerImage->setContentSize(Size(pictureSize, pictureSize));
    }

    else if (layerId == 31) {
        layerImage->setTexture("Squirtle-card.png");
        layerImage->setContentSize(Size(pictureSize, pictureSize));
    }
    else if (layerId == 32) {
        layerImage->setTexture("Squirtle-card.png");
        layerImage->setContentSize(Size(pictureSize, pictureSize));
    }
    else if (layerId == 33) {
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
    return id / 10;
}

