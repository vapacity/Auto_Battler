// HealthBar.h
#ifndef __HEALTH_BAR_H__
#define __HEALTH_BAR_H__

#include "cocos2d.h"
// �����HealthBarʱ����Ҫ����Ѫ��ֵ������
class HealthBar : public cocos2d::Node
{
public:
    static HealthBar* create();
    virtual bool initWithFile();
    virtual bool init();
    void setPercentage(float percentage); // �ú������ڿ�Ѫ
    void recover();// ���￼�ǵ�ÿ�ֽ����ָ�Ѫ��
    void setVisibility(bool visible);// �����Ƿ�ɼ�
private:
    cocos2d::ProgressTimer* healthBar; // ����ProgressTimer��ʵ��Ѫ���仯
    bool isVisible; // �Ƿ�ɼ� ���￼��Ѫ�����ɼ������
};

#endif // __HEALTH_BAR_H__