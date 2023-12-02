#pragma once

#include "Level.h"
#include "Hana/Time.h"
#include "Hana/Input.h"
#include "Hana/KeyCodes.h"
#include "Hana/MouseButtonCodes.h"
#include "Hana/StateMachine.h"

//#include <imgui/imgui.h>

class GameStartState;
class GamePlayState;
class GameOverState;

class GameLayer : public Hana::Layer
{
public:
	GameLayer();
	virtual ~GameLayer() override;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnRender() override;
	virtual void OnUpdate() override;

	virtual void OnImGuiRender() override;

	friend class GameStartState;
	friend class GamePlayState;
	friend class GameOverState;

private:
	StateMachine* stateMachine; // instantiate StateMachine

	// Game States
	GameStartState* gameStartState;
	GamePlayState* gamePlayState;
	GameOverState* gameOverState;

	Paddle paddle1;
	Paddle paddle2;
	Ball ball;

	Level m_Level;

	bool playerNumberSelect = false;
	int playerNumber = 1; // 1 includes ai, 2 enables second player

private:
	bool StartGame = false;
	double cur_t = 0.0;
	double prev_t = 0.0;
	double dt = 0.0;
	float fps;
	float fixed_timestep = 0.1;
	float timer = 0;

	Hana::Application appInstance;
};

class GameStartState : public State {
public:
	GameStartState(Paddle& p1, Paddle& p2, Ball& b);

	void Enter() override;
	void Update(double dt) override;
	void Exit() override;
private:
	Paddle& paddle1;
	Paddle& paddle2;
	Ball& ball;
};

class GamePlayState : public State {
public:
	GamePlayState(Paddle& p1, Paddle& p2, Ball& b);

	void Enter() override;
	void Update(double dt) override;
	void Exit() override;
private:
	Paddle& paddle1;
	Paddle& paddle2;
	Ball& ball;
};
class GameOverState : public State {
public:
	GameOverState(Paddle& p1, Paddle& p2, Ball& b);

	void Enter() override;
	void Update(double dt) override;
	void Exit() override;
private:
	Paddle& paddle1;
	Paddle& paddle2;
	Ball& ball;
};
