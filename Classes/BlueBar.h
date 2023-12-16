#pragma once
#include "cocos2d.h"
#define HealthBarSize Size(100, 10) 
USING_NS_CC;

class BlueBar : public Node
{
public:
    static BlueBar* create();
    virtual bool initWithFile();
    virtual bool init();
    void setPercentage(float percentage); // 该函数用于扣血
    void setVisibility(bool visible);// 设置是否可见
    void enableTimer();
    void disableTimer();
private:
    bool isVisible;
    ProgressTimer* blueBar;
    bool timerEnabled;
    void increaseBlue(float dt);
};