#include <raylib.h>
#include <vector>
#include <iostream>
#include "chunk.h"
#include <cassert>

class ChunkManager {
private:
    const int BASIC_BLUR_SIZE = 5;

    static const int CHUNK_WIDTH = 16;
    static const int CHUNKS_TO_GENERATE = 64;
    std::vector<Chunk*> chunks;
public:
    ChunkManager() {
        double result_value = 0;
        double fraction = modf(this->CHUNKS_TO_GENERATE, &result_value);
        assert(result_value != 0);
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
        int chunks_generated = 0;

        for (int i = 0; i < CHUNKS_TO_GENERATE; i++) {
            int chunk_x = chunks_x_count * CHUNK_WIDTH;
            int chunk_y = chunks_y_count * CHUNK_WIDTH;

            Rectangle rect {
                chunk_x,
                chunk_y,
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

        std::cout << "Chunks generated: " << chunks_generated << std::endl;
        UnloadImage(perlin_image);
    }

    void Draw() {
        for (int i = 0; i < CHUNKS_TO_GENERATE; i++) {
            this->chunks[i]->Draw();
        }
    }

    void Update() {
        //for (int i = 0; i < CHUNKS_TO_GENERATE; i++) {
        //    Vector3 pos = this->chunks[i]->blocks[0].GetPosition();
        //    float distance = (float)hypot(
        //        hypot(
        //            pos.x - this->camera_ref->position.x, pos.y - this->camera_ref->position.y
        //        ),
        //        pos.z - this->camera_ref->position.z);

        //    if (distance > 100.f) {
        //        std::cout << "do something" << std::endl;
        //        return;
        //    }

        //    this->chunks[i]->Draw();
        //}
    }
};