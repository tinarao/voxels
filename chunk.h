#pragma once
#include <vector>
#include "block.h"
#include <cassert>

class Chunk {
private:
	Vector2 initial_position;
	static const int BASE_CHUNK_SIZE = 16;
	int height_map[BASE_CHUNK_SIZE][BASE_CHUNK_SIZE] = { 0 };

public:
	std::vector<Block*> blocks;

	Chunk(Image* perlin_image, Vector2 initial_pos) {
		assert(perlin_image->width == BASE_CHUNK_SIZE && perlin_image->height == BASE_CHUNK_SIZE);

		for (int x = 0; x < perlin_image->height; x++) {
			for (int y = 0; y < perlin_image->width; y++) {
				Color col = GetImageColor(*perlin_image, x, y);

				int h_multiplier = (col.r + col.g + col.b) * 100 / 775;
				this->height_map[y][x] = h_multiplier / 10;
			}
		}

		int hmap_idx_count = 0;

		for (int x = 0; x < BASE_CHUNK_SIZE; x++) {
			for (int z = 0; z < BASE_CHUNK_SIZE; z++) {
				int h_multiplier_val = this->height_map[z][x];

				for (int y_blocks_count = 0; y_blocks_count < h_multiplier_val; y_blocks_count++) {




					bool is_renderable = true;
					int block_x = x + initial_pos.x;
					int block_z = z + initial_pos.y;






					//if (x >= 1 && x <= 14) {
					//	is_renderable = false;
					//}


					Block* block = new Block(Vector3{
						float(block_x), float(y_blocks_count), float(block_z)
						}, DARKGRAY, is_renderable);
					this->blocks.push_back(block);
				}

				if (hmap_idx_count == (BASE_CHUNK_SIZE * BASE_CHUNK_SIZE - 1)) {
					break;
				}
				else {
					hmap_idx_count++;
				}
			}
		}
	}

	~Chunk() {
		this->blocks.clear();
	}

	void Draw() {
		for (const auto& block : this->blocks) {
			block->Draw();
		}
	}
};