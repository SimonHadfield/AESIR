#include "GameLayer.h"
#include <iostream>

GameLayer::GameLayer()
{
	// prior to adding glm::transforms
	paddle1 = Paddle(-0.8f, -0.25f, 0.03f, 0.3f);
	paddle2 = Paddle(0.7f, -0.25f, 0.03f, 0.3f);

	ball = Ball(0.0f, -0.25f);


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


	// Player 1
	if (Hana::Input::IsKeyPressed(HA_KEY_W)) {
		HA_TRACE("W pressed");
		paddle1.MoveUp(dt);
	}

	if (Hana::Input::IsKeyPressed(HA_KEY_S)) {
		HA_TRACE("S pressed");
		paddle1.MoveDown(dt);
	}

	// Player 2
	if (Hana::Input::IsKeyPressed(HA_KEY_UP)) {
		HA_TRACE("W pressed");
		paddle2.MoveUp(dt);
	}

	if (Hana::Input::IsKeyPressed(HA_KEY_DOWN)) {
		HA_TRACE("S pressed");
		paddle2.MoveDown(dt);
	}
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