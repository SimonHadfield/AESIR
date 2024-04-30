#include "OrthographicCamera.h"

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float nearClip, float farClip)
: projection(glm::ortho(left, right, bottom, top, nearClip, farClip)), view(1.0f) 
{
	RecalculateViewMatrix();
}
