#include <iostream>
#include "raylib.h"
#include "../includes/game.h"
#include "../includes/obstacle.h"

int main() {

	constexpr int windowWidth = 750;
	constexpr int windowHeight = 700;

	InitWindow(windowWidth, windowHeight, "Raylib Space Invaders");
	SetTargetFPS(60);

	Game game;

	while (!WindowShouldClose()) {

		game.HandleInput();
		game.Update();
		BeginDrawing();
		ClearBackground({29, 29, 27, 255});
		game.Draw();
		EndDrawing();
	}
	CloseWindow();
	return 0;
}