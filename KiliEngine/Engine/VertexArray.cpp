#include "VertexArray.h"
#include "glew.h"

void VertexArray::SetupAttributes()
{
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

VertexArray::VertexArray(const float* pVertices, const unsigned int pVerticeCount) :
	mVerticeCount(pVerticeCount), mIndiceCount(0), mVaoId(0), mVboId(0), mEboId(0)
{
	//Generate VAO
	glGenVertexArrays(1, &mVaoId);
	glBindVertexArray(mVaoId);

	//Generate VBO
	glGenBuffers(1, &mVboId);
	glBindBuffer(GL_ARRAY_BUFFER, mVboId);
	glBufferData(GL_ARRAY_BUFFER, mVerticeCount * 8 * sizeof(float), pVertices, GL_STATIC_DRAW);
	
	SetupAttributes();
	glBindVertexArray(0);
}

VertexArray::VertexArray(const float* pVertices, const unsigned int pVerticeCount, const unsigned int* pIndices, const unsigned int pIndicesCount) :
	mVerticeCount(pVerticeCount), mIndiceCount(pIndicesCount), mVaoId(0), mVboId(0), mEboId(0)
{
	//Generate VAO
	glGenVertexArrays(1, &mVaoId);
	glBindVertexArray(mVaoId);

	//Generate VBO
	glGenBuffers(1, &mVboId);
	glBindBuffer(GL_ARRAY_BUFFER, mVboId);
	glBufferData(GL_ARRAY_BUFFER, mVerticeCount * 8 * sizeof(float), pVertices, GL_STATIC_DRAW);
	
	//Generate EBO
	glGenBuffers(1, &mEboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndiceCount * sizeof(unsigned int), pIndices, GL_STATIC_DRAW);

	SetupAttributes();
	glBindVertexArray(0);
}

VertexArray::~VertexArray()
{
	if (HasIndice())
	{
		glDeleteBuffers(1, &mEboId);
	}
	
	glDeleteBuffers(1, &mVboId);
	glDeleteVertexArrays(1, &mVaoId);
}

void VertexArray::SetActive()
{
	glBindVertexArray(mVaoId);
}
