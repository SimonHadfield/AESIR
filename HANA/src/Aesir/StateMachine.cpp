#include "StateMachine.h"


void StateMachine::ChangeState(State* newState) {
	
	if (currentState) {
		currentState->Exit();
	}
	currentState = newState;
		
	if (currentState) {
		currentState->Enter();
	}
}

void StateMachine::Update(double dt) {
	if (currentState) {
		currentState->Update(dt);
	}
}
