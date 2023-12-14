//杰尼龟 1阶
#ifndef SQUIRTLE_H
#include"cocos2d.h"
#include"Chess.h"

USING_NS_CC;

class Squirtle :public Chess
{
public:
	//create一个杰尼龟
	static Squirtle* create(const std::string& filename);

	//重写init方法
	virtual bool init() override;

	//特有函数。。待更新
	void breateWater();
};
#endif
