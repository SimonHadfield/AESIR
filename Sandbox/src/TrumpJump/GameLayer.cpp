#include "GameLayer.h"
#include "glad/glad.h"


// character jump
void Character::Jump(double dt) {
	dy = - Jump_force * dt;
	PlayerPos.y += dy * dt;
	//PlayerPos.y = 0.0f;
	//dy = 0;
}

void Character::UpdatePos(double dt) {
	if (PlayerPos.y < 720.0f - 300) {
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
	PipePairs[i].SetPos(glm::vec2( 0.0f + i * 200.0f, 300.0f));
	PipePairs[i].SetSize(glm::vec2( 70.0f * 2, 288.0f * 2));
	PipePairs[i].SetGap(200.0f);

}

Player.SetPos(glm::vec2(300.0f, 0.0f));
}

GameLayer::~GameLayer() {
	delete renderable;
}

void GameLayer::LoadResources() {
	// load shaders
	//ResourceManager::LoadShader("A:/dev/Hana/HANA/HANA/src/Renderer/res/shaders/background.vert", "A:/dev/Hana/HANA/HANA/src/Renderer/res/shaders/background.frag", nullptr, "background");
	ResourceManager::LoadShader("A:/dev/Hana/HANA/HANA/src/Renderer/res/shaders/default.vert", "A:/dev/Hana/HANA/HANA/src/Renderer/res/shaders/default.frag", nullptr, "default");
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
	//this->renderable = new Renderable(ResourceManager::GetShader("background"));
	this->renderable = new Renderable(ResourceManager::GetShader("default"));
	//this->renderable = new Renderable(ResourceManager::GetShader("turdpipe"));

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


	//Player.SetPos(glm::vec2(Player.GetPos().x, Player.GetPos().y + 100.0f * dt));

	HA_TRACE(Player.GetPos().y);


	if (Hana::Input::IsKeyPressed(HA_KEY_SPACE)) {
		// introduce cool down
 		Player.Jump(dt);
		//Player.SetPos(glm::vec2(Player.GetPos().x, Player.GetPos().y - 550.0f * dt));
	}


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
		glm::vec2 pos = PipePairs[i].GetPos();
		glm::vec2 size = PipePairs[i].GetSize();
		float gap = PipePairs[i].GetGap();
		if (pos.x < 0) {
			PipePairs[i].SetPos( glm::vec2(PipePairs[i].GetPos().x + 1080, PipePairs[i].GetPos().y ) );
		}
	}

	Player.UpdatePos(dt);
}

void GameLayer::OnRender()
{

	renderable->DrawTextureQuad2D(ResourceManager::GetTexture("scene_background"), glm::vec2(cam_x, cam_y), glm::vec2(1157 * 2.5 * multiplier, 228 * 3.5), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	renderable->DrawTextureQuad2D(ResourceManager::GetTexture("character"), Player.GetPos(), glm::vec2(10.0f * 20, 10.0f * 20), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));

	for (int i = 0; i < 5; i++) {
		glm::vec2 pos = PipePairs[i].GetPos();
		glm::vec2 size = PipePairs[i].GetSize();
		float gap = PipePairs[i].GetGap();
		renderable->DrawTextureQuad2D(ResourceManager::GetTexture("turdpipe"), pos + gap * glm::vec2(0.5f, 0.5f) + glm::vec2(cam_x, cam_y), size, 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
		//renderable->DrawTextureQuad2D(ResourceManager::GetTexture("turdpipe"), pos - gap * glm::vec2(0.5f, 0.5f) + glm::vec2(cam_x, cam_y), size, 180.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	}



}

void GameLayer::OnImGuiRender()
{
	//Renderable::DrawImGuiText("Trump Jump", 0, 50, 2.0f, 2);
}