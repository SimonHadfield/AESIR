#include "GameLayer.h"
#include "glad/glad.h"

#include <filesystem>

// character jump
void Character::Jump(double dt) {
	dy = - Jump_force * dt;
	PlayerPos.y += dy * dt;
	//PlayerPos.y = 0.0f;
	//dy = 0;
}

void Character::UpdatePos(double dt) {
	if (PlayerPos.y < 300.0f) {
		dy += g * dt;
		PlayerPos.y += dy * dt;
	}
}

void Character::Gravity(double dt) {
	if (PlayerPos.y < 720.0f - 300) {
		PlayerPos.y += g * dt;
	}
	else
	{
		PlayerPos.y = 720.0f - 300;
	}
}

// GameLayer
GameLayer::GameLayer() {
HA_TRACE(x);
HA_TRACE(y);
HA_TRACE(width);
HA_TRACE(height);


// init pipe pairs
for (int i = 0; i < 5; i++) {
	PipePairs.push_back(PipePair);
	// 1480 / 5
	PipePairs[i].SetPos(glm::vec3( 0.0f + i * (width + 400) / 3 , 300.0f, 0.5f));
	PipePairs[i].SetSize(glm::vec3( 70.0f * 2, 288.0f * 2, 0.0f));
	PipePairs[i].SetGap(200.0f);

}

Player.SetPos(glm::vec3(300.0f, 0.0f, 0.1f));
}

GameLayer::~GameLayer() {
	delete renderable;
}

void GameLayer::LoadResources() {
	// load shaders
	//ResourceManager::LoadShader("A:/dev/Hana/HANA/HANA/src/Renderer/res/shaders/default.vert", "A:/dev/Hana/HANA/HANA/src/Renderer/res/shaders/default.frag", nullptr, "default");
	//ResourceManager::LoadShader("C:/dev/HANA/HANA/src/Renderer/res/shaders/default.vert", "C:/dev/HANA/HANA/src/Renderer/res/shaders/default.frag", nullptr, "default");
	const char* default_vert = "../HANA/src/Renderer/res/shaders/default.vert";
	const char* default_frag = "../HANA/src/Renderer/res/shaders/default.frag";
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

	//displayFPS(dt);

	//HA_TRACE(Player.GetPos().y);
	HA_TRACE(PipePairs[0].GetPos().x);


	if (Hana::Input::IsKeyPressed(HA_KEY_SPACE)) {
		// introduce cool down
 		Player.Jump(dt);
		//Player.SetPos(glm::vec2(Player.GetPos().x, Player.GetPos().y - 550.0f * dt));
	}

	if (Player.GetPos().y > floor)
		Player.SetPos(glm::vec3(Player.GetPos().x, floor, 0.1f));

	else
	{
		vy_cur = vy_prev + g * dt;
		y = y - vy_cur * dt;
		vy_prev = vy_cur;
	}

	if (Hana::Input::IsKeyPressed(HA_KEY_A)) {
		
		
		//loopingPoint -= 10.0f;
		HA_TRACE(loopingPoint);
	}
	cam_x -= (300.0f * dt);

	if (Hana::Input::IsKeyPressed(HA_KEY_D)) {
		//cam_x += 300.0f * dt;
		loopingPoint += 10.0f;
		HA_TRACE(loopingPoint);
	}

	if (Hana::Input::IsKeyPressed(HA_KEY_0)) {
		HA_TRACE("Key positions: ");

		HA_TRACE("Background 1 xy: ");
		HA_TRACE(cam_x);
		HA_TRACE(cam_y);
		HA_TRACE("Background 2 xy: ");
		HA_TRACE(cam_x);
		HA_TRACE(cam_y);

		HA_TRACE("Offset: ");
		HA_TRACE(cam_x - cam2_x);
		HA_TRACE(cam_y - cam2_y);

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


	// move pillars
	for (int i = 0; i < 5; i++) {
		glm::vec3 pos = PipePairs[i].GetPos();
		
		// if pillar beyond scope of view (move right to side of screen)
		if (pos.x < -200) {
			PipePairs[i].SetPos(glm::vec3(pos.x + 1080 + 200, pos.y, pos.z));
		}

		else {
			PipePairs[i].SetPos(glm::vec3(pos.x - ground_speed * dt, pos.y, pos.z));
		}
		float gap = PipePairs[i].GetGap();
	}

	Player.UpdatePos(dt);
}

void GameLayer::OnRender()
{
	//renderable->DrawTextureQuad2D(ResourceManager::GetTexture("scene_background"), glm::vec3(cam_x, cam_y, -0.5f), glm::vec2(1157 * 2.5 * multiplier, 228 * 3.5), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));

	renderable->DrawTextureQuad2D(ResourceManager::GetTexture("character"), Player.GetPos(), glm::vec2(10.0f * 20, 10.0f * 20), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));

	for (int i = 0; i < 5; i++) {
		glm::vec3 pos = PipePairs[i].GetPos();
		glm::vec2 size = PipePairs[i].GetSize();
		float gap = PipePairs[i].GetGap();
		renderable->DrawTextureQuad2D(ResourceManager::GetTexture("turdpipe"), pos + gap * glm::vec3(0.5f, 0.5f, 0.0f), size, 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
		//renderable->DrawTextureQuad2D(ResourceManager::GetTexture("turdpipe"), pos - gap * glm::vec2(0.5f, 0.5f) + glm::vec2(cam_x, cam_y), size, 180.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	}



}

void GameLayer::OnImGuiRender()
{
	//Renderable::DrawImGuiText("Trump Jump", 0, 50, 2.0f, 2);
}