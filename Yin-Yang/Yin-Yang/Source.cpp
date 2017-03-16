#include <iostream>
#include <gl/glut.h>
#include <math.h>

using namespace std;

void setTransformations();
void draw();
void drawAxis();
void drawCircle();
void drawSinWave();
void drawInnerCircles();

#define PI 3.14159

void initialize(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 400);
	glutCreateWindow("Assignment 1 - Yin-Yang Symbol");
	glutDisplayFunc(draw);
	setTransformations();
	glutMainLoop();
}

void setTransformations()
{
	glClearColor(0.4, 0.7, 0.5, 1.0); // Set Background color
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100, 100, -100, 100);
}

void drawAxis(){
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(10);
	glBegin(GL_LINES);
	glVertex2f(-100, 0);
	glVertex2f(100, 0);
	glVertex2f(0, 100);
	glVertex2f(0, -100);
	glEnd();

}

void drawCircle(){
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_TRIANGLE_FAN);

	for (double x = 0; x < PI; x += 0.01){				//Draw the black half of the circle
		glVertex2f(50 * cos(x), 25 * sin(x));
	}

	glEnd();

	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLE_FAN);

	for (double x = PI; x < 2 * PI; x += 0.01){			//Draw the white half of the circle
		glVertex2f(50 * cos(x), 25 * sin(x));
	}

	glEnd();
}

void drawInnerCircles(){
	glColor3f(0.0, 0.0, 0.0);

	glBegin(GL_TRIANGLE_FAN);
	for (double x = 0; x < 2 * PI; x += 0.01){			//Draw the small black circle
		glVertex2f(3.5* cos(x), 7 * sin(x) + 25);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 1, 1);
	for (double x = 0; x < 2 * PI; x += 0.01){			//Draw the small white circle
		glVertex2f(3.5 * cos(x), 7 * sin(x) - 25);
	}
	glEnd();
}

void drawSinWave(){
	glColor3f(1, 1, 1);
	glPointSize(1);
	glBegin(GL_TRIANGLE_FAN);

	for (double x = 0; x < PI; x += 0.01){				//Draw 1/2 a sin wave in white
		float i = 3.35 *sin(x);
		glVertex2f(15 * i, 9 * sin(i));
	}
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_TRIANGLE_FAN);
	for (double x = PI; x < 2 * PI; x += 0.01){			//Draw 1/2 a sin wave in black
		float i = 3.35 *sin(x);
		glVertex2f(15 * i, 8 * sin(i));
	}
	glEnd();
}

void drawYingYang(){
	glPushMatrix();										//this is a stack so we rotate first then draw
	glRotated(90, 0, 0, 1);								//Rotating the circle by 90'
	drawCircle();										//Drawing the circle
	glPopMatrix();

	glPushMatrix();										//this is a stack so we rotate first then draw
	glRotated(91.8, 0, 0, 1);							//Rotating the sin wave by 91.8'
	drawSinWave();										//Drawing the sin wave
	glPopMatrix();

	drawInnerCircles();									//Drawing the inner circles
}

void draw(){

	glColor3f(0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	drawYingYang();										//Draw the Yin-Yang Symbol
	glFlush();
}

int main(int argc, char *argv[]){
	initialize(argc, argv);
	return 0;
}
