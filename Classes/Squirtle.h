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
	bool init(const std::string& filename);

	virtual void useSkill() override;
};

#endif
