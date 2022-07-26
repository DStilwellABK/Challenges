#include <iostream>
#include "Game.h"
#include <Windows.h>
#include <conio.h>

using namespace std;

constexpr int kOpenDoorColor = 10;
constexpr int kClosedDoorColor = 10;
constexpr int kRegularColor = 10;


Game::Game()
	: m_gameOver(false)
{

}
Game::~Game() {

}

bool Game::Load() {
	return m_level.Load("level1.txt", m_player.GetXPositionPointer(), m_player.GetYPositionPointer());
}

void Game::Run() {
	Draw();
	m_gameOver = Update();

	// Draw the final state
	if (m_gameOver) {
		Draw();
	}
}



bool Game::Update() {
    char input = _getch();

    int newPlayerX = m_player.GetXPosition();
    int newPlayerY = m_player.GetYPosition();

    switch (input) {
    case 'w':
    case 'W':
    {
        newPlayerY--;
        break;
    }

    case 's':
    case 'S':
    {
        newPlayerY++;
        break;
    }

    case 'a':
    case 'A':
    {
        newPlayerX--;
        break;
    }

    case 'd':
    case 'D':
    {
        newPlayerX++;
        break;
    }

    default:
        break;
    }

    // Collision detection
    if (m_level.IsSpace(newPlayerX,newPlayerY)) {
        m_player.SetPosition(newPlayerX, newPlayerY);
    }
    else if (m_level.IsKey(newPlayerX, newPlayerY)) {
        m_level.PickupKey(newPlayerX, newPlayerY);
        m_player.PickupKey();
    
        m_player.SetPosition(newPlayerX, newPlayerY);
    }
    else if (m_level.IsDoor(newPlayerX, newPlayerY)) {
        if (m_player.HasKey()) {
            m_level.OpenDoor(newPlayerX, newPlayerY);
            m_player.UseKey();
            //PlayDoorOpenSound();
        }
        else {
            //PlayDoorClosedSound();
        }

    }
    else if (m_level.IsGoal(newPlayerX, newPlayerY)) {
        // Go to the next level
        m_player.SetPosition(newPlayerX, newPlayerY);
        //PlayWinSound();
        return true;
    }
    return false;
}

void Game::Draw() {
    for (int y = 0; y < m_level.GetHeight(); y++)
    {
        for (int x = 0; x < m_level.GetWidth(); x++)
        {
            if (m_player.GetXPosition() == x && m_player.GetYPosition() == y) {
                m_player.Draw();
            }
            else {
                HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
            
                if (m_level.IsDoor(x, y)) {
                    if (m_player.HasKey()) {
                        SetConsoleTextAttribute(console, kOpenDoorColor);
                    }
                    else {
                        SetConsoleTextAttribute(console, kClosedDoorColor);
                    }
                }
                else {
                    SetConsoleTextAttribute(console, kRegularColor);
                }
                m_level.Draw(x,y);
            }
        }
        cout << endl;
    }
}