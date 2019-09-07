#pragma once
#include <vector>

#include <glad/glad.h>

// The Shader class 
class Shader
{
private:
	std::vector<GLuint> m_shaders;

public:

	~Shader();
	enum class Type
	{
		VERTEX = GL_VERTEX_SHADER,
		FRAGMENT = GL_FRAGMENT_SHADER
	};

	// Compiles a shader for you, when all shaders are added, call linkProgram
	// Adding 2 shaders of the same type yields undefined behavior
	bool addShader(Type shaderType, const char* shaderPath);
	// Supply a program to link the shaders too. Logs errors and returns false if linking failed
	bool linkProgram(GLuint program);
};