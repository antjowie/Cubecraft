#include "BlockMesh.h"
#include "utils/Shader.h"

#include <glad/glad.h>
#include <iostream>

BlockMesh::BlockMesh()
{
	// Make the cube
	// well, it is actually a temp triangle
	static const GLfloat vertices[] = {
		-0.5f, -0.5f, -1.0f, // bottom left  
		 0.5f, -0.5f, -1.0f, // bottom right 
		-0.5f,  0.5f, -1.0f, // top left 
	    -0.5f,  0.5f, -1.0f, // top left  
		 0.5f, -0.5f, -1.0f, // bottom right 
		 0.5f,  0.5f, -1.0f  // top right
	};
	// Gen buffers and bind
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	// Fill buffer with data
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Set attrib pointers and enable the array
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	// Unbind
	glBindVertexArray(0);
}

void BlockMesh::draw() const
{
	//glUseProgram(m_program);
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}