#include "GameLayer.h"
#include "imgui/imgui.h"

#include <iostream>
#include <string>

// ___ Implement GameStates ___

// Game Start State
GameStartState::GameStartState(GameLayer& gameLayer, StateMachine*& stateMachine, GamePlayState*& gamePlayState, Paddle& p1, Paddle& p2, Ball& b) : gameLayer(gameLayer), stateMachine(*stateMachine), gamePlayState(gamePlayState), paddle1(p1), paddle2(p2), ball(b) {}
void GameStartState::Enter() {
	// set paddle and ball positions
	paddle1.PaddleReset(-0.8f, -0.1f);
	paddle2.PaddleReset(0.7f, -0.135f);
	ball.SetResetRound();
	paddle1.ScoreReset(); paddle2.ScoreReset();
};
void GameStartState::Update(double dt) {
	
	Renderable::DrawImGuiText("Press 1 for single player mode", 0, 200, 2.0f, 2);
	Renderable::DrawImGuiText("Press 2 for dual player mode", 0, 240, 2.0f, 2);

	if (Hana::Input::IsKeyPressed(HA_KEY_1)) {
		gameLayer.SetPlayerNumber(1);
		stateMachine.ChangeState(gamePlayState);
	}
	if (Hana::Input::IsKeyPressed(HA_KEY_2)) {
		gameLayer.SetPlayerNumber(2);
		stateMachine.ChangeState(gamePlayState);
	}
};
void GameStartState::Exit() {};

// Game Play State
GamePlayState::GamePlayState(GameLayer& gameLayer, StateMachine*& stateMachine, GameOverState*& gameOverState, Paddle& p1, Paddle& p2, Ball& b) : gameLayer(gameLayer), stateMachine(*stateMachine), gameOverState(gameOverState), paddle1(p1), paddle2(p2), ball(b) {}
void GamePlayState::Enter() {};
void GamePlayState::Update(double dt) {
	
	if (Hana::Input::IsKeyPressed(HA_KEY_ENTER) && !isRoundStarted) {
		ball.StartMoving();
		isRoundStarted = true;
	}

	// Player 1:
	if (Hana::Input::IsKeyPressed(HA_KEY_W)) {
		paddle1.MoveUp(dt);
	}
	if (Hana::Input::IsKeyPressed(HA_KEY_S)) {
		paddle1.MoveDown(dt);
	}

	// Player 2: 
	int playerNumber = gameLayer.GetPlayerNumber();

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
			paddle2.MoveUp(dt);
		}
		if (Hana::Input::IsKeyPressed(HA_KEY_DOWN)) {
			paddle2.MoveDown(dt);
		}
	}

	if (ball.ResetRound())
	{
		//playerNumberSelect = false;
		isRoundStarted = false;
		ball.SetResetRound();
		paddle1.PaddleReset(-0.8f, -0.1f);
		paddle2.PaddleReset(0.7f, -0.1f);
	}


	// Collisions
	paddle1.CollisionBoundary();				// contain paddles within screen
	paddle2.CollisionBoundary();				// ''
	ball.PaddleCollision(paddle1);				// ball collision with paddles
	ball.PaddleCollision(paddle2);				// ''
	ball.BoundaryCollision(paddle1, paddle2);	// ball collision with walls

	ball.UpdatePos(dt);

	// winning/losing condition 
	if (paddle1.GetScore() > 2 || paddle2.GetScore() > 2) {
		stateMachine.ChangeState(gameOverState); isRoundStarted = false;
	}

};
void GamePlayState::Exit() {};

// Game Over State
GameOverState::GameOverState(GameLayer& gameLayer, StateMachine*& stateMachine, GameStartState*& gameStartState, Paddle& p1, Paddle& p2, Ball& b) : gameLayer(gameLayer), stateMachine(*stateMachine), gameStartState(gameStartState), paddle1(p1), paddle2(p2), ball(b) {}
void GameOverState::Enter() {};
void GameOverState::Update(double dt) {

	// winning state
	if (paddle1.GetScore() > 2) {
		Renderable::DrawImGuiText("Player 1 wins!", 0, 100, 2.0f, 2);
		Renderable::DrawImGuiText("Press Enter to play again", 0, 150, 2.0f, 2);
	}
	if (paddle2.GetScore() > 2) {
		Renderable::DrawImGuiText("Player 2 wins!", 0, 100, 2.0f, 2);
		Renderable::DrawImGuiText("Press Enter to play again", 0, 150, 2.0f, 2);
	}

	// if enter pressed return to start state
	if (Hana::Input::IsKeyPressed(HA_KEY_ENTER))
		stateMachine.ChangeState(gameStartState);
};
void GameOverState::Exit() {};

// GameLayer
GameLayer::GameLayer() : stateMachine(), gameStartState(nullptr), gamePlayState(nullptr), gameOverState(nullptr) {
	// prior to adding glm::transforms
	paddle1 = Paddle(Player::Player1, -0.8f, -0.1f, 0.03f, 0.3f); // -0.1f y
	paddle2 = Paddle(Player::Player2, 0.7f,  -0.1f, 0.03f, 0.3f); // -0.1f y
	ball = Ball(0.0f, 0.0f);
	
	stateMachine = new StateMachine();
	gameStartState = new GameStartState(*this, stateMachine, gamePlayState, paddle1, paddle2, ball);
	gamePlayState = new GamePlayState(*this, stateMachine, gameOverState, paddle1, paddle2, ball);
	gameOverState = new GameOverState(*this, stateMachine, gameStartState, paddle1, paddle2, ball);
	
	stateMachine->ChangeState(gameStartState); // initial state
}
GameLayer::~GameLayer() { delete stateMachine; }
void GameLayer::OnAttach() {}
void GameLayer::OnDetach() {}
void GameLayer::displayFPS(double dt) {
	timer += dt;
	if (timer > fixed_timestep) {
		HA_TRACE(fps);
		timer = 0;
	}
}
void GameLayer::OnUpdate()
{
	// update timer
	cur_t = Hana::Time::GetTime();
	dt = cur_t - prev_t;
	prev_t = cur_t;
	fps = 1 / dt;

	// update states
	stateMachine->Update(dt);

	//displayFPS(dt);

}
void GameLayer::OnRender()
{
	paddle1.Draw();
	paddle2.Draw();

	ball.Draw();

	// render background - need to add mvp transforms
	Renderable::DrawBackground();
}

void GameLayer::OnImGuiRender()
{
	Renderable::DrawImGuiText("PONG", 0, 50, 2.0f, 2);
	Renderable::DrawImGui(paddle1.GetScore(), paddle2.GetScore());
	Renderable::DrawImGuiText(std::to_string(paddle1.GetScore()));
}

