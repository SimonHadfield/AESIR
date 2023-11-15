#include "GameLayer.h"
// #include "imgui/imgui.h"

#include <iostream>

GameLayer::GameLayer()
{
	// prior to adding glm::transforms
	paddle1 = Paddle(Player::Player1, -0.8f, -0.1f, 0.03f, 0.3f);
	paddle2 = Paddle(Player::Player2, 0.7f, -0.1f, 0.03f, 0.3f);

	ball = Ball(0.0f, 0.0f);


}

void GameLayer::Init()
{

}

void GameLayer::OnAttach()
{
	HA_TRACE("Attached");
}

void GameLayer::OnDetach()
{
	HA_TRACE("Detached");
}

void GameLayer::OnUpdate()
{
	// update timer
	cur_t = Hana::Time::GetTime();
	dt = cur_t - prev_t;
	prev_t = cur_t;

	// Select players
	if (Hana::Input::IsKeyPressed(HA_KEY_1) && !(playerNumberSelect)) {
		//HA_TRACE("Enter pressed");
		playerNumberSelect = true;
		playerNumber = 1; // One player
	}
	else if (Hana::Input::IsKeyPressed(HA_KEY_2) && !(playerNumberSelect)) {
		//HA_TRACE("Enter pressed");
		playerNumberSelect = true;
		playerNumber = 2; // Two players
	}

	// Start game
	if (Hana::Input::IsKeyPressed(HA_KEY_ENTER) && !(StartGame) && (playerNumberSelect)) {
		//HA_TRACE("Enter pressed");
		StartGame = true;
		ball.StartMoving();
	}

	// Player 1:
	if (Hana::Input::IsKeyPressed(HA_KEY_W)) {
		//HA_TRACE("W pressed");
		paddle1.MoveUp(dt);
	}
	if (Hana::Input::IsKeyPressed(HA_KEY_S)) {
		//HA_TRACE("S pressed");
		paddle1.MoveDown(dt);
	}


	// Player 2: 

	if (playerNumber == 1) // Ai player - difficulty 1-3, 3 hardest
	{
		if (paddle2.GetPos().second + 0.5 * paddle2.GetDimensions().second < ball.GetBallPosY() + 0.5 * ball.GetBallHeight())
			paddle2.MoveUp(dt);
		if (paddle2.GetPos().second + 0.5 * paddle2.GetDimensions().second > ball.GetBallPosY() + 0.5 * ball.GetBallHeight() )
			paddle2.MoveDown(dt);
	}
	else // User Player
	{
		if (Hana::Input::IsKeyPressed(HA_KEY_UP)) {
			//HA_TRACE("W pressed");
			paddle2.MoveUp(dt);
		}
		if (Hana::Input::IsKeyPressed(HA_KEY_DOWN)) {
			//HA_TRACE("S pressed");
			paddle2.MoveDown(dt);
		}
	}

	if (ball.ResetGame())
	{
		playerNumberSelect = false;
		StartGame = false;
		ball.SetReset();
	}


	paddle1.CollisionBoundary();
	paddle2.CollisionBoundary();
	ball.PaddleCollision(paddle1);
	ball.PaddleCollision(paddle2);

	HA_TRACE(paddle1.GetScore());
	//HA_TRACE(paddle2.GetScore());

	ball.BoundaryCollision(paddle1, paddle2);
	ball.UpdatePos(dt);
}

void GameLayer::OnRender()
{
	//HA_TRACE("Rendering");

	paddle1.Draw();
	paddle2.Draw();

	ball.Draw();

	// render background - need to add mvp transforms
	Renderable::DrawBackground();
}

void GameLayer::OnImGuiRender()
{

}