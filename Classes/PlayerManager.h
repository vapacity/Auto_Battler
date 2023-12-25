#pragma once
#include "Player.h"
class PlayerManager
{
public:
    static PlayerManager* getInstance();

    void addPlayer(Player* player);

    Player* getPlayer(int index);

    // 其他管理方法...

    static int getPlayerNum();
    

private:
    std::vector<Player*> players;

};