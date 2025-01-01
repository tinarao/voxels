#pragma once
#include <vector>
#include "block.h"

class Chunk {
private:
	static const int BASIC_BLUR_SIZE = 6;
	std::vector<int> generate_height_map() {
		std::vector <int> height_map;
		Image perlin_image = GenImagePerlinNoise(BASE_CHUNK_SIZE, BASE_CHUNK_SIZE, 0, 0, 1);
		ImageBlurGaussian(&perlin_image, BASIC_BLUR_SIZE);
		Texture2D tex = LoadTextureFromImage(perlin_image);

		for (int x = 0; x < perlin_image.height; x++) {
			for (int y = 0; y < perlin_image.width; y++) {
				Color col = GetImageColor(perlin_image, x, y);

				int h_multiplier = (col.r + col.g + col.b) * 100 / 775;
				height_map.push_back(h_multiplier);
			}
		}

		return height_map;
	}

public:
	static const int BASE_CHUNK_SIZE = 16;
	std::vector<Block> blocks;

	Chunk() {
		std::vector<int> height_map = this->generate_height_map();
		int hmap_idx_count = 0;

		for (int x = 0; x <= BASE_CHUNK_SIZE; x++) {
			for (int z = 0; z <= BASE_CHUNK_SIZE; z++) {
				for (int y_c = 0; y_c < height_map[hmap_idx_count]; y_c++) {
					Block* block = new Block(Vector3{
						float(x), float(y_c), float(z)
						}, RED);
					this->blocks.push_back(*block);
				}

				if (hmap_idx_count == height_map.size() - 1) {
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
		for (Block& block : this->blocks) {
			block.Draw();
		}
	}
};