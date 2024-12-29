#pragma once

#include <raylib.h>
#include <vector>
#include "chunk.hpp"
#include <iostream>

class ChunkManager {
private:
	Camera3D* camera_ref;
	std::vector<Chunk> chunks;

public:
	ChunkManager(Camera3D* cam) {
		this->camera_ref = cam;
		chunks.push_back(*new Chunk());

	}

	void Update() {
		for (Chunk &chunk : this->chunks) {
			Vector3 pos = chunk.blocks[0].GetPosition();
			if (
				((pos.x - this->camera_ref->position.x) >= 1.f) ||
				((pos.y - this->camera_ref->position.y) >= 1.f) ||
				((pos.z - this->camera_ref->position.z) >= 1.f)
				) {
				std::cout << "OUT OF VIEWPORT" << std::endl;
			}
			else {
				chunk.Draw();
			}
		}
	}
};