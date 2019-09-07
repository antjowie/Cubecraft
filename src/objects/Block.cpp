#include "Block.h"
#include "BlockMesh.h"

Block::Block(const BlockMesh & mesh):
	m_mesh(mesh)
{
}

void Block::draw() const
{
	m_mesh.draw();
}
