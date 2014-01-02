#include "Target.h"
#include <math.h>
#include <iostream>
#include <GL/glut.h>

//Variables
struct Color
{
	float r;
	float g;
	float b;

};
Color tOutColor;
Color tInColor;

int wait;

Target::Target(void)
{
}


Target::~Target(void)
{
}

Target::Target(int x, int y, int r)
{
	place = Vector(x,y);
	rad = r;
	tInColor.r = 50;
	tInColor.g = 50;
	tInColor.b = 50;
	tOutColor.r = 0;
	tOutColor.g = 0;
	tOutColor.b = 0;

	wait = 0;
}

void Target::Draw()
{
	glPushMatrix();
	glTranslatef(place.X, place.Y, 0.0f);
	glColor3f(tOutColor.r,tOutColor.b,tOutColor.g);
	glutSolidSphere(rad, 50, 50);
	glColor3f(tInColor.r,tInColor.b,tInColor.g);
	glutSolidSphere(rad / 2, 50, 50);
	glPopMatrix();
}

//Check for collision with ball
//Check CircleBumper::Collide for how it works
void Target::Collide(Ball* b)
{
	Vector v = b->Speed;
	if(v.GetMagnitude() >= (b->Center.GetDistance(place) - (b->Radius + rad)))
	{
		Vector x = place - b->Center;
		Vector n = v.UnitVector();
		float d = n.DotProduct(x);
		if(d > 0)
		{
			float f = pow(x.GetMagnitude(),2) - pow(d,2);
			if(f < pow(b->Radius + rad, 2))
			{
			
				float t = pow(b->Radius + rad,2) - f;
				if(t >= 0)
				{
					d = d - sqrt(t);
					if(v.GetMagnitude() >= d)
					{
						//adds score and makes colors change for a bit
						wait = 120;
						b->score += 1000;
					}
				}
			
			}
		}
	}
}

//Changes colors of the rings
void Target::Update()
{
	if(wait > 0)
	{
		if(wait % 10 == 0)
		{
			Color temp = tInColor;
			tInColor = tOutColor;
			tOutColor = temp;
		}
		wait--;
	}
	else
	{
		tInColor.r = 50;
		tInColor.g = 50;
		tInColor.b = 50;
		tOutColor.r = 0;
		tOutColor.g = 0;
		tOutColor.b = 0;
	}
}