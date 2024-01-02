#include "SceneLayer.h"

// SceneLayer

SceneLayer::SceneLayer() {}
SceneLayer::~SceneLayer() {}
void SceneLayer::OnAttach() {}
void SceneLayer::OnDetach() {}

void SceneLayer::init() {
	// load shaders
	//A:/dev/Hana/HANA/HANA/src/Renderer/res/shaders/background.vert", "A:/dev/Hana/HANA/HANA/src/Renderer/res/shaders/background.frag
	//ResourceManager::LoadShader("A:/dev/Hana/HANA/HANA/src/Renderer/res/shaders/background.vert", "A:/dev/Hana/HANA/HANA/src/Renderer/res/shaders//background.frag", /nullptr, "sprite");
	//// configure shaders
	//glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
	//	static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
	//ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	//ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	//// set render-specific controls
	//renderable = new Renderable(ResourceManager::GetShader("sprite"));
}

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
	cur_t = Hana::Time::GetTime();
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
	//renderable->DrawBackground();

}

void SceneLayer::OnImGuiRender()
{
	// Renderable::DrawImGuiText("Texture", 0, 50, 2.0f, 2);
}