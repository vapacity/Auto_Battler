//snorlax 1��
#ifndef SNORLAX_H

#include"cocos2d.h"
#include"Chess.h"

USING_NS_CC;

class Snorlax :public Chess
{
public:
	//createһ��
	static Snorlax* create(const std::string& filename);

	//��дinit����
	bool init(const std::string& filename);

	//���к�������������
	void breateFire();
};
#endif