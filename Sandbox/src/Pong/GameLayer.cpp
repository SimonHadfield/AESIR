#include "GameLayer.h"
#include "imgui/imgui.h"

#include <iostream>
#include <string>

// Implement GameStates
// 
// Game Start State
//  : paddle1(p1), paddle2(p2) 
GameStartState::GameStartState(Paddle& p1, Paddle& p2, Ball& b) : paddle1(p1), paddle2(p2), ball(b) {}

void GameStartState::Enter() {
	// set paddle and ball positions
	paddle1.PaddleReset(-0.8f, -0.1f);
	paddle2.PaddleReset(0.7f, -0.1f);
	ball.SetReset();

};
void GameStartState::Update(double dt) {
	if (Hana::Input::IsKeyPressed(HA_KEY_ENTER)) {}
	//stateMachine.changeState();
};
void GameStartState::Exit() {};

// Game Play State
GamePlayState::GamePlayState(Paddle& p1, Paddle& p2, Ball& b) : paddle1(p1), paddle2(p2), ball(b) {}

void GamePlayState::Enter() {
	//ball.StartMoving();
};
void GamePlayState::Update(double dt) {};
void GamePlayState::Exit() {};

// Game Over State
void GameOverState::Enter() {};
void GameOverState::Update(double dt) {};
void GameOverState::Exit() {};


//  : stateMachine(nullptr), gameStartState(nullptr), gamePlayState(nullptr), gameOverState(nullptr)
GameLayer::GameLayer()  {

	// prior to adding glm::transforms
	paddle1 = Paddle(Player::Player1, -0.8f, -0.1f, 0.03f, 0.3f); // -0.1f y
	paddle2 = Paddle(Player::Player2, 0.7f,  -0.1f, 0.03f, 0.3f); // -0.1f y
	
	stateMachine = new StateMachine();
	gameStartState = new GameStartState(paddle1, paddle2, ball);
	

	ball = Ball(0.0f, 0.0f);

	stateMachine->ChangeState(gameStartState); // initial state
}

GameLayer::~GameLayer() { delete stateMachine; }

void GameLayer::OnAttach()
{
	// HA_TRACE("Attached");
}

void GameLayer::OnDetach()
{
	// HA_TRACE("Detached");
}

void GameLayer::OnUpdate()
{
	// update timer
	cur_t = Hana::Time::GetTime();
	dt = cur_t - prev_t;
	prev_t = cur_t;
	fps = 1 / dt;


	//timer += dt;
	//
	//if (timer > fixed_timestep) {
	//	HA_TRACE(fps);
	//	timer = 0;
	//}

	// stateMachine->Update(dt);

	// Select players
	if (Hana::Input::IsKeyPressed(HA_KEY_1) && !(playerNumberSelect)) {
		playerNumberSelect = true;
		playerNumber = 1; // One player
	}
	else if (Hana::Input::IsKeyPressed(HA_KEY_2) && !(playerNumberSelect)) {
		playerNumberSelect = true;
		playerNumber = 2; // Two players
	}

	// Start game
	if (Hana::Input::IsKeyPressed(HA_KEY_ENTER) && !(StartGame) && (playerNumberSelect)) {
		StartGame = true;
		//stateMachine->ChangeState(gamePlayState);
		ball.StartMoving();
	}

	
	if (StartGame) {

		// Player 1:
		if (Hana::Input::IsKeyPressed(HA_KEY_W)) {
			paddle1.MoveUp(dt);
		}
		if (Hana::Input::IsKeyPressed(HA_KEY_S)) {
			paddle1.MoveDown(dt);
		}


		// Player 2: 

		if (playerNumber == 1) // Ai player - difficulty 1-3, 3 hardest
		{
			if (paddle2.GetPos().second + 0.5 * paddle2.GetDimensions().second < ball.GetBallPosY() + 0.5 * ball.GetBallHeight())
				paddle2.MoveUp(dt);
			if (paddle2.GetPos().second + 0.5 * paddle2.GetDimensions().second > ball.GetBallPosY() + 0.5 * ball.GetBallHeight())
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
			paddle1.PaddleReset(-0.8f, -0.1f);
			paddle2.PaddleReset(0.7f, -0.1f);
		}


		// Collisions

		paddle1.CollisionBoundary();				// contain paddle within screen
		paddle2.CollisionBoundary();

		ball.PaddleCollision(paddle1);				// collision with left paddle
		ball.PaddleCollision(paddle2);				// collision with right paddle
		ball.BoundaryCollision(paddle1, paddle2);	// if ball hits edges of screen
	}


	//HA_TRACE(paddle1.GetScore());
	//HA_TRACE(paddle2.GetScore());

	ball.UpdatePos(dt);

	Renderable::DrawImGuiText("PONG", 0, 100, 2.0f, 2); // "Test", 540, 360, 10.0f

	// winning state
	if (paddle1.GetScore() > 3)
	{
		Renderable::DrawImGuiText("Player 1 wins!");
	}

	if (paddle2.GetScore() > 3)
	{
		Renderable::DrawImGuiText("Player 2 wins!");
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

void GameLayer::OnImGuiRender()
{
	Renderable::DrawImGui(paddle1.GetScore(), paddle2.GetScore());
	Renderable::DrawImGuiText(std::to_string(paddle1.GetScore()));
}

