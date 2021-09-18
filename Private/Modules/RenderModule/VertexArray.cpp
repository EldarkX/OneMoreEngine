
#include "Modules/RenderModule/VertexArray.h"

VertexArray::VertexArray(const float* verts, unsigned int numVerts, const unsigned int* indices, unsigned int numIndices)
	: mNumVerts(numVerts), mNumIndices(numIndices)
{
	//create vertex array
	glGenVertexArrays(1, &mVertexArray);
	glBindVertexArray(mVertexArray);

	//Create vertex buffer
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);

	glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(mNumVerts) * 5 * sizeof(float), verts, GL_STATIC_DRAW);

	//Create indices buffer
	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mNumIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, reinterpret_cast<void*>(sizeof(float) * 3));
}

void VertexArray::SetActive()
{
	glBindVertexArray(mVertexArray);
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &mVertexBuffer);
	glDeleteBuffers(1, &mIndexBuffer);
	glDeleteVertexArrays(1, &mVertexArray);
}

