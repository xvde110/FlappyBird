// FlappyBird.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "GameController.h"
#include <time.h>

GameController game_controller;

void init()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	//glEnable(GL_DEPTH_TEST);
	game_controller.initGame();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	game_controller.renderScene();
	glutSwapBuffers();

	glutPostRedisplay();
}

void mouseFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !game_controller.isDie())
		game_controller.addBirdSpeed(Vector3(0, 0.4, 0));
}

int main(int argc, char **argv)
{
	srand(time(0));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Triangle demo");

	glewInit();
	init();

	glutDisplayFunc(display);
	glutMouseFunc(mouseFunc);
	glutMainLoop();
	return 0;
}
