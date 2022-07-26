#pragma once
#include "PlaceableActor.h"

class Key : public PlaceableActor {
public:
	Key(int x, int color) 
		: PlaceableActor(x,y,color)
	{

	}
	virtual void Draw() override;
};