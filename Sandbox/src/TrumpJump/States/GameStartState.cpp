#include "Aesir/StateMachine.h"
#include "../GameLayer.h"

class GameStartState : public State {
public:
	GameStartState();

	void Enter() override;
	void Update(double dt) override;
	void Exit() override;
private:
	//GameLayer& gameLayer;
	//StateMachine& stateMachine;
	//GamePlayState*& gamePlayState;
	
};