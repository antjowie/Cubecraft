#include "BlockMesh.h"
#include "utils/Shader.h"

#include <glad/glad.h>
#include <stb_image.h>

#include "utils/Logger.h"

BlockMesh::BlockMesh()
{
	constexpr GLfloat vertices[] = {
	-1.0f,-1.0f,-1.0f, 0.0f, 0.0f,
	-1.0f,-1.0f, 1.0f, 1.0f, 0.0f,
	-1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	
	 1.0f, 1.0f,-1.0f, 1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f, 0.0f, 0.0f,
	-1.0f, 1.0f,-1.0f, 0.0f, 1.0f,
	
	 1.0f,-1.0f, 1.0f, 1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f, 0.0f, 0.0f,
	 1.0f,-1.0f,-1.0f, 1.0f, 0.0f,
	
	 1.0f, 1.0f,-1.0f, 1.0f, 1.0f,
	 1.0f,-1.0f,-1.0f, 1.0f, 0.0f,
	-1.0f,-1.0f,-1.0f, 0.0f, 0.0f,
	
	-1.0f,-1.0f,-1.0f, 0.0f, 0.0f,
	-1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f, 1.0f, 0.0f,
	
	 1.0f,-1.0f, 1.0f, 1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f, 0.0f, 1.0f,
	-1.0f,-1.0f,-1.0f, 0.0f, 0.0f,
	
	-1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-1.0f,-1.0f, 1.0f, 0.0f, 0.0f,
	 1.0f,-1.0f, 1.0f, 1.0f, 0.0f,
	
	 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 1.0f,-1.0f,-1.0f, 0.0f, 0.0f, 
	 1.0f, 1.0f,-1.0f, 1.0f, 0.0f, 
	 
	 1.0f,-1.0f,-1.0f, 0.0f, 0.0f, 
	 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 1.0f,-1.0f, 1.0f, 0.0f, 1.0f,
	 
	 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 1.0f, 1.0f,-1.0f, 1.0f, 0.0f,
	-1.0f, 1.0f,-1.0f, 0.0f, 0.0f,
	 
	 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f, 0.0f, 0.0f,
	-1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	
 	 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 1.0f,-1.0f, 1.0f, 1.0f, 0.0f
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, 5 * sizeof(GLfloat), (void*)3);
	glEnableVertexAttribArray(1);


	// Unbind
	glBindVertexArray(0);

	// Load texture
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int width, height, nrChannels;
	unsigned char* data = stbi_load("resources/textures/dirt.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		LOG("Failed to load texture",Logger::Severity::WARNING);
	}
	stbi_image_free(data);
}

void BlockMesh::draw() const
{
	//glUseProgram(m_program);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glBindVertexArray(m_vao);

	glDrawArrays(GL_TRIANGLES, 0, 3*2*6);
	glBindVertexArray(0);
}