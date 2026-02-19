#pragma once

constexpr float PlaneVertices[] = {
    -0.5,  0.5, 0.0,		   0, 0,     //top left
     0.5,  0.5, 0.0,     1, 0,     //top right
     0.5, -0.5, 0.0,     1, 1,     //bottom right
    -0.5, -0.5, 0.0,     0, 1      //bottom left
};   

constexpr unsigned int PlaneIndices[] = {
0, 1, 2,
2, 3, 0
};

constexpr float CubeVertices[] = {
    // ===== FRONT (Z+) =====
    -0.5f, -0.5f,  0.5f,   0.0f, 1.0f, // 0 bottom left
     0.5f, -0.5f,  0.5f,   1.0f, 1.0f, // 1 bottom right
     0.5f,  0.5f,  0.5f,   1.0f, 0.0f, // 2 top right
    -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, // 3 top left    
    // ===== BACK (Z-) =====
     0.5f, -0.5f, -0.5f,   0.0f, 1.0f, // 4 bottom left
    -0.5f, -0.5f, -0.5f,   1.0f, 1.0f, // 5 bottom right
    -0.5f,  0.5f, -0.5f,   1.0f, 0.0f, // 6 top right
     0.5f,  0.5f, -0.5f,   0.0f, 0.0f, // 7 top left    
    // ===== LEFT (X-) =====
    -0.5f, -0.5f, -0.5f,   0.0f, 1.0f, // 8 bottom left
    -0.5f, -0.5f,  0.5f,   1.0f, 1.0f, // 9 bottom right
    -0.5f,  0.5f,  0.5f,   1.0f, 0.0f, // 10 top right
    -0.5f,  0.5f, -0.5f,   0.0f, 0.0f, // 11 top left   
    // ===== RIGHT (X+) =====
     0.5f, -0.5f,  0.5f,   0.0f, 1.0f, // 12 bottom left
     0.5f, -0.5f, -0.5f,   1.0f, 1.0f, // 13 bottom right
     0.5f,  0.5f, -0.5f,   1.0f, 0.0f, // 14 top right
     0.5f,  0.5f,  0.5f,   0.0f, 0.0f, // 15 top left   
    // ===== TOP (Y+) =====
    -0.5f,  0.5f,  0.5f,   0.0f, 1.0f, // 16 bottom left
     0.5f,  0.5f,  0.5f,   1.0f, 1.0f, // 17 bottom right
     0.5f,  0.5f, -0.5f,   1.0f, 0.0f, // 18 top right
    -0.5f,  0.5f, -0.5f,   0.0f, 0.0f, // 19 top left   
    // ===== BOTTOM (Y-) =====
    -0.5f, -0.5f, -0.5f,   0.0f, 1.0f, // 20 bottom left
     0.5f, -0.5f, -0.5f,   1.0f, 1.0f, // 21 bottom right
     0.5f, -0.5f,  0.5f,   1.0f, 0.0f, // 22 top right
    -0.5f, -0.5f,  0.5f,   0.0f, 0.0f  // 23 top left
};

constexpr unsigned int CubeIndices[] = {
    0,1,2, 2,3,0,        // Front
    4,5,6, 6,7,4,        // Back
    8,9,10, 10,11,8,     // Left
    12,13,14, 14,15,12,  // Right
    16,17,18, 18,19,16,  // Top
    20,21,22, 22,23,20   // Bottom
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
