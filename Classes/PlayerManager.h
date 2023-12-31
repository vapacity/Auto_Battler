#pragma once
#include "Player.h"
class PlayerManager
{
public:
    static PlayerManager* getInstance();

    void addPlayer(Player* player);//添加玩家

    Player* getPlayer(int index);//根据编号返回玩家信息


private:
    std::vector<Player*> players;
};