// BlueBar.h
#ifndef __BLUE_BAR_H__
#define __BLUE_BAR_H__ 

#include "cocos2d.h"

class BlueBar : public cocos2d::Node
{
public:
    BlueBar();
    //创建一个蓝条
    static BlueBar* create(const std::string& backgroundFilename, const std::string& barFilename, float initialPercentage);

    virtual bool init(const std::string& backgroundFilename, const std::string& barFilename, float initialPercentage);
    //设置蓝条百分比
    void setPercentage(float percentage);

private:
    cocos2d::ProgressTimer* blueBar;
};

#endif // __BLUE_BAR_H__