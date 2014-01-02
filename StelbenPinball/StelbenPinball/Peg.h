#pragma once
#include "Ball.h"
#include "Vector.h"
class Peg
{
private:
	Vector position;
	float r;
public:
	Peg(void);
	Peg(int, int, int);
	~Peg(void);
	void Draw(void);
	void Update(void);
	void Collide(Ball*);
};

