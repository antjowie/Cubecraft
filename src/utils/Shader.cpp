#include "Shader.h"
#include "Logger.h"

#include <glad/glad.h>


#include <fstream>
#include <sstream>
#include <iostream>

bool Shader::addShader(Shader::Type shaderType, const char * shaderPath)
{
	std::ifstream file;

	file.open(shaderPath);
	if (!file.is_open())
	{
		std::string message("Could not find shader located at " + std::string(shaderPath));
		LOG(message, Logger::Severity::FATAL);
		
		return false;
	}

	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();

	const std::string string = buffer.str();
	const char* source = string.c_str();

	// Assume we always load 1 shader
	GLuint shader = glCreateShader(static_cast<GLenum>(shaderType));
	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);

	// Check compile status
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		char info[512];
		glGetShaderInfoLog(shader, 512, nullptr, info);
		LOG(std::string("Error while compiling shader: ") +info, Logger::Severity::FATAL);

		glDeleteShader(shader);
		return false;
	}

	m_shaders.push_back(shader);
	return true;
}

bool Shader::linkProgram(GLuint program)
{
	for (unsigned shader : m_shaders)
	{
		// Attach shader to program
		glAttachShader(program, shader);
	}

	// Check linking status
	glLinkProgram(program);

	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status != GL_TRUE)
	{
		char info[512];
		glGetProgramInfoLog(program, 512, nullptr, info);
		LOG(std::string("Error while linking program: ") + info, Logger::Severity::FATAL);
		
		return false;
	}
	return true;
}

Shader::~Shader()
{
	for (unsigned shader : m_shaders)
	{
		glDeleteShader(shader);
	}
}