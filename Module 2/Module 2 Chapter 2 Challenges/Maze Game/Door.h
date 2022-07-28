#pragma once
#include "PlaceableActor.h"

class Door : public PlaceableActor {
public:
	Door(int x, int y, ActorColor color, ActorColor closedColor);
	virtual void Draw() override;

	bool IsOpen() { return m_isOpen; }
	void ToggleDoor(bool status) { m_isOpen = status; }

	void SetButtonToggable() { m_doorIsButtonToggable = true; }

private:
	bool m_isOpen;
	bool m_doorIsButtonToggable;
	ActorColor m_closedColor;

};