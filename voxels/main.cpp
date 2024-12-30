#include <raylib.h>
#include "chunk_manager.h"

const int screenWidth = 800;
const int screenHeight = 450;

int main() {
	InitWindow(screenWidth, screenHeight, "Minceraft");
	
	Camera3D camera = { 0 };
	camera.position = Vector3{ 0.0f, 0.0f, 99.0f };
	camera.target = Vector3{ 0.0f, 0.0f, 0.0f };
	camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
	camera.fovy = 45.0f;
	camera.projection = CAMERA_PERSPECTIVE;

	DisableCursor();
	SetTargetFPS(60);

	//ChunkManager* cm = new ChunkManager(&camera);

	// GetColor

	while (!WindowShouldClose()) {
		UpdateCamera(&camera, CAMERA_FREE);

		BeginDrawing();
		ClearBackground(RAYWHITE);
		BeginMode3D(camera);

			//cm->Update();
		DrawBillboard(camera, tex, Vector3{ 0, 0, 0 }, 1, RAYWHITE);
		

		EndMode3D();
		EndDrawing();
	}

	CloseWindow();
	return 1;
}