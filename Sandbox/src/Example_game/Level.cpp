#include "Level.h"


void Level::Init()
{
    // init blocks and ball
};


//Paddle::Paddle(float x, float y, float width, float height) {};

void Paddle::Draw() {
	//Renderable::DrawQuad2D(-0.5f, -0.5f, 10.0f, 10.0f);
	Renderable::DrawQuad2D(x, y, width, height);
	//Renderable::DrawQuad2D(x, y, width, height);
};

void Paddle::MoveUp(double dt) {
	y += paddle_speed * dt;
}

void Paddle::MoveDown(double dt) {
	y -= paddle_speed * dt;
}

void Ball::Draw() {
	Renderable::DrawQuad2D(x, y, width, height);
}

// void Level::OnUpdate()
// {
// 	// collision tests
// 
// 	// movement updates
// 
// 	// score updates
// }

// void Level::OnUpdate() {}
void Level::OnRender()
{
	

}