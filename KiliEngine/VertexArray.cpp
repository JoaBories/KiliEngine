#include "VertexArray.h"

#include "glew.h"

VertexArray::VertexArray(const float* pVertices, const unsigned int pVerticeCount) :
	mVerticeCount(pVerticeCount), mVaoId(0), mVboId(0)
{
	//Generate VAO
	glGenVertexArrays(1, &mVaoId);
	glBindVertexArray(mVaoId);

	//Generate VBO
	glGenBuffers(1, &mVboId);
	glBindBuffer(GL_ARRAY_BUFFER, mVboId);
	glBufferData(GL_ARRAY_BUFFER, mVerticeCount * 8 * sizeof(float), pVertices, GL_STATIC_DRAW);

	//Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);
	//Normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 3));
	//Texture coordinates
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 6));
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &mVboId);
	glDeleteBuffers(1, &mVaoId);
}

void VertexArray::SetActive()
{
	glBindVertexArray(mVaoId);
}
