#include "BlockMesh.h"
#include "utils/Shader.h"

#include <glad/glad.h>
#include <iostream>

#ifdef DEBUG
#include <cassert>
#endif // DEBUG

BlockMesh::BlockMesh()
{
	// Should this be a singleton???
#ifdef DEBUG
	static bool initialized = false;
	assert(!initialized && "BlockMesh got constructed multiple times");
	initialized = true;
#endif // DEBUG


	Shader shader;
	m_program = glCreateProgram();

	if (!shader.addShader(GL_VERTEX_SHADER, "resources/shaders/block.vert"))
		std::cout << "Vertex shader failed compilation\n";
	if (!shader.addShader(GL_FRAGMENT_SHADER, "resources/shaders/block.frag"))
		std::cout << "Fragment shader failed compilation\n";
	if (!shader.linkProgram(m_program))
		std::cout << "Linking program failed\n";

	// Make the cube
	// well, it is actually a temp triangle
	static const GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f, // left  
		 0.5f, -0.5f, 0.0f, // right 
		 0.0f,  0.5f, 0.0f  // top   
	};
	// Gen buffers
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void BlockMesh::draw() const
{
	glUseProgram(m_program);
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}