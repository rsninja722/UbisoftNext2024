#ifndef NEXT2024_SRC_ENGINE_RENDER_RENDER_H_
#define NEXT2024_SRC_ENGINE_RENDER_RENDER_H_

# define M_PI 3.14159265358979323846

#include "Mesh.h"
#include "engine/math/Vec3.h"
#include "engine/math/Mat4.h"

class Render {
public:
	static const int SCREEN_WIDTH = 1024;
	static const int SCREEN_HEIGHT = 768;

	static Mesh* m_city;
	static Mesh* m_rocket;
	static Mesh* m_shield;
	static Mesh* m_base;
	static Mesh* m_terrain;
	static Mesh* m_plane;
	static Mesh* m_target;

	Render();

	static void Init();

	static void SetCameraPos(const Vec3& pos);

	static void SetCameraTarget(const Vec3& target);

	static void UpdateCameraPos(const Vec3& pos);

	static void RenderFirstStep();

	static void RenderMesh(Mesh* mesh, Color color, Vec3 translate = { 0.0f, 0.0f, 0.0f }, Vec3 scale = { 1.0f, 1.0f, 1.0f }, Vec3 rotation = { 0.0f, 0.0f, 0.0f });

	static void RenderFinalStep();

	static void UnloadMeshes();

private:
	static float m_fov;
	static float m_near;
	static float m_far;
	static float m_aspectRatio;

	static Vec3 m_camEye;
	static Vec3 m_camTarget;
	static Vec3 m_camUp;
	static Mat4 m_worldMatrix;
	static Mat4 m_viewMatrix;
	static Mat4 m_projectionMatrix;

	static std::vector<std::pair<Triangle, Color>> m_drawBuffer;

};

#endif // NEXT2024_SRC_ENGINE_RENDER_RENDER_H_
