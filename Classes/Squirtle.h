//����� 1��
#ifndef SQUIRTLE_H
#include"cocos2d.h"
#include"Chess.h"

USING_NS_CC;

class Squirtle1 :public Chess
{
public:
	//createһ�������
	static Squirtle1* create(const std::string& filename);

	//��дinit����
	virtual bool init() override;

	//���к�������������
	void breateWater();
};

class Squirtle2 :public Chess
{
public:
	//createһ�������
	static Squirtle2* create(const std::string& filename);

	//��дinit����
	virtual bool init() override;

	//���к�������������
	void breateWater();
};

class Squirtle3 :public Chess
{
public:
	//createһ�������
	static Squirtle3* create(const std::string& filename);

	//��дinit����
	virtual bool init() override;

	//���к�������������
	void breateWater();
};
#endif
