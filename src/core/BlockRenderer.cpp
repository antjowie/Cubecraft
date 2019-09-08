#include "BlockRenderer.h"
#include "utils/Logger.h"

BlockRenderer::BlockRenderer()
{
	Shader shader;

	if (!shader.addShader(Shader::Type::VERTEX, "resources/shaders/block.vert"))
		LOG("Vertex shader failed compilation", Logger::Severity::FATAL);
	if (!shader.addShader(Shader::Type::FRAGMENT, "resources/shaders/block.frag"))
		LOG("Fragment shader failed compilation", Logger::Severity::FATAL);

	m_program = glCreateProgram();
	if (!shader.linkProgram(m_program))
		LOG("Linking program failed", Logger::Severity::FATAL);
}

void BlockRenderer::render(const std::vector<Block>& blocks, const Camera& camera)
{
	glm::mat4 mvp = camera.perspective() * camera.view();
	glUseProgram(m_program);
	glUniformMatrix4fv(glGetUniformLocation(m_program,"aMVP"), 1, GL_FALSE, &mvp[0][0]);

	for (const auto& block : blocks)
	{
		block.draw();
	}
}
