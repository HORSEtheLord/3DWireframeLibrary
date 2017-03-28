#pragma once
#include <vector>
#include "Edge.h"
#include "Graphics.h"
#include "Matrix3D.h"
#include "Point3D.h"

class Object3D
{
protected:
	std::vector<Point3D> m_points;
	std::vector<Edge> m_edges;
	Matrix3D m_worldMatrix;

	Object3D(float positionX, float positionY, float positionZ);
public:
	void Draw(const Graphics &graphics, const Matrix3D &viewMatrix, const Matrix3D &projectionMatrix) const;
};
