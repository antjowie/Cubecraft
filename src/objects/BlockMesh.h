#pragma once

// Blockmesh is its own class so that rendering can be split from the logic
class BlockMesh
{
private:
	unsigned m_vao;
	unsigned m_program;

public:
	BlockMesh();
	void draw() const;
};