#include "CircleBumper.h"
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
Color cColor;
Vector c;
float radius;

//Constants
float KICK_BACK = 15;

CircleBumper::CircleBumper(void)
{

}


CircleBumper::~CircleBumper(void)
{
}

CircleBumper::CircleBumper(int x, int y, int r)
{
	c = Vector(x,y);
	radius = r;
	cColor.r = 50;
	cColor.g = 50;
	cColor.b = 50;
}

void CircleBumper::Draw()
{
	glPushMatrix();
	glTranslatef(c.X, c.Y, 0.0f);
	glColor3f(cColor.r,cColor.b,cColor.g);
	glutSolidSphere(radius, 50, 50);
	glPopMatrix();
}



void CircleBumper::Collide(Ball* b)
{
	//Check is Ball could even reach this bumper
	Vector v = b->Speed;
	if(v.GetMagnitude() >= (b->Center.GetDistance(c) - (b->Radius + radius)))
	{
		//Check if Ball is even moving towards this bumper
		Vector x = c - b->Center;
		Vector n = v.UnitVector();
		float d = n.DotProduct(x);
		if(d > 0)
		{
			//Get closest distance between Bumper and Ball Speed vector
			float f = pow(x.GetMagnitude(),2) - pow(d,2);
			//Make sure that distance is less than combined radii
			if(f < pow(b->Radius + radius, 2))
			{
				//Get distance away from f that will be where the Ball collides
				float t = pow(b->Radius + radius,2) - f;
				if(t >= 0)
				{
					// get distance from where Ball is to where it will collide
					d = d - sqrt(t);
					//Make sure this location will be reached in one update
					if(v.GetMagnitude() >= d)
					{
						//Move ball to bumper
						b->Speed = n;
						b->Speed.Multiply(d);
						b->Center.Add(b->Speed);
						
						//Change Ball movement vector with some kickback
						Vector n = b->Center - c;
						n = n.UnitVector();
						n.Multiply(KICK_BACK);
						b->Speed = b->Speed + n;
						b->score += 100;

					}
				}
			
			}
		}
	}
}