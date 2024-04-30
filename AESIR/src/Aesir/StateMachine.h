#pragma once

#include "Core.h"

class AESIR_API State {
	public:
		virtual void Enter() = 0;
		virtual void Update(double dt) = 0;
		virtual void Exit() = 0;
		virtual ~State() = default;
	};

class AESIR_API StateMachine {
public:
	StateMachine::StateMachine() : currentState(nullptr) {};
	virtual void ChangeState(State* newState);
	virtual void Update(double dt);
private:
	State* currentState = nullptr;
};