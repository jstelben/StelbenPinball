#pragma once
#include "Ball.h"
#include "Vector.h"
class TriangleBumper
{



public:
	Vector p1;
	Vector p2;
	Vector p3;
	TriangleBumper(void);
	TriangleBumper(float, float, float, float, float, float);
	~TriangleBumper(void);
	void Update(void);
	void Draw(void);
	void Collide(Ball*);
};

