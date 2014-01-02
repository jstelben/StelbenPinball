#include "Ball.h"
#include <math.h>
#include <iostream>
#include <GL/glut.h>

struct Color
{
	float r;
	float g;
	float b;

};

//Variables
Color c;



//Constants
float const GRAVITY = -.005;

Ball::Ball(void)
{
	c.r = 155.0;
	c.b = 0.0;
	c.g = 0.0;
	Center = Vector(200,100);
	Radius = 10;
	IsFalling = true;


	Speed = Vector(0,0);
	Acceleration = Vector(0,0);
	BallActive = false;
	score = 0;
	ballsLeft = 6;
}


Ball::~Ball(void)
{

}

void Ball::Draw()
{
	glPushMatrix();
	glTranslatef(Center.X, Center.Y, 0.0f);
	glColor3f(c.r,c.b,c.g);
	glutSolidSphere(Radius, 50, 50);
	glPopMatrix();
}

void Ball::Update()
{
	//Increase acceleration downward
	if(IsFalling)
	{
		Acceleration.Y += GRAVITY;
	}
	
	//Change speed and location
	Speed.Add(Acceleration);
	Center.Add(Speed);
	//Below table
	if(Center.Y < 0 - Radius)
	{
		if(ballsLeft > 0)
		{
			SetBall();
		}
		else
		{
			//end game, kinda
			IsFalling = false;
			Speed = Vector(0,0);
			Acceleration = Vector(0,0);
		}
		
	}
}
//Resets ball above plunger
void Ball::SetBall()
{
	Speed = Vector(0,0);
	Acceleration = Vector(0,0);
	Center = Vector(380,100);
	BallActive = true;
	ballsLeft--;
}