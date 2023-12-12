#pragma once

#pragma once

#include "Hana.h"
#include "Hana/Time.h"
#include "Hana/Input.h"
#include "Hana/KeyCodes.h"
#include "Hana/MouseButtonCodes.h"
#include "Hana/StateMachine.h"

class SceneLayer : public Hana::Layer
{
public:
	SceneLayer();
	virtual ~SceneLayer() override;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnRender() override;
	virtual void OnUpdate() override;
	virtual void OnImGuiRender() override;

	void displayFPS(double dt);

private:
	const char* path = "A:/dev/Hana/HANA/HANA/src/Renderer/res/textures/Logo.png";
	double cur_t = 0.0;
	double fps = 0.0;
	double prev_t = 0.0;
	double fixed_timestep = 0.5;
	double dt = 0.0;
	double timer = 0.0;

	Hana::Application appInstance;

};