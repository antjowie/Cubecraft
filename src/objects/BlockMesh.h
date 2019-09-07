#pragma once

// This class contains the mesh of a block

class BlockMesh
{
private:
	unsigned m_vao;
	unsigned m_program;

public:
	BlockMesh();
	void draw() const;
};