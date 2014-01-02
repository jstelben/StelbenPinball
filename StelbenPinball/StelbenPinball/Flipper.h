#pragma once
#include "Vector.h"
#include "Ball.h"
class Flipper
{
public:
	Vector f1;
	Vector f2;
	Vector f3;
	float angle;
	Vector permf1;
	Vector permf2;
	Vector permf3;
	Vector rotationPoint;
	bool held;
	Flipper(void);
	~Flipper(void);
	Flipper(float, float, float, float, float, float, float, float);
	void Update(bool, char);
	void Collide(Ball*);
	void Draw(void);
	void BounceBall(Ball*,Vector,Vector,Vector,Vector, bool);
};

