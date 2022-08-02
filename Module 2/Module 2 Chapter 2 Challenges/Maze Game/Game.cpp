#include <iostream>
#include "Game.h"
#include <Windows.h>
#include <conio.h>

#include "Enemy.h"
#include "Key.h"
#include "Door.h"
#include "Goal.h"
#include "Money.h"
#include "PlaceableActor.h"
#include "Button.h"

using namespace std;

//constexpr int kOpenDoorColor = 10;
//constexpr int kClosedDoorColor = 10;
//constexpr int kRegularColor = 10;

constexpr int kArrowInput = 224;
constexpr int kLeftArrow = 75;
constexpr int kRightArrow = 77;
constexpr int kUpArrow = 72;
constexpr int kDownArrow = 80;
constexpr int kEscapeKey = 27;

Button* previousButtonPressed;

void ClearScreen();

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

bool Game::HandleCollision(int newPlayerX, int newPlayerY) {
    PlaceableActor* collidedActor = m_level.UpdateActors(newPlayerX, newPlayerY);
    if (collidedActor != nullptr && collidedActor->IsActive()) {
        Enemy* collidedEnemy = dynamic_cast<Enemy*>(collidedActor);
        if (collidedEnemy) {
            collidedEnemy->Remove();
            m_player.SetPosition(newPlayerX, newPlayerY);

            m_player.DecrementLives();
            if (m_player.GetLives() < 0) {
                return true;
            }
        }

        Money* collidedMoney = dynamic_cast<Money*>(collidedActor);
        if (collidedMoney) {
            collidedMoney->Remove();
            m_player.AddMoney(collidedMoney->GetWorth());
            m_player.SetPosition(newPlayerX, newPlayerY);
        }

        Key* collidedKey = dynamic_cast<Key*>(collidedActor);
        if (collidedKey) {
            // If the player doesn't already have a key
            if (!m_player.HasKey()) {
                m_player.PickupKey(collidedKey);
                collidedActor->Remove();
                m_player.SetPosition(newPlayerX, newPlayerY);
            }
        }

        // Setup status of the previosu button if it was toggable
        if (previousButtonPressed != nullptr) {
            previousButtonPressed->m_doorToOpen.ToggleDoor(false);
            previousButtonPressed->SetButtonStatus(false);
         
            // Finished with the previous button, now we cant set this to null
            previousButtonPressed = nullptr;
        }


        Button* collidedButton = dynamic_cast<Button*>(collidedActor);
        if (collidedButton) {

            // Set the player positon on top of the button, but don't remove the button.
            m_player.SetPosition(newPlayerX, newPlayerY);
            
            // Set the button pressed 
            collidedButton->SetButtonStatus(true);
            
            // Open the door
            collidedButton->m_doorToOpen.ToggleDoor(true);

            // Set this if it's toggable
            if (collidedButton->ButtonIsToggable())
                previousButtonPressed = collidedButton;
        }

        Door* collidedDoor = dynamic_cast<Door*>(collidedActor);
        if (collidedDoor) {
            // If the collided door is not already Open
            if (!collidedDoor->IsOpen()) {
                if (m_player.HasKey(collidedDoor->GetColor())) {
                    // Opens the door
                    collidedDoor->ToggleDoor(true);
                    collidedButton->SetButtonStatus(false);
                    collidedDoor->Remove();
                    m_player.UseKey();
                    m_player.SetPosition(newPlayerX, newPlayerY);

                }
                else {

                }
            }
            else {
                m_player.SetPosition(newPlayerX, newPlayerY);
            }
        }
        Goal* collidedGoal = dynamic_cast<Goal*>(collidedActor);
        if (collidedGoal) {
            collidedGoal->Remove();
            m_player.SetPosition(newPlayerX, newPlayerY);
            return true;
        }
    }
    else if (m_level.IsSpace(newPlayerX, newPlayerY)) {
        m_player.SetPosition(newPlayerX, newPlayerY);
    }
    else if (m_level.IsWall(newPlayerX, newPlayerY)) {
        // Is a wall, do nothing.
    }

    return false;
}


bool Game::Update() {
    char input = _getch();

    int newPlayerX = m_player.GetXPosition();
    int newPlayerY = m_player.GetYPosition();
    int arrowInput = 0;

    // One of the Arrow keys was pressed here
    if (input == kArrowInput) {
        arrowInput = _getch();
    }

    if ((input == kArrowInput && arrowInput == kLeftArrow)
        || (char)input == 'A'
        || (char)input == 'a') {
        newPlayerX--;
    }

    else if ((input == kArrowInput && arrowInput == kRightArrow)
        || (char)input == 'D'
        || (char)input == 'd') {
        newPlayerX++;
    }

    else if ((input == kArrowInput && arrowInput == kUpArrow)
        || (char)input == 'W'
        || (char)input == 'w') {
        newPlayerY--;
    }


    else if ((input == kArrowInput && arrowInput == kDownArrow)
        || (char)input == 'S'
        || (char)input == 's') {
        newPlayerY++;
    }

    else if (input == kEscapeKey) {
        m_UserQuit = true;
        return true;
    }
    else if ((char)input == 'Z' || (char)input == 'z') {
        m_player.DropKey();
    }

    if (newPlayerX == m_player.GetXPosition() && newPlayerY == m_player.GetYPosition()) {
        return false;
    }
    else {
        return HandleCollision(newPlayerX, newPlayerY);
    }
}

void ClearScreen()
{
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}


void Game::Draw() {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    ClearScreen();
    
    m_level.Draw();

    COORD actorCursorPosition;
    actorCursorPosition.X = m_player.GetXPosition();
    actorCursorPosition.Y = m_player.GetYPosition();
    SetConsoleCursorPosition(console, actorCursorPosition);
    m_player.Draw();

    COORD currentCursorPosition;
    currentCursorPosition.X = 0;
    currentCursorPosition.X = m_level.GetHeight();
    SetConsoleCursorPosition(console, currentCursorPosition);
}