#include "stdafx.h"
#include "GameController.h"


GameController::GameController()
{
	bg = NULL;
	bird = NULL;
	ob1 = NULL;
	ob2 = NULL;
	ob3 = NULL;
	ob4 = NULL;

}


GameController::~GameController()
{
	delete bg;
	delete bird;
	bg = NULL;
	bird = NULL;
}

void GameController::initGame()
{
	bg = new RenderImage(point2(-1, 1), point2(1, -1), "texture//bg.bmp");
	bird = new Bird();
	ob1 = new Obstacle(0);
	ob2 = new Obstacle(1);
	ob3 = new Obstacle(0);
	ob4 = new Obstacle(1);
	for (int i = 0; i < 100; i++) {
		ob3->updatePosition();
		ob4->updatePosition();
	}
	die = false;
	bird->getPosition(bird_positions);
}

void GameController::renderScene()
{
	bg->render();
	//更新位置
	bird->updatePosition();
	//得到包围点用于碰撞计算
	bird->getPosition(bird_positions);
	bird->render();

	renderObstacle(ob1, 0);
	renderObstacle(ob2, 1);
	renderObstacle(ob3, 0);
	renderObstacle(ob4, 1);

	//碰撞检测
	judgeCollision(ob1);
	judgeCollision(ob2);
	judgeCollision(ob3);
	judgeCollision(ob4);

	//判断得分显示分数

}

void GameController::addBirdSpeed(Vector3 v)
{
	bird->addSpeed(v);
}

bool GameController::isDie()
{
	return die;
}

void GameController::renderObstacle(Obstacle *&ob,int type)
{
	if (ob == NULL) return;
	if (!ob->isDisappear())
	{
		if(!die)
			ob->updatePosition();
		ob->render();
	}
	else {
		ob = new Obstacle(type);
	}
}

void GameController::judgeCollision(Obstacle *& ob)
{
	point2 leftDown, rightUp;
	ob->getLeftDownAndRightUpPosition(leftDown, rightUp);
	for (int i = 0; i < 4; i++) {
		if (insideQuad(leftDown,rightUp,bird_positions[i]))
			die = true;
	}
}

bool GameController::insideQuad(point2 & leftDown, point2 & rightUp, point2 p)
{
	/*glPointSize(5);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	glVertex2d(leftDown.x, leftDown.y);
	glVertex2d(rightUp.x, rightUp.y);
	glVertex2d(p.x, p.y);
	glEnd();*/
	if (p.x >= leftDown.x && p.x <= rightUp.x && p.y >= leftDown.y && p.y <= rightUp.y)
		return true;
	else
		return false;
}
