#pragma once
#include "Ball.h"
#include "Vector.h"
class CircleBumper
{
private:
	Vector c;
	float radius;
public:


	CircleBumper(void);
	CircleBumper(int, int, int);
	~CircleBumper(void);
	void Draw(void);
	void Update(void);
	void Collide(Ball*);
};

