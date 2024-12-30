#pragma once
#include <vector>
#include "block.h"

class Chunk {
private:
	std::vector<int> height_map;
	void generate_height_map() {
		Image perlin_image = GenImagePerlinNoise(256, 256, 0, 0, 1);
		Texture2D tex = LoadTextureFromImage(perlin_image);

		for (int x = 0; x < perlin_image.height; x++) {
			for (int y = 0; y < perlin_image.width; y++) {
				Color col = GetImageColor(perlin_image, x, y);

				int h_multiplier = (col.r + col.g + col.b) * 100 / 775;
				this->height_map.push_back(h_multiplier);
			}
		}
	}

public:
	static const int BASE_CHUNK_X_SIZE = 16;
	static const int CHUNK_Y_SIZE = 128;

	/*
		Algorithm:
			1. Generate perlin multipliers array
				Value = 0..100
			2. Generate <value> blocks in vertical

		Future:
			1. Генерировать перлина с размером (chunks_amount * 16)
			2. Делить на отрезки по 16x16 пикселей и прокидывать 
				в менеджере в чанки
			3. Генерить на основе переданной даты

		На данный момент сделаю в пределах чанка, чтобы протестить
	*/

	std::vector<Block> blocks;

	Chunk() {

		/*
			for (const auto &height) {
				generate <height> blocks in this column
			}
		*/

		for (int x = 0; x <= BASE_CHUNK_X_SIZE; x++) {
			for (int y = 0; y <= CHUNK_Y_SIZE; y++) {
				for (int z = 0; z <= BASE_CHUNK_X_SIZE; z++) {
					// TODO: Generate one single chunk mesh instead of 1000 blocks
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