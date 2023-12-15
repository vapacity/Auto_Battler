//伊布 1阶
#ifndef YEVEE_H

#include"cocos2d.h"
#include"Chess.h"

USING_NS_CC;

class Yevee :public Chess
{
public:
	//create一个伊布
	static Yevee* create(const std::string& filename);

	//重写init方法
	virtual bool init() override;

	//特有函数。。待更新
	void breateFire();
};
#endif
