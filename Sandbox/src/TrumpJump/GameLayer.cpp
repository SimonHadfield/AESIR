#include "GameLayer.h"

// GameLayer
GameLayer::GameLayer() {
HA_TRACE(x);
HA_TRACE(y);
HA_TRACE(width);
HA_TRACE(height);
}
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
	//HA_TRACE(y);

	if (y <= 0.0f) {
		y = 0.0f;
		g = 0.0f;
		vy_cur = 0.0f;
		vy_prev = 0.0f;
	}
	else {
		g = 200.0f;
	}

	if (Hana::Input::IsKeyPressed(HA_KEY_SPACE)) {
		vy_cur = vy_prev + g * dt - force_y * dt;
		y = y - vy_cur * dt;
		vy_prev = vy_cur;
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

	if (Hana::Input::IsKeyPressed(HA_KEY_SPACE)) {
		HA_TRACE(cam2_x);
	}

	if (cam2_x < -1700.0f - 1157) {
		cam2_x = 1700.0f + 1157;
	}
	if (cam3_x < -1700.0f - 1157) {
		cam3_x = 1700.0f + 1157;
	}

	cam2_x -= 100.0f * dt;
	cam3_x -= 100.0f * dt;

}

void GameLayer::OnRender()
{
	
	// render background - need to add mvp transforms
	//Renderable::DrawTextureQuad2D(x, y, width, height, path);
	Renderable::DrawBackground();
	Renderable::DrawTextureQuad2D(cam2_x , cam_y, 1157*2.5 * multiplier, 228*3.5, Graphics::background); // background clouds 1
	Renderable::DrawTextureQuad2D(cam3_x, cam_y, 1157*2.5 * multiplier, 228*3.5, Graphics::background); // background clouds 2
	Renderable::DrawTextureQuad2D(cam_x, cam_y, 1157*2.5 * multiplier, 228*3.5 * 0.5, Graphics::background, 1.0f, 0.5f); // background toilets
	Renderable::DrawTextureQuad2D(0, 90, 1100*2, 16*3, Graphics::ground); // ground


	Renderable::DrawTextureQuad2D(cam2_x + 1000, -100, 70*2, 288*2, Graphics::turdpipe); // turdpipe



}

void GameLayer::OnImGuiRender()
{
	//Renderable::DrawImGuiText("Trump Jump", 0, 50, 2.0f, 2);
}