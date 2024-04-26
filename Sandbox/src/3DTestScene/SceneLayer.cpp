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
	ResourceManager::LoadShader(background_vert, background_frag, nullptr, "default");

	// configure shaders
	float window_width = 1080.0f;
	float window_height = 720.0f;
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(window_width),
		static_cast<float>(window_height), 0.0f, -1.0f, 1.0f);

	// load textures
	// ResourceManager::LoadTexture(Graphics::background, true, "scene_background");
	

	ResourceManager::GetShader("default").Use().SetInteger("image", 0);
	ResourceManager::GetShader("default").SetMatrix4("projection", projection);

	ResourceManager::GetShader("background").Use().SetInteger("image", 0);
	ResourceManager::GetShader("background").SetMatrix4("projection", projection);

	// set render-specific controls
	this->renderable = new Renderable(ResourceManager::GetShader("default"));
}

void SceneLayer::OnAttach() {}
void SceneLayer::OnDetach() {}

void SceneLayer::displayFPS(double dt) {
	timer += dt;
	if (timer > fixed_timestep) {
		HA_TRACE(fps);
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

	//displayFPS(dt);

}
void SceneLayer::OnRender()
{
	// render background - need to add mvp transforms
	// Renderable::DrawTextureQuad2D(-0.5f, -0.5f, 1.0f, 1.0f, path);
	// Renderable::DrawBackground();
	renderable->DrawCuboid(pos, dimen);
	renderable->DrawBackground(glm::vec3(1.0f,1.0f,0.0f));

}

void SceneLayer::OnImGuiRender()
{
	// Renderable::DrawImGuiText("Texture", 0, 50, 2.0f, 2);
}
