#include "Flipper.h"
#include <math.h>
#include <iostream>
#include <GL/glut.h>
#define PI 3.14159

//Variables
struct Color
{
	float r;
	float g;
	float b;

};
Color fColor;
int const KICK_BACK = 1.1;

Flipper::Flipper(void)
{
}


Flipper::~Flipper(void)
{
}

Flipper::Flipper(float x1, float y1, float x2, float y2, float x3, float y3, float rx, float ry)
{
	f1 = Vector(x1,y1);
	f2 = Vector(x2,y2);
	f3 = Vector(x3,y3);
	permf1 = f1;
	permf2 = f2;
	permf3 = f3;
	fColor.r = 50;
	fColor.b = 50;
	fColor.g = 0;
	angle = 0;
	rotationPoint = Vector(rx,ry); 
	held = false;
}

void Flipper::Draw()
{
	glPushMatrix();
	glColor3f(fColor.r, fColor.b, fColor.g);
	glBegin(GL_TRIANGLES);
		glVertex3f(f1.X, f1.Y, 0.0f);
		glVertex3f(f2.X, f2.Y, 0.0f);
		glVertex3f(f3.X, f3.Y, 0.0f);
	glEnd();
	glPopMatrix();
	
}

//Rotates flippers
void Flipper::Update(bool isHeld, char flipper)
{
	held = isHeld;
	if(flipper == 'l')
	{
		if(held)
	{
		if(angle < 45)
		{
			angle+=5;
		}
	}
	else 
	{
		if(angle > 0)
		{
			angle -=5;
		}
	}
	}
	if(flipper == 'r')
	{
		if(held)
		{
			if(angle > -45)
			{
				angle-=5;
			}
			
		}
		else 
		{
			if(angle < 0)
			{
				angle += 5;
			}
		}
	}
	float radian = (angle/180) * PI;
	float s = sin(radian);
	float c = cos(radian);
	f1 = permf1;
	f2 = permf2;
	f3 = permf3;
	f1.Rotate(rotationPoint, s, c);
	f2.Rotate(rotationPoint, s, c);
	f3.Rotate(rotationPoint, s, c);
}

//Bounce ball off flipper.  Check Box::BounceBall for how it works
void Flipper::BounceBall(Ball* b , Vector leftP, Vector rightP, Vector topP, Vector botP, bool isHeld)
{
	Vector d = rightP - leftP;
	Vector n1 = Vector(d.Y, -d.X);
	n1 = n1.UnitVector();
	d = leftP - b->Center;
	float distanceToLine = d.DotProduct(n1);
	Vector nextLocation = b->Center + b->Speed;
	d = rightP - nextLocation;
	float nextDistanceToLine = d.DotProduct(n1);
	float time = (b->Radius - distanceToLine) / (nextDistanceToLine - distanceToLine);
	if(time > 0 && time <= 1)
	{


		Vector moveToLine = b->Speed;
		moveToLine.Multiply(time);
		moveToLine = b->Center + moveToLine;
		//Make sure ball is within line segment
		if((moveToLine.X > leftP.X - b->Radius && moveToLine.X < rightP.X + b->Radius) || (moveToLine.X > rightP.X + b->Radius && moveToLine.X < leftP.X - b->Radius))
		{
			if((moveToLine.Y > botP.Y - b->Radius && moveToLine.Y < topP.Y + b->Radius) || (moveToLine.Y > botP.Y - b->Radius && moveToLine.Y < topP.Y + b->Radius))
			{

				b->Center = moveToLine;
				n1 = n1.UnitVector();
				n1 = n1.Project(b->Speed);
				n1.Multiply(-1);

				//While the flipper is moving it will give some kick to the ball
				//Instead of calculating angular momentum and conserving momentum
				//Looks good enough
				if(isHeld)
				{
					n1.Multiply(1.1);
				}
				
				b->Speed = n1;
				b->score += 10;
			}
		}
		
		
	}
}

//Check for Collision of Ball on flipper
void Flipper::Collide(Ball* b)
{
	Vector left;
	Vector right;
	Vector top;
	Vector bot;
	if(f1.X > f3.X)
	{
		left = f3;
		right = f1;
	}
	else
	{
		left = f1;
		right = f3;
	}
	if(f1.Y > f3.Y)
	{
		top = f1;
		bot = f3;
	}
	else
	{
		top = f3;
		bot = f1;
	}
	BounceBall(b,left,right,top,bot, held);
}



