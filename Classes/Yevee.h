//���� 1��
#ifndef YEVEE_H

#include"cocos2d.h"
#include"Chess.h"

USING_NS_CC;

class Yevee1 :public Chess
{
public:
	//createһ������
	static Yevee1* create(const std::string& filename);

	//��дinit����
	virtual bool init() override;

	//���к�������������
	void breateFire();
};
class Yevee2 : public Chess
{
public:
	//createһ������
	static Yevee2* create(const std::string& filename);

	//��дinit����
	virtual bool init() override;

	//���к�������������
	void breateFire();
};

class Yevee3 :public Chess
{
public:
	//createһ������
	static Yevee3* create(const std::string& filename);

	//��дinit����
	virtual bool init() override;

	//���к�������������
	void breateFire();
};
#endif
