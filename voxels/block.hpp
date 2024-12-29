#include <raylib.h>

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

class Block {
public:
	Block(Vector3 pos, Color color) {
		this->color = color;
		this->position = pos;
	};

	bool IsActive() const {
		return this->is_active;
	};

	void SetActive(bool active) {
		this->is_active = active;
	}

	void Draw() const {
		DrawCube(this->position, BASIC_BLOCK_SIZE, BASIC_BLOCK_SIZE, BASIC_BLOCK_SIZE, this->color);
		if (this->is_wires_enabled) {
			DrawCubeWires(this->position, BASIC_BLOCK_SIZE, BASIC_BLOCK_SIZE, BASIC_BLOCK_SIZE, MAROON);
		}
	}

private:
	bool is_active;
	bool is_wires_enabled = true;
	Vector3 position;
	Color color;
};