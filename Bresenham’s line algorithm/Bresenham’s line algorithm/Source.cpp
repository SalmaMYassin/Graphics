#include <iostream>
#include <gl/glut.h>
#include <math.h>

using namespace std;

void setTransformations();
void draw();
void drawAxis();
void Bresenham(int x1, int y1, int x2, int y2);
void setPixel(int x, int y);
void KB(unsigned char key, int x, int y);

void initialize(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 400);
	glutCreateWindow("Assignment 1 - Bresenham’s line algorithm");
	glutDisplayFunc(draw);
	glutKeyboardFunc(KB);
	setTransformations();
	glutMainLoop();
}

void setTransformations()
{
	glClearColor(0.992, 0.961, 0.902, 1.0); // Set foreground color
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100, 100, -100, 100);
}

void setPixel(int x, int y){
	glPointSize(4);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void Bresenham(int x1, int y1, int const x2, int const y2)
{
	int dx(x2 - x1);
	// if x1 == x2, then it does not matter what we set here
	signed char const ix((dx > 0) - (dx < 0));
	dx = std::abs(dx) << 1;

	int dy(y2 - y1);
	// if y1 == y2, then it does not matter what we set here
	signed char const iy((dy > 0) - (dy < 0));
	dy = std::abs(dy) << 1;

	setPixel(x1, y1);

	if (dx >= dy)
	{
		// error may go below zero
		int error(dy - (dx >> 1));

		while (x1 != x2)
		{
			if ((error >= 0) && (error || (ix > 0)))
			{
				error -= dx;
				y1 += iy;
			}
			// else do nothing

			error += dy;
			x1 += ix;

			setPixel(x1, y1);
		}
	}
	else
	{
		// error may go below zero
		int error(dx - (dy >> 1));

		while (y1 != y2)
		{
			if ((error >= 0) && (error || (iy > 0)))
			{
				error -= dy;
				x1 += ix;
			}
			// else do nothing

			error += dx;
			y1 += iy;

			setPixel(x1, y1);
		}
	}
}

void KB(unsigned char key, int x, int y){
	switch (key){
	case '1':
		glClear(GL_COLOR_BUFFER_BIT);
		drawAxis();
		Bresenham(10, 10, 70, 70);
		glFlush();
		break;

	case '2':
		glClear(GL_COLOR_BUFFER_BIT);
		drawAxis();
		Bresenham(-10, 10, -70, 70);
		glFlush();
		break;

	case '3':
		glClear(GL_COLOR_BUFFER_BIT);
		drawAxis();
		Bresenham(-10, -10, -70, -70);
		glFlush();
		break;

	case '4':
		glClear(GL_COLOR_BUFFER_BIT);
		drawAxis();
		Bresenham(10, -10, 70, -70);
		glFlush();
		break;

	default:
		glClear(GL_COLOR_BUFFER_BIT);
		drawAxis();
		glFlush();
		break;
	}
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

void draw(){

	glColor3f(0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	drawAxis();

	glFlush();
}

int main(int argc, char *argv[]){
	initialize(argc, argv);
	return 0;
}
