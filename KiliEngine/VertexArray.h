#pragma once

constexpr float planeVertices[] = {
-0.5f,  0.5f, 0.0f,		0.0f, 0.0f,     //top left
 0.5f,  0.5f, 0.0f,     1.0f, 0.0f,     //top right
 0.5f, -0.5f, 0.0f,     1.0f, 1.0f,     //bottom right
-0.5f, -0.5f, 0.0f,     0.0f, 1.0f };   //bottom left

constexpr unsigned int planeIndices[] = {
0, 1, 2,
2, 3, 0
};

constexpr float cubeVertices[] = {
   -0.5, -0.5, -0.5,    0,  0 ,
    0.5, -0.5, -0.5,    1,  0 ,
   -0.5,  0.5, -0.5,    0, -1 ,
    0.5,  0.5, -0.5,    1, -1 ,
   -0.5,  0.5,  0.5,    0, -1 ,
    0.5,  0.5,  0.5,    1, -1 ,
   -0.5, -0.5,  0.5,    0,  0 ,
    0.5, -0.5,  0.5,    1,  0 ,
   -0.5,  0.5, -0.5,    0, -1 ,
    0.5, -0.5, -0.5,    1,  0 ,
   -0.5,  0.5, -0.5,    0, -1 ,
    0.5,  0.5, -0.5,    1, -1 ,
   -0.5,  0.5,  0.5,    0, -1 ,
   -0.5,  0.5,  0.5,    0, -1 ,
    0.5,  0.5,  0.5,    1, -1 ,
   -0.5, -0.5,  0.5,    0,  0 ,
   -0.5, -0.5,  0.5,    0,  0 ,
    0.5, -0.5,  0.5,    1,  0 ,
   -0.5, -0.5, -0.5,    0,  0 ,
    0.5, -0.5, -0.5,    1,  0 ,
    0.5, -0.5, -0.5,    1,  0 ,
    0.5, -0.5,  0.5,    1,  0 ,
    0.5,  0.5, -0.5,    1, -1 ,
    0.5,  0.5,  0.5,    1, -1 ,
   -0.5, -0.5,  0.5,    0,  0 ,
   -0.5, -0.5, -0.5,    0,  0 ,
   -0.5,  0.5,  0.5,    0, -1 ,
   -0.5,  0.5, -0.5,    0, -1
};

constexpr unsigned int cubeIndices[] = {
    2,  1,  0 ,
    3,  9,  8 ,
    4,  11, 10 ,
    5,  11, 12 ,
    6,  14, 13 ,
    7,  14, 15 ,
    18, 17, 16 ,
    19, 17, 18 ,
    22, 21, 20 ,
    23, 21, 22 ,
    26, 25, 24 ,
    27, 25, 26
};

class VertexArray
{
private:
	unsigned int mVerticeCount;
	unsigned int mIndexCount;

	unsigned int mVaoId;
	unsigned int mVboId;
	unsigned int mIndexBufferId;

public:
	VertexArray(const float* pVertices, unsigned int pVerticeCount, const unsigned int* pIndices, unsigned int pIndexCount);
	~VertexArray();

	void SetActive();
	unsigned int GetVerticeCount() const { return mVerticeCount; }
	unsigned int GetIndicesCount() const { return mIndexCount; }
};
