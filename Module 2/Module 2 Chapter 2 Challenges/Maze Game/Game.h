#pragma once
#include "Player.h"
#include "Level.h"

class Game {
	Player m_player;
	Level m_level;
	bool m_gameOver;

public: 
	Game();
	~Game();

	bool Load();

	void Run();

	bool IsGameOver() { return m_gameOver; }

private:
	bool Update();
	void Draw();
};