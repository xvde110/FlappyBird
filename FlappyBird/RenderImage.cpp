#include "stdafx.h"
#include "RenderImage.h"


GLuint RenderImage::VAO = 0;
GLuint RenderImage::VBO = 0;
GLuint RenderImage::programId = 0;
float RenderImage::vertices[16] = { 0 };


RenderImage::RenderImage(point2 leftUp, point2 rightDown, char * bmpFile)
{
	if (glIsProgram(RenderImage::programId)==GL_FALSE)
	{
		RenderImage::init();
	}
	leftUp_ = leftUp;
	rightDown_ = rightDown;
	Shader::loadBMPFile(&textureId, bmpFile);
}

RenderImage::~RenderImage()
{
}

void RenderImage::render()
{
	glBindVertexArray(VAO);
	setData();
	glUseProgram(programId);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,textureId);
	glUniform1i(glGetUniformLocation(programId, "img"), 0);

	glDrawArrays(GL_QUADS, 0, 4);

	glUseProgram(0);
	glBindVertexArray(0);
}

void RenderImage::resetPosition(point2 leftUp, point2 rightDown)
{
	leftUp_ = leftUp;
	rightDown_ = rightDown;
}

void RenderImage::init()
{
	//VAO VBO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, (void*)(sizeof(GLfloat) * 2));
	glEnableVertexAttribArray(1);

	//create shader 
	std::vector<GLuint> v;
	v.push_back(Shader::createShader(GL_VERTEX_SHADER, "glsl//renderImageVertexShader.glsl"));
	v.push_back(Shader::createShader(GL_FRAGMENT_SHADER, "glsl//renderImageFragmentShader.glsl"));
	programId = Shader::createProgram(v);
}

void RenderImage::setData()
{
	//update the array buffer
	vertices[0] = leftUp_.x;vertices[1] = rightDown_.y;vertices[2] = 0;vertices[3] = 0;
	vertices[4] = rightDown_.x; vertices[5] = rightDown_.y; vertices[6] = 1; vertices[7] = 0;
	vertices[8] = rightDown_.x; vertices[9] = leftUp_.y; vertices[10] = 1; vertices[11] = 1;
	vertices[12] = leftUp_.x; vertices[13] = leftUp_.y; vertices[14] = 0; vertices[15] = 1;

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
}
