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
	bool init(const std::string& filename);

	virtual void useSkill() override;

	virtual void getHurt(int ATK);
};
#endif
