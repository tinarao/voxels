#include <raylib.h>
#include "chunk_manager.h"

const int screenWidth = 1200;
const int screenHeight = 850;

int main() {
	InitWindow(screenWidth, screenHeight, "Minceraft");
	
	Camera3D camera = { 0 };
	camera.position = Vector3{ 35.0f, 60.0f, 55.0f };
	camera.target = Vector3{ 0.0f, 0.0f, 0.0f };
	camera.up = Vector3{ 0, 1.f, 0 };
	camera.fovy = 65.0f;
	camera.projection = CAMERA_PERSPECTIVE;

	DisableCursor();
	SetTargetFPS(60);

	ChunkManager *cm = new ChunkManager();
	cm->GenerateWorld();

	while (!WindowShouldClose()) {
		UpdateCamera(&camera, CAMERA_FREE);

		BeginDrawing();
		ClearBackground(RAYWHITE);
		BeginMode3D(camera);

		cm->Draw();
		
		EndMode3D();
		EndDrawing();
	}

	delete cm;
	CloseWindow();
	return 0;
}