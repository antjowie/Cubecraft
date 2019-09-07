#pragma once
#include <glm/vec3.hpp>

class BlockMesh;

// Block is an object in the game that is static

class Block
{
private:
	const BlockMesh & m_mesh;
	glm::vec3 m_pos;

public:
	Block(const BlockMesh &mesh);
	void draw() const;
};