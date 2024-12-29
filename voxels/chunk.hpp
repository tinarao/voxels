#pragma once
#include <vector>
#include "block.hpp"

class Chunk {
public:
	static const int CHUNK_SIZE = 16;
	std::vector<Block> blocks;

	Chunk() {
		for (int x = 0; x <= CHUNK_SIZE; x++) {
			for (int y = 0; y <= CHUNK_SIZE; y++) {
				for (int z = 0; z <= CHUNK_SIZE; z++) {
					Block* block = new Block(Vector3{ (float)x, (float)y, (float)z }, YELLOW);
					this->blocks.push_back(*block);
				}
			}
		}
	}

	~Chunk() {
		this->blocks.clear();
	}

	void Draw() {
		for (Block& block : this->blocks) {
			block.Draw();
		}
	}
};