#pragma once

#include "glew.h"
#include <string>

#include "Modules/MathModule/Matrix4.h"

using std::string;

class Shader
{

public:

	Shader() = default;

	bool	Load(const string& vertName, const string& fragName);

	void	SetMatrixUniform(const char* paramName, const Matrix4D& paramValue);

	void	SetActive();

	~Shader();

private:

	bool	CompileShader(const string& fileName, GLenum shaderType, GLuint& outShader);

	bool	IsCompiled(GLuint shader);

	bool	IsValidProgram();

	bool	CheckIsValid(GLenum checkParam, bool isProgram, GLuint* entity, string errorMsg);

	GLuint	mVertexShader = 0;
	GLuint	mFragShader = 0;
	GLuint	mShaderProgram = 0;

};