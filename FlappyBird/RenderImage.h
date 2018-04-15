#pragma once
#include "stdafx.h"
#include "shader.h"
struct point2 {
	float x;
	float y;
	point2(float x_, float y_) { x = x_; y = y_; }
	point2() { x = 0; y = 0; }
};

class RenderImage
{
public:
	RenderImage(point2 leftUp,point2 rightDown,char* bmpFile);
	~RenderImage();
	void render();
	void resetPosition(point2 leftUp, point2 rightDown);
private:
	//init
	static void init();
	//global
	static GLuint VAO, VBO;
	static GLuint programId;
	// point.x point.y coord.x coord.y *4
	static float vertices[16];
	//local
	point2 leftUp_;
	point2 rightDown_;
	GLuint textureId;
	void setData();
};

