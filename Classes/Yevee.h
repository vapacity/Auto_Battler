//���� 1��
#ifndef YEVEE_H

#include"cocos2d.h"
#include"Chess.h"

USING_NS_CC;

class Yevee :public Chess
{
public:
	//createһ��С����
	static Yevee* create(const std::string& filename);

	//��дinit����
	virtual bool init() override;

	//���к�������������
	void breateFire();
};
#endif
