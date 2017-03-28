#pragma once
#include <vector>
#include "Object3D.h"
#include <memory>

class Scene
{
private:
	std::vector<std::shared_ptr<Object3D>> m_objects;
	Matrix3D m_viewMatrix;
	Matrix3D m_projectionMatrix;

public:
	Scene();

	void Draw(const Graphics &graphics) const;

	void TransformViewMatrix(const Matrix3D &matrix);
};
