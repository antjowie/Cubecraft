#pragma once
#include <vector>

#include <glad/glad.h>

// The Shader class compiles shaders and links them to a program
class Shader
{
public:
	enum class Type;

	~Shader();

	// Compiles a shader for you, when all shaders are added, call linkProgram
	// Adding 2 shaders of the same type yields undefined behavior
	bool addShader(Type shaderType, const char* shaderPath);
	// Supply a program to link the shaders too. Logs errors and returns false if linking failed
	bool linkProgram(GLuint program);

	enum class Type
	{
		VERTEX = GL_VERTEX_SHADER,
		FRAGMENT = GL_FRAGMENT_SHADER
	};

private:
	std::vector<GLuint> m_shaders;
};