#pragma once

#include "Hana.h"
#include <random>

enum Player {
	Player1,
	Player2
};

struct Wall {
	static inline int wall_left = -1.0, wall_right = 1.0, wall_top = 1.0, wall_bottom = -1.0;
};

class Paddle {
public:
	// Default constructor
	Paddle() : player(Player1), x(0.0f), y(0.0f), width(0.1f), height(0.1f) {}
	// Constructor with arguments
	Paddle(Player player, float x, float y, float width, float height) : player(player), x(x), y(y), width(width), height(height), score(0) {}

	void MoveUp(double dt);
	void MoveDown(double dt);
	void CollisionBoundary();
	void PaddleReset(float start_x, float start_y);

	void Draw();

	int GetScore() const { return score; }
	void incrementScore() { score++; }
	void ScoreReset() { score = 0; }

	Player GetPlayer() { return player; }
	std::pair<float, float> GetPos() { return { x, y }; }
	std::pair<float, float> GetDimensions() { return { width, height }; }
	std::pair<int, float> GetSpeed() { return { Direction, paddle_speed }; }

private:
	Player player;
	float paddle_speed = 0.8;
	unsigned int Direction = 3; // 3 up, 1 down
	float x = 1.0f;
	float y = 1.0f;
	float width, height = 1.0f;
	int score;
};

class Ball {
public:
	Ball() : x(0.0f), y(0.0f) {}

	Ball(float x, float y) : x(x), y(y) {}

	void StartMoving();
	void UpdatePos(double dt);

	void BoundaryCollision(Paddle& paddle1, Paddle& paddle2);
	void PaddleCollision(Paddle& paddle);
	float GetBallPosY() { return y; }
	float GetBallHeight() { return height; }

	void Draw();

	bool ResetRound() { return resetRound; }
	void SetResetRound() { resetRound = false; }

private:
	static inline float width = 0.018f;
	static inline float height = 0.03f;
	float Ball_speed_x = 0.0f;
	float Ball_speed_y = 0.0f;
	float x = 1.0f;
	float y = 1.0f;
	bool resetRound = false;
};




class Level
{
public:
	void Init();
	void OnRender();

	// void OnUpdate(TimeStep ts);
	// void OnImGuiRender();
	
	bool GameOver() const { return m_GameOver; };
	// void Reset();

private:
	bool m_GameOver = false;

};

