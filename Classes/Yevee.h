//���� 1��
#ifndef YEVEE_H

#include"cocos2d.h"
#include"Chess.h"

USING_NS_CC;

class Yevee :public Chess
{
public:
	//createһ������
	static Yevee* create(const std::string& filename);

	//��дinit����
	bool init(const std::string& filename);

	virtual void useSkill() override;

	virtual void getHurt(int ATK);
};
#endif
