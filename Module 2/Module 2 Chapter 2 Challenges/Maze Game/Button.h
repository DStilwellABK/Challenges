#pragma once
#include "PlaceableActor.h"
#include "Door.h"

class Button : public PlaceableActor {
public:
	Door m_doorToOpen;
	Button(int x, int y, Door doorToOpen);
	virtual void Draw() override;

	bool IsButtonPressed() { return m_isPressed; }
	bool ButtonIsToggable() { return m_toggable; }
	void SetToggable() { m_toggable = true; }

	void SetButtonStatus(bool status) { m_isPressed = status; }


private:
	bool m_toggable;
	bool m_isPressed;
};