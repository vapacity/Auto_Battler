//杰尼龟 1阶
#ifndef SQUIRTLE_H
#include"cocos2d.h"
#include"Chess.h"

USING_NS_CC;

class Squirtle1 :public Chess
{
public:
	//create一个杰尼龟
	static Squirtle1* create(const std::string& filename);

	//重写init方法
	virtual bool init() override;

	//特有函数。。待更新
	void breateWater();
};

class Squirtle2 :public Chess
{
public:
	//create一个杰尼龟
	static Squirtle2* create(const std::string& filename);

	//重写init方法
	virtual bool init() override;

	//特有函数。。待更新
	void breateWater();
};

class Squirtle3 :public Chess
{
public:
	//create一个杰尼龟
	static Squirtle3* create(const std::string& filename);

	//重写init方法
	virtual bool init() override;

	//特有函数。。待更新
	void breateWater();
};
#endif
