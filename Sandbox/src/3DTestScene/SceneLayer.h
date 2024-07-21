#pragma once

#include "Aesir.h"
#include "Aesir/Time.h"
#include "Aesir/Input.h"
#include "Aesir/KeyCodes.h"
#include "Aesir/MouseButtonCodes.h"
#include "Aesir/StateMachine.h"

// GLM
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class SceneLayer : public Aesir::Layer
{
public:
	SceneLayer();
	virtual ~SceneLayer() override ;

	void LoadResources();
	
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnRender() override;
	virtual void OnUpdate() override;
	virtual void OnImGuiRender() override {};

	void displayFPS(double dt);

private:
	Renderable *renderable_cube;
	Renderable *renderable_background;
	Renderable *renderable_texture;
	float Width = 1080.0f;
	float Height = 720.0f;

	const char* Logo_path = "A:/dev/Aesir/Aesir/Aesir/src/Renderer/res/textures/Logo.png";
	double cur_t = 0.0;
	double fps = 0.0;
	double prev_t = 0.0;
	double fixed_timestep = 0.5;
	double dt = 0.0;
	double timer = 0.0;

	glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 dimen = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);


	Aesir::Application appInstance;

};