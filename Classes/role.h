/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __ROLE_H__
#define __ROLE_H__

#include <cstring>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "player.h"
USING_NS_CC;
class role
{
public:
	friend class player;
	virtual void attack();//攻击函数

	void moveTo();//移动函数

	virtual void getHurt();//掉血函数

	virtual void useSkill();//使用技能

protected:
	std::string name;//名字
	std::string picture;//图片
	float X;//坐标
	float Y;
	int HP;//红条
	int MP;//蓝条
	int ATK;//攻击力
	int attackSpeed;//攻击速度
	int moveSpeed;//移动速度
	int attackRange;//攻击范围
	int price;//价格
};
#endif // __ROLE_H__

