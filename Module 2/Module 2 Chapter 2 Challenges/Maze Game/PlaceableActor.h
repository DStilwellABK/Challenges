#pragma once
#include "Point.h"



enum class ActorColor {
	Regular = 7,
	Red = 12,
	Green = 10,
	Blue = 9,
	SolidRed = 68,
	SolidGreen = 34,
	SolidBlue = 153,
};

class PlaceableActor {

	public: 
		PlaceableActor(int x, int y, ActorColor color = ActorColor::Regular);
		virtual ~PlaceableActor();

		int GetXPosition();
		int GetYPosition();
		int* GetXPositionPointer();
		int* GetYPositionPointer();

		void SetPosition(int x, int y);

		ActorColor GetColor() { return m_color; }

		void Remove() { m_IsActive = false; }

		bool IsActive() { return m_IsActive; }
		void Place(int x, int y);

		virtual void Draw() = 0;
		virtual void Update() {

		}

	protected:
		Point* m_pPosition;

		bool m_IsActive;
		ActorColor m_color;
};