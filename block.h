#pragma once
#include <raylib.h>
#include <vector>

const float BASIC_BLOCK_SIZE = 1.0f;
enum BlockType {
	Default = 0,
	Grass,
	Dirt,
	Water,
	Stone,
	Wood,
	Sand
};

struct CubeVerticies {
	Vector3 t1;
	Vector3 t2;
	Vector3 t3;
	Vector3 t4;
	Vector3 b1;
	Vector3 b2;
	Vector3 b3;
	Vector3 b4;
};

class Block {
private:
	bool is_wires_enabled = true;
	Vector3 position;
	Color color;

	// the block will be rendered if true
	bool is_renderable = true;

public:
	const int HEIGHT = 1;
	Block(Vector3 pos, Color color, bool p_is_renderable) {
		this->color = color;
		this->position = pos;
		this->is_renderable = p_is_renderable;
	};

	Vector3 GetPosition() const {
		return this->position;
	}

	void Draw() const {
		if (!this->is_renderable) {
			return;
		}

		DrawCube(this->position, BASIC_BLOCK_SIZE, BASIC_BLOCK_SIZE, BASIC_BLOCK_SIZE, this->color);
		if (this->is_wires_enabled) {
			DrawCubeWires(this->position, BASIC_BLOCK_SIZE, BASIC_BLOCK_SIZE, BASIC_BLOCK_SIZE, BLACK);
		}
	}

};