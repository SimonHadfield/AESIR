#include "SceneLayer.h"

// SceneLayer

SceneLayer::SceneLayer() {}
SceneLayer::~SceneLayer() {}

void SceneLayer::LoadResources() {
	// load shaders
	const char* default_vert = "../Aesir/src/Renderer/res/shaders/default.vert";
	const char* default_frag = "../Aesir/src/Renderer/res/shaders/default.frag";
	ResourceManager::LoadShader(default_vert, default_frag, nullptr, "default");

	const char* background_vert = "../Aesir/src/Renderer/res/shaders/background.vert";
	const char* background_frag = "../Aesir/src/Renderer/res/shaders/background.frag"; 
	ResourceManager::LoadShader(background_vert, background_frag, nullptr, "background");

	const char* texture_vert = "../Aesir/src/Renderer/res/shaders/texture.vert";
	const char* texture_frag = "../Aesir/src/Renderer/res/shaders/texture.frag";
	ResourceManager::LoadShader(texture_vert, texture_frag, nullptr, "texture");

	// configure shaders
	float window_width = 1080.0f;
	float window_height = 720.0f;
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(window_width),
		static_cast<float>(window_height), 0.0f, -1.0f, 1.0f);

	// load textures
	ResourceManager::LoadTexture(Logo_path, false, "Logo");
	//ResourceManager::LoadTexture(Graphics::background, true, "scene_background");
	

	ResourceManager::GetShader("default").Use().SetInteger("image", 0);
	ResourceManager::GetShader("default").SetMatrix4("projection", projection);

	//ResourceManager::GetShader("background").Use().SetInteger("image", 0);
	//ResourceManager::GetShader("background").SetMatrix4("projection", projection);

	//ResourceManager::GetShader("texture").Use().SetInteger("image", 0); 
	//ResourceManager::GetShader("texture").SetMatrix4("projection", projection);
	// set render-specific controls
	this->renderable_cube = new Renderable(ResourceManager::GetShader("default"));
	//this->renderable_background = new Renderable(ResourceManager::GetShader("background"));
	//this->renderable_texture = new Renderable(ResourceManager::GetShader("texture"));
}

void SceneLayer::OnAttach() {}
void SceneLayer::OnDetach() {}

void SceneLayer::displayFPS(double dt) {
	timer += dt;
	if (timer > fixed_timestep) {
		AE_TRACE(fps);
		timer = 0;
	}
}
void SceneLayer::OnUpdate()
{
	// update timer
	cur_t = Aesir::Time::GetTime();
	dt = cur_t - prev_t;
	prev_t = cur_t;
	fps = 1 / dt;

	float movement_speed = 0.1;
	float scale_speed = 0.1;

	if (Aesir::Input::IsKeyPressed(AE_KEY_LEFT_SHIFT)) {
		scale_speed = 0.01;
		movement_speed = 0.01;
	}

	if (Aesir::Input::IsKeyPressed(AE_KEY_W)) {
		pos.y += movement_speed * 1;
	}
	if (Aesir::Input::IsKeyPressed(AE_KEY_S)) {
		pos.y -= movement_speed * 1;
	}
	if (Aesir::Input::IsKeyPressed(AE_KEY_A)) {
		pos.x -= movement_speed * 1;
	}
	if (Aesir::Input::IsKeyPressed(AE_KEY_D)) {
		pos.x += movement_speed * 1;
	}

	if (Aesir::Input::IsKeyPressed(AE_KEY_Q)) {
		pos.z -= movement_speed * 1;
	}
	if (Aesir::Input::IsKeyPressed(AE_KEY_E)) {
		pos.z += movement_speed * 1;
	}

	// rotate 
	if (Aesir::Input::IsKeyPressed(AE_KEY_K)) {
		rotation.x += 1;
	}
	if (Aesir::Input::IsKeyPressed(AE_KEY_L)) {
		rotation.x -= 1;
	}

	if (Aesir::Input::IsKeyPressed(AE_KEY_I)) {
		rotation.z += 1;
	}
	if (Aesir::Input::IsKeyPressed(AE_KEY_O)) {
		rotation.z -= 1;
	}

	if (Aesir::Input::IsKeyPressed(AE_KEY_V)) {
		dimen.x += 1 * scale_speed;
		dimen.y += 1 * scale_speed;
		dimen.z += 1 * scale_speed;
	}
	if (Aesir::Input::IsKeyPressed(AE_KEY_B)) {
		dimen.x -= 1 * scale_speed;
		dimen.y -= 1 * scale_speed;
		dimen.z -= 1 * scale_speed;
	}

	
	//displayFPS(dt);

}
void SceneLayer::OnRender()
{
	// render background - need to add mvp transforms
	// Renderable::DrawTextureQuad2D(-0.5f, -0.5f, 1.0f, 1.0f, path);
	// Renderable::DrawBackground();
	//renderable_background->DrawBackground(glm::vec3(1.0f,1.0f,-1.0f));
	renderable_cube->DrawCuboid(pos, dimen, rotation, ResourceManager::GetTexture("Logo"));
	//renderable_texture->DrawTextureQuad2D(ResourceManager::GetTexture("Logo"), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(10.0f, 10.0f), 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));

	//AE_TRACE("pos.x: ");
	//AE_TRACE(dimen.x);
	//AE_TRACE("pos.y: ");
	//AE_TRACE(dimen.y);

}

//void SceneLayer::OnImGuiRender()
//{
	// Renderable::DrawImGuiText("Texture", 0, 50, 2.0f, 2);
//ssssssssssssssssssssssssssssssssdfdcxdcvxcdfcccdcxddds}
