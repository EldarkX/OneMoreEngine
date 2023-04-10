#pragma once

#include "Modules/RenderModule/RenderManager.h"
#include "Modules/MathModule/Matrix4.h"

#include <string>

#include "glew.h"

class Shader
{
public:
			Shader() = default;

	bool	Load(const std::string& vertName, const std::string& fragName);
	void	SetMatrixUniform(const char* paramName, const Matrix4D& paramValue);
	void	SetActive();

			~Shader();
private:
	bool	CompileShader(const std::string& fileName, GLenum shaderType, GLuint& outShader);
	bool	IsCompiled(GLuint shader);
	bool	IsValidProgram();
	bool	CheckIsValid(GLenum checkParam, bool isProgram, GLuint* entity, std::string errorMsg);

private:
	GLuint	mVertexShader = 0;
	GLuint	mFragShader = 0;
	GLuint	mShaderProgram = 0;
};