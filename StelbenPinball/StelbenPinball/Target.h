#pragma once
#include "Ball.h"
#include "Vector.h"
class Target
{
private:
	Vector place;
	int rad;
public:
	Target(void);
	~Target(void);
	Target(int, int, int);
	void Draw(void);
	void Collide(Ball*);
	void Update();
};

