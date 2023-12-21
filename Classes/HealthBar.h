// HealthBar.h
#ifndef __HEALTH_BAR_H__
#define __HEALTH_BAR_H__

#include "cocos2d.h"
// 再添加HealthBar时还需要加入血量值等数据
class HealthBar : public cocos2d::Node
{
public:
    static HealthBar* create();
    virtual bool initWithFile();
    virtual bool init();
    void setPercentage(float percentage); // 该函数用于扣血
    void recover();// 这里考虑到每局结束恢复血量
    void setVisibility(bool visible);// 设置是否可见
private:
    cocos2d::ProgressTimer* healthBar; // 利用ProgressTimer类实现血条变化
    bool isVisible; // 是否可见 这里考虑血条不可见的情况
};

#endif // __HEALTH_BAR_H__