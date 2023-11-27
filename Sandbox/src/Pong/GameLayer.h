#pragma once

#include "Level.h"
#include "Hana/Time.h"
#include "Hana/Input.h"
#include "Hana/KeyCodes.h"
#include "Hana/MouseButtonCodes.h"

//#include <imgui/imgui.h>

class GameLayer : public Hana::Layer
{
public:
	GameLayer();
	virtual ~GameLayer() = default;

	void Init();
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnRender() override;
	virtual void OnUpdate() override;

	virtual void OnImGuiRender() override;

private:
	Paddle paddle1;
	Paddle paddle2;

	Ball ball;

	Level m_Level;

	bool playerNumberSelect = false;
	int playerNumber = 1; // 1 includes ai, 2 enables second player
	
	enum class State
	{
		StartState = 0, PlayState = 1, GameOverState = 2
	};

	State m_State = State::StartState;

private:
	bool StartGame = false;
	double cur_t = 0.0;
	double prev_t = 0.0;
	double dt = 0.0;
	float fps;
	float fixed_timestep = 0.5;
	float timer = 0;

	Hana::Application appInstance;
};