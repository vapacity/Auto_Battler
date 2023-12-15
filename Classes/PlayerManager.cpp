#include "PlayerManager.h"

PlayerManager* PlayerManager::getInstance()
{
    static PlayerManager instance;
    return &instance;
}

void PlayerManager::addPlayer(Player* player)
{

    players.push_back(player);

}

Player* PlayerManager::getPlayer(int index)
{
    if (index >= 0 && index < players.size()) {

        return players[index];
    }
    return nullptr;
}
