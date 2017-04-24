#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include<Windows.h>
#include <gl/glut.h>
#include<fstream>
using namespace std;

int width = 800;
int height = 800;

GLUquadricObj * Quad;
bool brown = false;
bool odd = true;

GLuint LoadTexture(const char* fileName, int wrap){
	FILE * file = fopen(fileName, "r");
	if (file == NULL)
		return 0;
	int width = 256, height = 256;
	BYTE * data = (byte*)malloc(width*height * 3);
	fread(data, width*height * 3, 1, file);
	fclose(file);
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap ? GL_REPEAT : GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap ? GL_REPEAT : GL_CLAMP);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glEnable(GL_TEXTURE_2D);
	return texture;
}



void Pieces(float x, float y, float z)
{
	GLuint texture;

	if (brown)		//change color of pieces
		texture = LoadTexture("dark-piece.bmp", 0);
	else
		texture = LoadTexture("light-piece.bmp", 0);

	glPushMatrix();

	glTranslated(x, y, z);
	gluCylinder(Quad, 25, 25, 5, 10, 10);
	glTranslated(0, 0, 5);
	gluDisk(Quad, 0, 25, 10, 10);

	glPopMatrix();
	glFlush();
}

void drawTiles(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
	GLuint texture;

	if (odd)		//change colors of tiles
	{
		texture = LoadTexture("light-tile.bmp", 0);
		odd = false;
	}
	else
	{
		texture = LoadTexture("dark-tile.bmp", 0);
		odd = true;
	}


	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_POLYGON);

	glTexCoord2f(0, 0);
	glVertex2d(x1, y1);
	glTexCoord2f(1, 0);
	glVertex2d(x2, y2);
	glTexCoord2f(1, 1);
	glVertex2d(x3, y3);
	glTexCoord2f(0, 1);
	glVertex2d(x4, y4);

	glEnd();
}

void drawBoard()
{
	int horizontal = width / 7;		//7 rows
	int vertical = height / 7;		//7 columns
	int counter = 0;

	for (int x = 0; x <= width; x += horizontal)
	{
		odd = !odd;
		for (int y = 0; y <= height; y += vertical)
		{

			drawTiles(x, y, x + horizontal, y, x + horizontal, y + vertical, x, y + vertical); //(0,0),(1,0),(1,1),(0,1) vertices

			if (counter < 2 || counter > 5){
				if (counter < 3)				//put the brown pieces on the first two rows
					brown = true;
				else if (counter >5)			//put the non brown pieces(light pieces) on the last 2 rows
					brown = false;

				Pieces(x + horizontal/2 , y + vertical / 2, 0);		//to center the pieces in the middle of each tile
			}
			counter++;
		}
		counter = 0;
	}
}

void draw(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	drawBoard();

	glFlush();
}

void setTransformations()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (width / height), 1, 100);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, -3, -3, 0, 0, 0, 0, 1, 0);
	glOrtho(width, 100, 0, height, 0, 100);
}

void initialize(int argc, char *argv[]){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Computer Graphics - Assignment 2 - Salma133722");
	glutDisplayFunc(draw);
	Quad = gluNewQuadric();
	gluQuadricTexture(Quad, GL_TRUE);
	setTransformations();
	glutMainLoop();
}

void main(int argc, char *argv[]){
	initialize(argc, argv);
}
