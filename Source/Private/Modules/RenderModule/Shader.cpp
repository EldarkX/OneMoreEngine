
#include "Modules/RenderModule/Shader.h"

#include <fstream>
#include <sstream>

#include "SDL.h"

bool Shader::Load(const std::string& vertName, const std::string& fragName)
{
	if (!CompileShader(vertName, GL_VERTEX_SHADER, mVertexShader)
		|| !CompileShader(fragName, GL_FRAGMENT_SHADER, mFragShader))
	{
		return false;
	}

	mShaderProgram = glCreateProgram();
	glAttachShader(mShaderProgram, mVertexShader);
	glAttachShader(mShaderProgram, mFragShader);
	glLinkProgram(mShaderProgram);
	
	return IsValidProgram();
}

void Shader::SetMatrixUniform(const char* paramName, const Matrix4D& paramValue)
{
	GLuint loc = glGetUniformLocation(mShaderProgram, paramName);

	float array[16];
	for (int i = 0, k = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j, ++k)
			array[k] = paramValue(i, j);

	glUniformMatrix4fv(loc, 1, GL_TRUE, array);
}

void Shader::SetActive()
{
	glUseProgram(mShaderProgram);
}

Shader::~Shader()
{
	glDeleteProgram(mShaderProgram);
	glDeleteShader(mVertexShader);
	glDeleteShader(mFragShader);
}

bool Shader::CompileShader(const std::string& fileName, GLenum shaderType, GLuint& outShader)
{
	std::ifstream shaderFile(fileName);

	if (shaderFile.is_open())
	{
		std::stringstream sstream;

		sstream << shaderFile.rdbuf();
		
		std::string tmp = sstream.str();

		const char* contentsChar = tmp.c_str();

		outShader = glCreateShader(shaderType);

		glShaderSource(outShader, 1, &contentsChar, nullptr);

		glCompileShader(outShader);

		if (!IsCompiled(outShader))
		{
			SDL_Log("Failed to compile shader: %s\n", fileName.c_str());
			return false;
		}
	}
	else
	{
		SDL_Log("Shader file not found: %s\n", fileName.c_str());
		return false;
	}

	return true;
}

bool Shader::IsCompiled(GLuint shader)
{
	return CheckIsValid(GL_COMPILE_STATUS, false, &shader, "GLSL compile failed: %s\n");
}

bool Shader::IsValidProgram()
{
	return CheckIsValid(GL_LINK_STATUS, true, &mShaderProgram, "GLSL compile failed: %s\n");
}

bool Shader::CheckIsValid(GLenum checkParam, bool isProgram, GLuint *entity, std::string errorMsg)
{
	GLint status;

	if (isProgram)
		glGetProgramiv(*entity, checkParam, &status);
	else
		glGetShaderiv(*entity, checkParam, &status);

	if (status != GL_TRUE)
	{
		const size_t size = 512;
		char buffer[size];
		memset(buffer, 0, size);
		if (isProgram)
			glGetProgramInfoLog(*entity, size - 1, nullptr, buffer);
		else
			glGetShaderInfoLog(*entity, size - 1, nullptr, buffer);
		SDL_Log(errorMsg.c_str(), buffer);
		return false;
	}
	return true;
}

