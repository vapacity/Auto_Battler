//����� 1��
#ifndef SQUIRTLE_H
#include"cocos2d.h"
#include"Chess.h"

USING_NS_CC;

class Squirtle :public Chess
{
public:
	//createһ�������
	static Squirtle* create(const std::string& filename);

	//��дinit����
	virtual bool init() override;

	//���к�������������
	void breateWater();
};
#endif
