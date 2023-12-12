#pragma once


#include "../Hana/Core.h"

// GLM
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class HANA_API OrthographicCamera {

public:
	OrthographicCamera(float left = 1.0f, float right = -1.0f, float bottom = -1.0f, float top = 1.0f, float nearClip = -1.0f, float farClip = 1.0f);

	void SetPosition(const glm::vec3& position) {
		cameraPos = position; RecalculateViewMatrix();
	}

	void translateCamera(const glm::vec3& offset) { cameraPos += offset; RecalculateViewMatrix(); }
	// void rotateCamera();

	const glm::mat4& GetViewMatrix() const { return view; }
	const glm::mat4& GetProjectionMatrix() const { return projection; }


private:
	// MVP matrices
	glm::mat4 projection;
	glm::mat4 view;
	glm::vec3 cameraPos;

	float left, right, bottom, top, nearClip, farClip;

	void RecalculateViewMatrix() {
		view = glm::translate(glm::mat4(1.0f), -cameraPos);
	}
};