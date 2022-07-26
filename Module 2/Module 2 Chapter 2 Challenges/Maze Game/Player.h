#pragma once
#include "PlaceableActor.h"
#include "Key.h"

class Key;

class Player : public PlaceableActor {



public:
	Player();
	~Player();
	
	void AddMoney(int money) { m_money += money; }
	int GetMoney() { return m_money; }

	int GetLives() { return m_lives; }
	void DecrementLives() { m_lives--; }

	bool HasKey();
	bool HasKey(int colr);
	void PickupKey(Key* key);
	void UseKey();
	void DropKey();

	virtual void Draw() override;


private:
	Key* m_pCurrentKey;
	int m_money;
	int m_lives;
};