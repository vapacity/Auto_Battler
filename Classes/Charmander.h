#ifndef CHARMANDER_H
#include"cocos2d.h"
#include"Chess.h"

USING_NS_CC;

class Charmander :public Chess
{
public:
	//createһ��С����
	static Charmander* create(const std::string& filename);

	//��дinit����
	virtual bool init() override;

	//���к�������������
	void breateFire();
};
#endif
