#ifndef NEXT2024_SRC_ENGINE_RENDER_RENDER_H_
#define NEXT2024_SRC_ENGINE_RENDER_RENDER_H_

#include "engine/math/Vec3.h"
#include "engine/math/Mat4.h"

class Render {
public:
	const int SCREEN_WIDTH = 1024;
	const int SCREEN_HEIGHT = 768;

	Render();

	void Init();

	void SetCameraPos(const Vec3& pos);

	void SetCameraTarget(const Vec3& target);

	void RenderAll();

private:
	float m_fov = 90.0f;
	float m_near = 0.1f;
	float m_far = 1000.0f;
	float m_aspectRatio = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;

	Vec3 m_camEye;
	Vec3 m_camTarget;
	Vec3 m_camUp;
	Mat4 m_worldMatrix;
	Mat4 m_viewMatrix;
	Mat4 m_projectionMatrix;
	Mat4 m_modelMatrix;

	void UpdateModel();
};


#endif // NEXT2024_SRC_ENGINE_RENDER_RENDER_H_
