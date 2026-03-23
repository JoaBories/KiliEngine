#pragma once
#include <vector>

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
	unsigned int mIndiceCount;

	unsigned int mVaoId;
	unsigned int mVboId;
	unsigned int mEboId;
	
	void SetupAttributes();

public:
	VertexArray(const float* pVertices, unsigned int pVerticeCount);
	VertexArray(const float* pVertices, unsigned int pVerticeCount, const unsigned int* pIndices, unsigned int pIndicesCount);
	~VertexArray();

	void SetActive();
	[[nodiscard]] unsigned int GetVerticeCount() const { return mVerticeCount; }
	[[nodiscard]] unsigned int GetIndiceCount() const { return mIndiceCount; }

	[[nodiscard]] bool HasIndice() const { return mIndiceCount != 0; }
};
