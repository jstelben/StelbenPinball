#pragma once
#include "Ball.h"
#include "Vector.h"

class Box
{

public:
	Vector topLeft;
	Vector topRight;
	Vector botLeft;
	Vector botRight;
	Box(void);
	~Box(void);
	Box(float, float, float, float);
	void Draw(void);
	void Collide(Ball*);
};

