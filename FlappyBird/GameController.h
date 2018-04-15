#pragma once
#include "RenderImage.h"

class Bird
{
public:
	Bird()
	{
		velocity = Vector3(0, -0.1, 0);
		speed = Vector3(0, 0, 0);
		position = point2(-0.5, 0.3);
		size_ = 0.1;
		birdImg = new RenderImage(position, point2(position.x + size_, position.y - size_), "texture//bird.bmp");
	}
	~Bird()
	{
		delete birdImg;
		birdImg = NULL;
	}
	void updatePosition()
	{
		float perTime = 0.1;
		//update speed
		speed.x += velocity.x*perTime; speed.y += velocity.y*perTime; 
		//update pos
		position.x += speed.x*perTime; position.y += speed.y*perTime;
		birdImg->resetPosition(position, point2(position.x + size_, position.y - size_));
	}
	void addSpeed(Vector3 s)
	{
		//add a speed
		speed.x += s.x;
		speed.y += s.y;
	}
	void render()
	{
		birdImg->render();
	}
	void getPosition(point2 *p)
	{
		p[0].x = position.x; p[0].y = position.y;
		p[1].x = position.x + size_; p[1].y = position.y - size_;
		p[2].x = position.x + size_; p[2].y = position.y;
		p[3].x = position.x; p[3].y = position.y - size_;
	}
private:
	Vector3 velocity;
	Vector3 speed;
	point2 position;
	float size_;
	RenderImage *birdImg;
};
class Obstacle 
{
public:
	//0 up 1 down
	Obstacle(GLuint dir)
	{;
		width = 0.2;
		length = rand()*1.0 / RAND_MAX*0.3+0.5;
		if (dir == 0) {
			position = point2(1, 1);
		}else {
			position = point2(1, -1 + length);
		}
		obstacleImg = new RenderImage(position, point2(position.x + width, position.y - length), "texture//obstacle.bmp");
	}
	~Obstacle()
	{
		delete obstacleImg;
		obstacleImg = NULL;
	}
	void updatePosition()
	{
		float perTime = 0.01;
		position.x -= perTime;
		obstacleImg->resetPosition(position, point2(position.x + width, position.y - length));
	}
	void render()
	{
		obstacleImg->render();
	}
	bool isDisappear()
	{
		return position.x + width < -1;
	}
	void getLeftDownAndRightUpPosition(point2 &leftDown,point2 &rightUp)
	{
		leftDown.x = position.x;
		leftDown.y = position.y - length;

		rightUp.x = position.x + width;
		rightUp.y = position.y;
	}
private:
	point2 position;
	float width, length;
	RenderImage *obstacleImg;
};
class GameController
{
public:
	GameController();
	~GameController();
	void initGame();
	void renderScene();
	void addBirdSpeed(Vector3 v);
	bool isDie();
private:
	//back ground
	RenderImage *bg;
	//bird
	Bird *bird;
	bool die;
	point2 bird_positions[4];
	//obstacle
	Obstacle *ob1, *ob2, *ob3, *ob4;
	//
	void renderObstacle(Obstacle *&ob,int type);
	void judgeCollision(Obstacle *&ob);
	bool insideQuad(point2 &leftDown, point2 &rightUp, point2 p);
};

