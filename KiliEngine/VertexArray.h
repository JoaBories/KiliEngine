#pragma once
#include <vector>

#include "Vertex.h"

constexpr float PLANE_VERTICES[] = {
    -0.5,  0.5, 0.0,    0.0,0.0,0.0,    0.0, 0.0,     //top left
     0.5,  0.5, 0.0,    0.0,0.0,0.0,    1.0, 0.0,     //top right
    -0.5, -0.5, 0.0,    0.0,0.0,0.0,    0.0, 1.0,     //bottom left
     0.5, -0.5, 0.0,    0.0,0.0,0.0,    1.0, 1.0      //bottom right
};

class VertexArray
{
private:
	unsigned int mVerticeCount;

	unsigned int mVaoId;
	unsigned int mVboId;

public:
	VertexArray(const float* pVertices, unsigned int pVerticeCount);
	~VertexArray();

	void SetActive();
	unsigned int GetVerticeCount() const { return mVerticeCount; }
};
