#pragma once

#include "Hana.h"
#include "Hana/Time.h"
#include "Hana/Input.h"
#include "Hana/KeyCodes.h"
#include "Hana/MouseButtonCodes.h"
#include "Hana/StateMachine.h"

class GameObject {
public:
	virtual glm::vec3 GetPos() { return this->pos; }
	virtual glm::vec2 GetSize() { return this->size; }
	float GetGap() { return this->gap; }
	virtual void SetPos(glm::vec3 Position) { this->pos = Position; }
	virtual void SetSize(glm::vec2 Size) { this->size = Size; }
	void SetGap(float Gap) { this->gap = Gap; }
	void SetOffset(float Offset) { offset = Offset; }
	float GetOffset() { return offset; }
private:
	glm::vec3 pos;
	glm::vec2 size;
	float gap;
	float offset;
};

class Character : public GameObject
{
public:
	glm::vec3 GetPos() override { return PlayerPos; }
	void SetPos(glm::vec3 playerPos) override { PlayerPos = playerPos; }
	void UpdatePos(double dt);
	void Jump(double dt);
	void Gravity(double dt);
	void SetFloor(float Floor) { floor = Floor;}
	void IncrementScore() { score++; }
	unsigned int GetScore() { return score;}
private:
	float Jump_force = 2 * 100000.0f;
	float dy = 0.0f;
	float g = 4.0f * 1000;
	glm::vec3 PlayerPos;
	glm::vec2 size;
	float floor = 500.0f;
	unsigned int score = 0;
};

class GameLayer : public Hana::Layer
{
public:
	std::vector<GameObject> PipePairs;
	GameLayer();
	virtual ~GameLayer() override;

	virtual void LoadResources() override;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnRender() override;
	virtual void OnUpdate() override;
	virtual void OnImGuiRender() override;

	void displayFPS(double dt);

private:
	Character Player;
	GameObject PipePair;
	StateMachine* stateMachine; // instantiate StateMachine

	// Game States
	// GameStartState* gameStartState;
	// GamePlayState* gamePlayState;
	// GameOverState* gameOverState;

	Renderable *renderable;
	float Width = 720;
	float Height = 1080;

	float left = 1.0f;
	float right = 1.0f;
	float bottom = 1.0f;
	float top = 1.0f;
	float nearClip = 1.0f;
	float farClip = 1.0f;
	OrthographicCamera camera;

	//temp variables
	float multiplier = 1.0f;
	float loopingPoint = 1176.697f * multiplier;

	float cam_x = 0.0f;
	float cam_y = 000.0f;
	float cam2_x = 0.0f;
	float cam2_y = 100.0f;
	float cam3_x = 1700.0f + 1157;

	float ground_speed = 500.0f;
	float min_gap = 200.0f;
	float max_gap = 300.0f;

	float jump_cooldown_timer = 0.15f;
	bool jump_cooldown = false;
	bool gameOver = false;

	const char* path = "../HANA/src/Renderer/res/textures/Logo.png";

	
	struct Graphics {
		static inline const char* background =	"./src/TrumpJump/graphics/background.png";
		static inline const char* ground =		"./src/TrumpJump/graphics/ground.png";
		static inline const char* turdpipe =	"./src/TrumpJump/graphics/turdpipe.png";
		static inline const char* character =	"./src/TrumpJump/graphics/TrumpJumpCharacterIdle.png";
	};

	struct TurdPipe {
		float x, y;
	};



	double cur_t = 0.0;
	double fps = 0.0;
	double prev_t = 0.0;
	double fixed_timestep = 0.5;
	double dt = 0.0;
	double fps_timer = 0.0;

	float width = 100.0f;
	float height = 100.0f;
	float x = 1080.0f / 2.0f - width/2.0f;
	float y = 0.0f;
	float vy_cur = 0.0f;
	float vy_prev = 0.0f;

	float g = 5.0f * (100000000);
	float force_y = 2.5f * (100000);
	float floor = 1000.0f;

	float gap_timer;



	Hana::Application appInstance;

};