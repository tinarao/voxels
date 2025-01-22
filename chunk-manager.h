#include <raylib.h>
#include <vector>
#include <math.h>
#include <iostream>
#include "config.h"
#include "chunk.h"
#include <cassert>

using namespace config;

class ChunkManager {
private:
    std::vector<Chunk*> chunks;
    Camera3D* camera_ref;

public:
    ChunkManager(Camera3D* cam) {
        double result_value = 0;
        modf(CHUNKS_TO_GENERATE, &result_value);
        assert(result_value != 0);

        this->camera_ref = cam;
    }

    ~ChunkManager() {
        for (const auto &chunk : this->chunks) {
            delete chunk;
        }
    }

    void GenerateWorld() {
        int h_map_w = sqrt(CHUNKS_TO_GENERATE) * CHUNK_WIDTH;

        Image perlin_image = GenImagePerlinNoise(h_map_w, h_map_w, 0, 0, 1);
        ImageBlurGaussian(&perlin_image, BASIC_BLUR_SIZE);

        int chunks_x_count = 0;
        int chunks_y_count = 0;
        int chunks_generated = 0;

        for (int i = 0; i < CHUNKS_TO_GENERATE; i++) {
            int chunk_x = chunks_x_count * CHUNK_WIDTH;
            int chunk_y = chunks_y_count * CHUNK_WIDTH;

            Rectangle rect {
                (float)chunk_x,
                (float)chunk_y,
                CHUNK_WIDTH,
                CHUNK_WIDTH,
            };

            Image perlin_crop_copy = ImageCopy(perlin_image);
            ImageCrop(&perlin_crop_copy, rect);

            Chunk* chunk = new Chunk(&perlin_crop_copy, Vector2{ static_cast<float>(chunk_x), static_cast<float>(chunk_y)});
            this->chunks.push_back(chunk);
            UnloadImage(perlin_crop_copy);

            if (chunks_x_count == (sqrt(CHUNKS_TO_GENERATE) - 1)) {
                chunks_y_count++;
                chunks_x_count = 0;
            }
            else {
                chunks_x_count++ ;
            }

            chunks_generated++;
        }

        UnloadImage(perlin_image);
    }

    static float CalculateDistance(Vector3 pos1, Vector3 pos2) {
        return hypot(
            hypot(
                pos1.x - pos2.x, pos1.y - pos2.y
            ),
            pos1.z - pos2.z
        );
    }

    void Draw() {
        for (const auto& chunk : this->chunks) {
            Vector3 chunk_pos = chunk->blocks[0]->GetPosition();
            float distance = (float)hypot(
                        hypot(
                            chunk_pos.x - this->camera_ref->position.x, chunk_pos.y - this->camera_ref->position.y
                        ),
                chunk_pos.z - this->camera_ref->position.z);

            if (distance < RENDER_DISTANCE) {
                chunk->Draw();
            }
        }
    }
};