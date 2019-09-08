#pragma once

#include "objects/Block.h"
#include "cameras/Camera.h"
#include "utils/Shader.h"

#include <vector>

class BlockRenderer
{
public:
	BlockRenderer();

	void render(const std::vector<Block>& blocks, const Camera& camera);

private:
	unsigned m_program;
};