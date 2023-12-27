#ifndef __GameOver_SCENE_H__
#define __GameOver_SCENE_H__
#include "cocos2d.h"
#include "PlayerManager.h"
class StartScene;
class GameOverScene :public cocos2d::Scene
{
public:
	Player* myPlayer = PlayerManager::getInstance()->getPlayer(0);
	Player* enemyPlayer=PlayerManager::getInstance()->getPlayer(1);
public:
	static cocos2d::Scene* createScene();
	// ��ʼ�������ķ���
	virtual bool init() override;
	void goToStartScene();
	CREATE_FUNC(GameOverScene);
};
#endif