#pragma once

#include <raylib.h>
#include <vector>
#include <iostream>
#include "chunk.h"

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
			double distance = hypot(
				hypot(
					pos.x - this->camera_ref->position.x, pos.y - this->camera_ref->position.y
				),
				pos.z - this->camera_ref->position.z);

			if (distance > static_cast<double>(100)) {
				std::cout << "do something" << std::endl;
				return;
			}

			chunk.Draw();

		}
	}
};