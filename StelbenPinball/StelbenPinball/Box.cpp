#include "Box.h"
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
Color bColor;
Box::Box(void)
{
}


Box::~Box(void)
{
}

Box::Box(float x, float y, float w, float h)
{
	//Makes 4 vectors to serve as corners
	topLeft = Vector(x,y);
	topRight = Vector(x + w, y);
	botLeft = Vector (x, y - h);
	botRight = Vector(x + w, y - h);
	bColor.r = 0;
	bColor.b = 50;
	bColor.g = 50;
}

//Draws the box
void Box::Draw()
{
	
	glPushMatrix();
	glColor3f(bColor.r,bColor.g,bColor.b);
	glBegin(GL_QUADS);
		glVertex3f(topLeft.X, topLeft.Y, 0.0f);
		glVertex3f(topRight.X, topRight.Y, 0.0f);
		glVertex3f(botRight.X, botRight.Y, 0.0f);
		glVertex3f(botLeft.X, botLeft.Y, 0.0f);
	glEnd();
	glPopMatrix();
}

//Collision along one of the sides
void bounceBall(Ball* b, Vector y, Vector x)
{
	//Get vector between two points of the side
	Vector d = y - x;
	//Gets normal of the side
	Vector n1 = Vector(-d.Y, d.X);
	n1 = n1.UnitVector();
	//Gets vector between Ball and one of the points
	d = y - b->Center;
	//Shortest distance from ball to the side
	float distanceToLine = d.DotProduct(n1);
	//If the distance is greater than teh ball radius
	if(distanceToLine > b->Radius || distanceToLine + b->Radius < b->Radius)
	{
		//Get Ball's next location
		Vector nextLocation = b->Center + b->Speed;
		//Distance from next location to the side
		d = y - nextLocation;
		//Shortest distance from Ball's next location to the side
		float nextDistanceToLine = d.DotProduct(n1);
		//Time when Ball will be next to the line
		float time = (b->Radius - distanceToLine) / (nextDistanceToLine - distanceToLine);
		//If the Ball will be next to the line within this update
		if(time > 0 && time <= 1.03)
		{
			//Gets location of Ball on the line
			Vector moveToLine = b->Speed;
			moveToLine.Multiply(time);
			moveToLine = b->Center + moveToLine;
			//Checks which side the line is
			if(x.X == y.X)
			{
				//Make sure Location is on the line segment and not just the line
				if((moveToLine.Y >= x.Y - b->Radius && moveToLine.Y <= y.Y + b->Radius) || (moveToLine.Y >= y.Y - b->Radius && moveToLine.Y <= x.Y + b->Radius))
				{
					//std::cout << "Collide with Box" << std::endl;

					//Make ball bounce off verticle line
					b->Center = moveToLine;
					b->Speed.X = -b->Speed.X;
					b->score += 50;
				}
			}
			else if(x.Y == y.Y)
			{
			
				if((moveToLine.X > x.X - b->Radius && moveToLine.X < y.X + b->Radius) || (moveToLine.X >y.X - b->Radius && moveToLine.X < x.X + b->Radius))
				{
					//std::cout << "Collide with Box" << std::endl;
					//Make ball bounce off horizontal line
					b->Center = moveToLine;
					b->Speed.Y = -b->Speed.Y;
					b->score += 50;
					
				}
			}
		}
	}
}

//Checks for collision on each side of the box
void Box::Collide(Ball* b)
{
	if(b->Center.X > topRight.X)
	{
		bounceBall(b, topRight, botRight);
	}
	if(b->Center.X < topLeft.X)
	{
		bounceBall(b, botLeft, topLeft);
	}
	if(b->Center.Y > topLeft.Y)
	{
		bounceBall(b, topLeft, topRight);
	}
	if(b->Center.Y < botLeft.Y)
	{
		bounceBall(b,botRight, botLeft);
	}


	
	
}



