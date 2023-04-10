#pragma once

#include "glew.h"

class VertexArray
{
public:
					VertexArray(const float* verts, unsigned int numVerts, const unsigned int* indices, unsigned int numIndices);

	void			SetActive();

	unsigned int	GetNumVerts() const { return mNumVerts; }
	unsigned int	GetNumIndices() const { return mNumIndices; }

					~VertexArray();
private:
	unsigned int	mNumVerts;
	unsigned int	mNumIndices;
	//stores ID
	unsigned int	mVertexBuffer;
	unsigned int	mIndexBuffer;
	unsigned int	mVertexArray;
};