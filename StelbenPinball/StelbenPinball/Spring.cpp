#include "Spring.h"
#include <math.h>
#include <iostream>
#include <GL/glut.h>



using namespace std;

struct Color
{
	float r;
	float g;
	float b;

};

//Variables
float currentY;
Color color;
float lastY;
float vy;

//Constants
float const HOME_X = 360;
float const HOME_Y = 60;
float const WIDTH = 40;
float const HEIGHT = 20;
float const SPRING = .05;


Spring::Spring(void)
{
	color.r = 0.0;
	color.b = 155.0;
	color.g = 0.0;
	currentY = HOME_Y;
	Held = false;
	vy = 0;
}


Spring::~Spring(void)
{
}

//Called on mouseclick
//If cursor is on the spring, it is held
void Spring::IsClicked(int mouseX, int mouseY)
{
	if(mouseX > HOME_X && mouseX < HOME_X + WIDTH)
	{
		if(mouseY < currentY && mouseY > currentY - HEIGHT)
		{
			Held = true;
		}
	}
}

//Moves spring
void Spring::Update(int mouseY)
{
	lastY = currentY;
	//if held follow the mouse
	if(Held)
	{
		vy = 0;
		currentY = mouseY;
	}
	//move spring up to it's original position
	else if(currentY < HOME_Y)
	{
		float dy = HOME_Y - currentY;
		float ay = dy * SPRING;
		vy += ay;
		currentY += vy;
	}
	//Stop spring when it gets to its original position
	else
	{
		currentY = HOME_Y;
		vy = 0;
	}
}

void Spring::Draw()
{
	glPushMatrix();
	glColor3f(color.r,color.g,color.b);
	glBegin(GL_QUADS);
		glVertex3f(HOME_X, currentY, 0.0f);
		glVertex3f(HOME_X + WIDTH, currentY, 0.0f);
		glVertex3f(HOME_X + WIDTH, currentY - HEIGHT, 0.0f);
		glVertex3f(HOME_X, currentY - HEIGHT, 0.0f);
	glEnd();
	glPopMatrix();

}

//Check for collision
void Spring::Collide(Ball* b)
{
	//As long as the ball is in the spring area, don't let it go below the spring
	if(b->Center.X > HOME_X && b->Center.X < HOME_X + WIDTH)
	{
		if(b->Center.Y < currentY + b->Radius)
		{
			//Change ball speed to spring speed
			b->Acceleration.Y = 0;
			b->Speed.Y = vy;
			b->Center.Y = currentY + b->Radius;
		}
	}
	
}