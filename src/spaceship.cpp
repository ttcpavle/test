#include "../includes/spaceship.h"

Spaceship::Spaceship() {
	image = LoadTexture("assets/Graphics/spaceship.png");
	position.x = (GetScreenWidth() - image.width) / 2;
	position.y = GetScreenHeight() - image.height;
	lastFireTime = 0;
}

Spaceship::~Spaceship() {
	UnloadTexture(image);
}

void Spaceship::Draw() {
	DrawTextureV(image, position, WHITE);
}

void Spaceship::MoveLeft() {
	position.x -= 7;
	if (position.x < 0) {
		position.x = 0;
	}
}

void Spaceship::MoveRight() {
	position.x += 7;
	if (position.x + image.width > GetScreenWidth()) {
		position.x = GetScreenWidth() - image.width;
	}
}

void Spaceship::FireLaser() {
	if (GetTime() - lastFireTime >= 0.3) {
		lasers.push_back(Laser({ position.x + image.width / 2 - 2, position.y }, -6));
		lastFireTime = GetTime();
	}
}

