#pragma once


#include "Hana.h"
//#include "Renderer/Renderable.h"

class Paddle {
public:
	Paddle() : x(0.0f), y(0.0f), width(0.1f), height(0.1f) {
		// Default constructor initializes with default values
	}

	Paddle(float x, float y, float width, float height) : x(x), y(y), width(width), height(height) {
		// Constructor with arguments
	}
	void MoveUp(double dt);
	void MoveDown(double dt);

	void Draw();
private:
	float paddle_speed = 0.8;
	float x = 1.0f;
	float y = 1.0f;
	float width = 1.0f;
	float height = 1.0f;
};

class Ball {
public:
	Ball() : x(0.0f), y(0.0f) {}

	Ball(float x, float y) : x(x), y(y) {}

	void MoveUp();
	void MoveDown();
	void Draw();

private:
	static inline float width = 0.01f;
	static inline float height = 0.01f;
	float Ball_test_speed = 0.001;
	float x = 1.0f;
	float y = 1.0f;
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

