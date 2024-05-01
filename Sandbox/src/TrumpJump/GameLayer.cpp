#include "GameLayer.h"
#include "glad/glad.h"

#include <random>
#include <filesystem>

// character jump
void Character::Jump(double dt) {
	dy = - Jump_force * dt;
	PlayerPos.y += dy * dt;
}

void Character::UpdatePos(double dt) {
	if (PlayerPos.y < floor) {
		dy += g * dt;
		PlayerPos.y += dy * dt;
	}
	else {
		PlayerPos.y = floor;
	}
}

void Character::Gravity(double dt) {
	if (PlayerPos.y < floor) {
		PlayerPos.y += g * dt;
	}
	else
	{
		PlayerPos.y = floor;
	}
}

// GameLayer
GameLayer::GameLayer() {
AE_TRACE(x);
AE_TRACE(y);
AE_TRACE(width);
AE_TRACE(height);


// init pipe pairs
int no_pipe_pairs = 3;

// Create a random device
std::random_device rd;
// Initialize Mersenne Twister pseudo-random generator
std::mt19937 gen(rd());
// Uniform real distribution between two floats

std::uniform_real_distribution<> dis(min_gap, max_gap);

for (int i = 0; i < no_pipe_pairs; i++) {
	PipePairs.push_back(PipePair);
	// 1480 / 5
	PipePairs[i].SetPos(glm::vec3( 1280.0f + (i * (1480.0f - 210.0f) / no_pipe_pairs), 300.0f, 0.5f));
	PipePairs[i].SetSize(glm::vec3( 70.0f * 2, 288.0f * 2, 0.0f));
	PipePairs[i].SetGap(dis(gen));

}

Player.SetPos(glm::vec3(300.0f, 0.0f, 0.1f));
Player.SetSize(glm::vec2(100.0f, 100.0f));
}

GameLayer::~GameLayer() {
	delete renderable;
}

void GameLayer::LoadResources() {
	// load shaders
	const char* default_vert = "../Aesir/src/Renderer/res/shaders/default.vert";
	const char* default_frag = "../Aesir/src/Renderer/res/shaders/default.frag";
	ResourceManager::LoadShader( default_vert, default_frag, nullptr, "default");
	
	// configure shaders
	float window_width = 1080.0f;
	float window_height = 720.0f;
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(window_width),
		static_cast<float>(window_height), 0.0f, -1.0f, 1.0f);

	// load textures
	ResourceManager::LoadTexture(Graphics::background, true, "scene_background");
	ResourceManager::LoadTexture(Graphics::ground, true, "ground");
	ResourceManager::LoadTexture(Graphics::turdpipe, true, "turdpipe");
	ResourceManager::LoadTexture(Graphics::character, true, "character");


	ResourceManager::GetShader("default").Use().SetInteger("image", 0);
	ResourceManager::GetShader("default").SetMatrix4("projection", projection);


	// set render-specific controls
	this->renderable = new Renderable(ResourceManager::GetShader("default"));
}

void GameLayer::OnAttach() {}
void GameLayer::OnDetach() {}
void GameLayer::displayFPS(double dt) {
	fps_timer += dt;
	if (fps_timer > fixed_timestep) {
		AE_TRACE(fps);
		fps_timer = 0;
	}
}

void GameLayer::OnUpdate()
{
	

	// update timer
	cur_t = Aesir::Time::GetTime();
	dt = cur_t - prev_t;
	prev_t = cur_t;
	fps = 1 / dt;

	displayFPS(dt);

	if (!jump_cooldown && !gameOver)
	{
		if (Aesir::Input::IsKeyPressed(AE_KEY_SPACE) || Aesir::Input::IsMouseButtonPressed(AE_MOUSE_BUTTON_1)) {
			Player.Jump(dt);
			jump_cooldown = true;
		}
	}
	else if (jump_cooldown)
	{
		if (jump_cooldown_timer >= 0)
			jump_cooldown_timer -= dt;
		else {
			jump_cooldown_timer = 0.15f;
			jump_cooldown = false;
		}
	}

	if (Player.GetPos().y > floor)
		Player.SetPos(glm::vec3(Player.GetPos().x, floor, 0.1f));

	else
	{
		vy_cur = vy_prev + g * dt;
		y = y - vy_cur * dt;
		vy_prev = vy_cur;
	}

	cam_x -= (300.0f * dt);

	if (Aesir::Input::IsKeyPressed(AE_KEY_D)) {
		//cam_x += 300.0f * dt;
		loopingPoint += 10.0f;
		AE_TRACE(loopingPoint);
	}

	if (cam_x < -loopingPoint) {
		cam_x += loopingPoint;
	}

	if (cam2_x < -1700.0f - 1157) {
		cam2_x = 1700.0f + 1157;
	}
	if (cam3_x < -1700.0f - 1157) {
		cam3_x = 1700.0f + 1157;
	}

	cam2_x -= 100.0f * dt;
	cam3_x -= 100.0f * dt;

	gap_timer += dt;
	if (gap_timer > 2) {
		if (min_gap > 100)
			min_gap -= 10; gap_timer = 0;
	}

	if (!gameOver) {

		for (int i = 0; i < PipePairs.size(); i++) {
			// collision bottom pipe
			float offset = PipePairs[i].GetOffset();
			if (((Player.GetPos().x + Player.GetSize().x * 0.5 > PipePairs[i].GetPos().x) &&
				(Player.GetPos().y < PipePairs[i].GetPos().y + PipePairs[i].GetSize().y - PipePairs[i].GetGap() + offset)) &&
				((Player.GetPos().x < PipePairs[i].GetPos().x + PipePairs[i].GetSize().x) &&
					(Player.GetPos().y + Player.GetSize().y * 0.5 > PipePairs[i].GetPos().y - PipePairs[i].GetGap() + offset)))
			{
				gameOver = true;
				Player.Jump(dt);
			}

			// collision top pipe
			if (((Player.GetPos().x + Player.GetSize().x * 0.5 > PipePairs[i].GetPos().x) &&
				((Player.GetPos().x < PipePairs[i].GetPos().x + PipePairs[i].GetSize().x) &&
					(Player.GetPos().y + Player.GetSize().y * 0.5 > PipePairs[i].GetPos().y + PipePairs[i].GetGap()))))
			{
				gameOver = true;
				Player.Jump(dt);
			}

			// if player passes pipe
			if (Player.GetPos().x + Player.GetSize().x * 0.5 == PipePairs[i].GetPos().x + PipePairs[i].GetSize().x * 0.5)
				Player.IncrementScore();
		}
	}

	if (gameOver) {
		
		Player.SetFloor(800.0f);
		ground_speed = 0;
	}
	// move pillars

	// Create a random device
std::random_device rd;
// Initialize Mersenne Twister pseudo-random generator
std::mt19937 gen(rd());
// Uniform real distribution between two floats

std::uniform_real_distribution<> dis(min_gap, max_gap);
std::uniform_real_distribution<> dis2(-200.0, 200.0);
float offset = dis2(gen);
	for (int i = 0; i < PipePairs.size(); i++) {
		glm::vec3 pos = PipePairs[i].GetPos();
		float gap = PipePairs[i].GetGap();
		float offset = PipePairs[i].GetOffset();
		// if pillar beyond scope of view (move right to side of screen)
		if (pos.x < -200) {
			PipePairs[i].SetPos(glm::vec3(pos.x + 1080 + 200, pos.y, pos.z));
			PipePairs[i].SetGap(dis(gen));
			PipePairs[i].SetOffset(offset);
		}

		else {
			PipePairs[i].SetPos(glm::vec3(pos.x - ground_speed * dt, pos.y, pos.z));
		}
	}

	Player.UpdatePos(dt);
}

void GameLayer::OnRender()
{
	renderable->DrawTextureQuad2D(ResourceManager::GetTexture("scene_background"), glm::vec3(cam_x, cam_y, -0.5f), glm::vec2(1157 * 2.5 * multiplier, 228 * 3.5), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));

	renderable->DrawTextureQuad2D(ResourceManager::GetTexture("character"), Player.GetPos(), Player.GetSize(), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));

	for (int i = 0; i < PipePairs.size(); i++) {
		glm::vec3 pos = PipePairs[i].GetPos();
		glm::vec2 size = PipePairs[i].GetSize();
		float gap = PipePairs[i].GetGap();
		float offset = PipePairs[i].GetOffset();
		// clip sprite at end (strip of non transparent pixels)
		renderable->DrawTextureQuad2D(ResourceManager::GetTexture("turdpipe"), pos + gap * glm::vec3(0.0f, 0.5f, 0.0f) + glm::vec3(0.0f, offset, 0.0f), size, 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
		renderable->DrawTextureQuad2D(ResourceManager::GetTexture("turdpipe"), pos - gap * glm::vec3(0.0f, 0.5f, 0.0f) + glm::vec3(140.0f, offset, 0.0f), size, 180, glm::vec3(1.0f, 1.0f, 1.0f));
	}



}

void GameLayer::OnImGuiRender()
{
	//renderable->DrawImGuiText("Trump Jump", 0, 50, 2.0f, 2);
	renderable->DrawImGuiText("Score: " + std::to_string(Player.GetScore()), 0, 150, 2.0f, 2);
}