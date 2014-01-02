#include "TriangleBumper.h"
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
Color tColor;
int const KICK_BACK = 1.5;


TriangleBumper::TriangleBumper(void)
{
}

TriangleBumper::TriangleBumper(float p1x, float p1y, float p2x, float p2y, float p3x, float p3y)
{
	
	p1 = Vector(p1x,p1y);
	p2 = Vector(p2x,p2y);
	p3 = Vector(p3x,p3y);
	tColor.r = 0;
	tColor.g = 155;
	tColor.b = 0;
}


TriangleBumper::~TriangleBumper(void)
{
}

void TriangleBumper::Draw()
{
	glPushMatrix();
	glColor3f(tColor.r,tColor.g,tColor.b);
	glBegin(GL_TRIANGLES);
		glVertex3f(p1.X, p1.Y, 0.0f);
		glVertex3f(p2.X, p2.Y, 0.0f);
		glVertex3f(p3.X, p3.Y, 0.0f);
	glEnd();
	glPopMatrix();
}



//Check for collision with ball
//Check Box::BounceBall for how it works
void TriangleBumper::Collide(Ball* b)
{
	Vector d = p3 - p1;
	Vector n1 = Vector(-d.Y, d.X);
	n1 = n1.UnitVector();
	d = p1 - b->Center;
	float distanceToLine = d.DotProduct(n1);
	Vector nextLocation = b->Center + b->Speed;
	d = p3 - nextLocation;
	float nextDistanceToLine = d.DotProduct(n1);
	float time = (b->Radius - distanceToLine) / (nextDistanceToLine - distanceToLine);
	if(time > 0 && time <= 1)
	{
	

		Vector moveToLine = b->Speed;
		moveToLine.Multiply(time);
		moveToLine = b->Center + moveToLine;
		
		if((moveToLine.X > p1.X - b->Radius && moveToLine.X < p3.X + b->Radius) || (moveToLine.X >p3.X - b->Radius && moveToLine.X < p1.X + b->Radius))
		{
			if((moveToLine.Y > p1.Y -b->Radius && moveToLine.Y < p3.Y + b->Radius) || (moveToLine.Y > p3.Y -b->Radius && moveToLine.Y < p1.Y + b->Radius))
			{



				b->Center = moveToLine;



				n1 = n1.UnitVector();
				n1 = n1.Project(b->Speed);
				n1.Multiply(-1);
				n1.Multiply(KICK_BACK);
				b->Speed = n1;
				b->score += 250;
			}
		}
		
	}
}