#pragma once

#include <raylib.h>
#include <vector>
#include <iostream>
#include "chunk.h"
#include <cassert>

class ChunkManager {
private:
	Camera3D* camera_ref;
	const int BASIC_BLUR_SIZE = 6;

	static const int CHUNK_WIDTH = 16;
	static const int CHUNKS_TO_GENERATE = 9;
	Chunk* chunks[CHUNKS_TO_GENERATE] = {};
	int world_heightmap[CHUNKS_TO_GENERATE][CHUNK_WIDTH][CHUNK_WIDTH] = { 0 };
public:
	ChunkManager(Camera3D* cam) {
		double result_value = 0;
		double fraction = modf(this->CHUNKS_TO_GENERATE, &result_value);
		assert(result_value != 0);

		this->camera_ref = cam;
	}

	~ChunkManager() {
		for (auto chunk : this->chunks) {
			delete chunk;
		}
	}

	void GenerateWorld() {
		int h_map_w = sqrt(this->CHUNKS_TO_GENERATE) * CHUNK_WIDTH;

		Image perlin_image = GenImagePerlinNoise(h_map_w, h_map_w, 0, 0, 1);
		ImageBlurGaussian(&perlin_image, BASIC_BLUR_SIZE);

		int chunks_x_count = 0;
		int chunks_y_count = 0;
		for (int i = 0; i < CHUNKS_TO_GENERATE; i++) {
			if (i == 3) {
				chunks_y_count++;
			}

			Image perlin_crop_copy = perlin_image;

			Rectangle rect { };
			rect.x = chunks_x_count * 16;
			rect.y = chunks_y_count * 16;
			rect.width = 16;
			rect.height = 16;

			// Crashes at second iteration
			ImageCrop(&perlin_crop_copy, rect);

			Chunk* chunk = new Chunk(&perlin_crop_copy);
			this->chunks[i] = chunk;

			UnloadImage(perlin_crop_copy);
		}

		UnloadImage(perlin_image);
	}

	void Update() {
		for (int i = 0; i < CHUNKS_TO_GENERATE; i++) {
			Vector3 pos = this->chunks[i]->blocks[0].GetPosition();
			float distance = (float)hypot(
				hypot(
					pos.x - this->camera_ref->position.x, pos.y - this->camera_ref->position.y
				),
				pos.z - this->camera_ref->position.z);

			if (distance > 100.f) {
				std::cout << "do something" << std::endl;
				return;
			}

			this->chunks[i]->Draw();
		}
	}
};