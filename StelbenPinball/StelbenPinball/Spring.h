#pragma once
#include "Ball.h"
class Spring
{
public:
	Spring(void);
	~Spring(void);
	void IsClicked(int mouseX, int mouseY);
	void Update(int mouseY);
	void Draw();
	void Collide(Ball* b);
	bool Held;
};

