#include <raylib.h>
#include "block.hpp"
#include <vector>

const int screenWidth = 800;
const int screenHeight = 450;

int main() {
	InitWindow(screenWidth, screenHeight, "Minceraft");
	
	Camera3D camera = { 0 };
	camera.position = Vector3{ 10.0f, 10.0f, 10.0f };
	camera.target = Vector3{ 0.0f, 0.0f, 0.0f };
	camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
	camera.fovy = 45.0f;
	camera.projection = CAMERA_PERSPECTIVE;

	DisableCursor();
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		UpdateCamera(&camera, CAMERA_FREE);

		BeginDrawing();
		ClearBackground(RAYWHITE);
		BeginMode3D(camera);

		// Loop

		EndMode3D();
		EndDrawing();
	}

	CloseWindow();
	return 1;
}