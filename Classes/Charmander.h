//С���� 1��
#ifndef CHARMANDER_H
#include"cocos2d.h"
#include"Chess.h"

USING_NS_CC;

class Charmander1 :public Chess
{
public:
	//createһ��С����
	static Charmander1* create(const std::string& filename);

	//��дinit����
	virtual bool init() override;

	//���к�������������
	void breateFire();
};

class Charmander2 :public Chess
{
public:
	//createһ��С����
	static Charmander2* create(const std::string& filename);

	//��дinit����
	virtual bool init() override;

	//���к�������������
	void breateFire();
};

class Charmander3 :public Chess
{
public:
	//createһ��С����
	static Charmander3* create(const std::string& filename);

	//��дinit����
	virtual bool init() override;

	//���к�������������
	void breateFire();
};
#endif
