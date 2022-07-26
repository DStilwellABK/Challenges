#include <iostream>
#include "Enemy.h"

Enemy::Enemy(int x, int y, int deltaX, int deltaY)
	: PlaceableActor(x, y)
	, m_currentMovementX(0)
	, m_currentMovementY(0)
	, m_directionX(0)
	, m_directionY(0)
	, m_movementInX(deltaX)
	, m_movementInY(deltaY)
{
	if (m_movementInX != 0) {
		m_directionX = 1;
	}
	if (m_movementInY != 0) {
		m_directionY = 1;
	}
}