#pragma once

class BlockMesh
{
private:
	unsigned m_vao;
	unsigned m_program;

public:
	BlockMesh();
	void draw() const;
};