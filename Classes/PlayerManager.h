#pragma once
#include "Player.h"
class PlayerManager
{
public:
    static PlayerManager* getInstance();

    void addPlayer(Player* player);//������

    Player* getPlayer(int index);//���ݱ�ŷ��������Ϣ


private:
    std::vector<Player*> players;
};