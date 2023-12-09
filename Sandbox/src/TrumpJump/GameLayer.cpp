#include "GameLayer.h"

// GameLayer
GameLayer::GameLayer() {}
GameLayer::~GameLayer() {}
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

}
void GameLayer::OnRender()
{
	// render background - need to add mvp transforms
	Renderable::DrawTextureQuad2D(-0.5f, -0.5f, 1.0f, 1.0f, path);
	Renderable::DrawBackground();

}

void GameLayer::OnImGuiRender()
{
	Renderable::DrawImGuiText("Texture", 0, 50, 2.0f, 2);
}