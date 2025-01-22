#include <raylib.h>
#include <format>
#include <string>
#include "chunk-manager.h"

const int screenWidth = 1200;
const int screenHeight = 850;

int main() {
	InitWindow(screenWidth, screenHeight, "Minceraft");

	Camera3D camera = { 0 };
	camera.position = Vector3{ 95.0f, 20.0f, 55.0f };
	camera.target = Vector3{ 0.0f, 0.0f, 0.0f };
	camera.up = Vector3{ 0, 1.f, 0 };
	camera.fovy = 65.0f;
	camera.projection = CAMERA_PERSPECTIVE;

	DisableCursor();
	SetTargetFPS(60);

	auto* cm = new ChunkManager(&camera);
	cm->GenerateWorld();

	while (!WindowShouldClose()) {
		UpdateCamera(&camera, CAMERA_FREE);

		BeginDrawing();
		ClearBackground(WHITE);
		BeginMode3D(camera);

		cm->Draw();

		EndMode3D();

		DrawFPS(25, 25);
        DrawText(
                std::format("x: {}\ty: {}\tz: {}\n", (int)camera.position.x, (int)camera.position.y, (int)camera.position.z).c_str(),
                25,
                50,
                18,
                BLACK
                );

		EndDrawing();
	}

	delete cm;
	CloseWindow();
	return 0;
}