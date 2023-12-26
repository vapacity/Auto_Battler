// HealthBar.h
#ifndef __HEALTH_BAR_H__
#define __HEALTH_BAR_H__ 

#include "cocos2d.h"

class HealthBar : public cocos2d::Node
{
public:
    HealthBar();

    static HealthBar* create(const std::string& backgroundFilename, const std::string& barFilename, float initialPercentage);

    virtual bool init(const std::string& backgroundFilename, const std::string& barFilename, float initialPercentage);

    void setPercentage(float percentage);

private:
    cocos2d::ProgressTimer* healthBar;
};

#endif // __HEALTH_BAR_H__