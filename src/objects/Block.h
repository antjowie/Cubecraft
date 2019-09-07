#pragma once
#include <glm/vec3.hpp>

class BlockMesh;

class Block
{
private:
	const BlockMesh & m_mesh;
	glm::vec3 m_pos;

public:
	Block(const BlockMesh &mesh);
	void draw() const;
};