#include <raylib.h>
#include "chunk_manager.hpp"

const int screenWidth = 800;
const int screenHeight = 450;

int main() {
	InitWindow(screenWidth, screenHeight, "Minceraft");
	
	Camera3D camera = { 0 };
	camera.position = Vector3{ 100.0f, 100.0f, 100.0f };
	camera.target = Vector3{ 0.0f, 0.0f, 0.0f };
	camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
	camera.fovy = 45.0f;
	camera.projection = CAMERA_PERSPECTIVE;

	DisableCursor();
	SetTargetFPS(60);

	ChunkManager* cm = new ChunkManager(&camera);

	while (!WindowShouldClose()) {
		UpdateCamera(&camera, CAMERA_FREE);

		BeginDrawing();
		ClearBackground(RAYWHITE);
		BeginMode3D(camera);


			cm->Update();


		EndMode3D();
		EndDrawing();
	}

	CloseWindow();
	return 1;
}