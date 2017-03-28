#include "Scene.h"
#include "Utils.h"
#include "Torus.h"

Scene::Scene()
	: m_viewMatrix(Matrix3D::CreateIdentity()),
	m_projectionMatrix(Matrix3D::CreateProjectionMatrix(-PROJECTION_DISTANCE))
{
	m_objects.push_back(std::make_shared<Torus>(0, 0, 0, 45, 100, 30, 30));
}

void Scene::Draw(const Graphics& graphics) const
{
	for(std::shared_ptr<Object3D> object : m_objects)
	{
		object->Draw(graphics, m_viewMatrix, m_projectionMatrix);
	}
}

void Scene::TransformViewMatrix(const Matrix3D& matrix)
{
	m_viewMatrix = matrix * m_viewMatrix;
}
