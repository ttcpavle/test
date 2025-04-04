#pragma once
#include "spaceship.h"
#include "obstacle.h"

class Game {
public:
	Game();
	~Game();
	void Draw();
	void Update();
	void HandleInput();
private:
	Spaceship spaceship;
	void CreateObstacles();
	void DeleteInactiveLasers();
	std::vector<Obstacle> obstacles;
};