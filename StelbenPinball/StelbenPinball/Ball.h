#pragma once
#include "Vector.h"
class Ball
{
public:
	Ball(void);
	~Ball(void);
	void Draw(void);
	void Update(void);
	void SetBall(void);
	bool BallActive;
	float Radius;
	Vector Center;
	Vector Speed;
	Vector Acceleration;
	float IsFalling;
	int score;
	int ballsLeft;
};

