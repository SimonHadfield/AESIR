#include "Level.h"


void Level::Init()
{};


void Paddle::Draw() {
	Renderable::DrawQuad2D(x, y, width, height);
};

void Paddle::MoveUp(double dt) {
	y += paddle_speed * dt;
	Direction = 3;
}

void Paddle::MoveDown(double dt) {
	y -= paddle_speed * dt;
	Direction = 1;
}

void Paddle::PaddleReset(float start_x, float start_y) {
	x = start_x;
	y = start_y;
}

void Paddle::CollisionBoundary() {

	if (y <= Wall::wall_bottom)
		y = Wall::wall_bottom;
	if (y + height > Wall::wall_top)
		y = Wall::wall_top - height;
}


void Ball::StartMoving() {
	// Create a random number engine
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_real_distribution<> distribution(0.35f, 0.6f);
	std::uniform_int_distribution<> distribution_int(0, 1);
	bool negative_x = distribution_int(gen);
	bool negative_y = distribution_int(gen);

	// Give ball random speed (random direction within given speed range above)
	if (negative_x)
		Ball_speed_x = -distribution(gen);
	if (negative_y)
		Ball_speed_y = -distribution(gen);
	if (!negative_x)
		Ball_speed_x = distribution(gen);
	if (!negative_y)
		Ball_speed_y = distribution(gen);

}

void Ball::BoundaryCollision(Paddle& paddle1, Paddle& paddle2) {
	// if ball hits walls bounce off

	if (x < Wall::wall_left) {
		paddle2.incrementScore(); // Player 2 scores
		x = 0.0f; y = 0.0f; Ball_speed_x = 0.0f; Ball_speed_y = 0.0f; resetRound = true;
	}
	if (x + width > Wall::wall_right) {
		paddle1.incrementScore(); // Player 1 scores
		x = 0.0f; y = 0.0f; Ball_speed_x = 0.0f; Ball_speed_y = 0.0f; resetRound = true; 
	}

	if (y <= Wall::wall_bottom)
	{
		Ball_speed_y = -Ball_speed_y;
		y = Wall::wall_bottom; // prevent clipping into wall
	}
	if (y + height > Wall::wall_top)
	{
		Ball_speed_y = -Ball_speed_y;
		y = Wall::wall_top - height; // prevent clipping into wall
	}
}

void Ball::PaddleCollision(Paddle& paddle) {

	Player paddlePlayer = paddle.GetPlayer();
	std::pair<float, float> PaddlePos = paddle.GetPos();
	std::pair<float, float> PaddleDimensions = paddle.GetDimensions();
	std::pair<int, float> paddleVelocity = paddle.GetSpeed();


	if (paddlePlayer == Player::Player1) {
		if ( ( (x + width > PaddlePos.first) && (x < PaddlePos.first + PaddleDimensions.first) )
			&& ( (y + height >= PaddlePos.second) && (y <= PaddlePos.second + PaddleDimensions.second) ) )
		{
			x = PaddlePos.first + PaddleDimensions.first;
			Ball_speed_x = -Ball_speed_x;
			Ball_speed_y = Ball_speed_y + 0.5 * (paddleVelocity.first - 2) * paddleVelocity.second ; // add fraction of paddle speed
		}
	}
	else if (paddlePlayer == Player::Player2)
	{
		if (((x + width >= PaddlePos.first) && (x <= PaddlePos.first + PaddleDimensions.first))
			&& ((y + height >= PaddlePos.second) && (y <= PaddlePos.second + PaddleDimensions.second)))
		{
			x = PaddlePos.first - width;
			Ball_speed_x = -Ball_speed_x;
			Ball_speed_y = Ball_speed_y + 0.5 * (paddleVelocity.first - 2) * paddleVelocity.second;; // add fraction of paddle speed
		}
	}
}

void Ball::UpdatePos(double dt) {
	x += Ball_speed_x * dt;
	y += Ball_speed_y * dt;
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