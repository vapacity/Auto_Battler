#include "Player.h"

Player* Player::create()
{
	Player* p = new (std::nothrow) Player();
	if (p && p->init()) {
		p->autorelease();
		return p;
	}
	CC_SAFE_DELETE(p);
	return nullptr;
}

bool Player::init()
{
	if (!Node::init()) {
		return false;
	}

	playerStore = StoreAttribute::create();

	for(int i=0;i<SEATS_NUM;i++){
		mySeats[i] = nullptr;
	}

	
}
