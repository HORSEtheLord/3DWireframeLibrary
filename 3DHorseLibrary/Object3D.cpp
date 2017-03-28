#include "Object3D.h"
#include "Utils.h"

Object3D::Object3D(float positionX, float positionY, float positionZ)
	: m_worldMatrix(Matrix3D::CreateTranslationMatrix(positionX, positionY, positionZ))
{
}

void Object3D::Draw(const Graphics &graphics, const Matrix3D &viewMatrix, const Matrix3D &projectionMatrix) const
{
	std::vector<Point3D> points;
	points.reserve(m_points.size());

	Matrix3D viewWorldMatrix = viewMatrix * m_worldMatrix;

	for (const Point3D &point : m_points)
	{
		Point3D p = viewWorldMatrix * point;
		points.push_back(std::move(p));
	}

	for (const Edge &edge : m_edges)
	{
		Point3D &p1 = points[edge.GetIndex1()];
		Point3D &p2 = points[edge.GetIndex2()];

		if (p1.GetZ() > PROJECTION_DISTANCE && p2.GetZ() > PROJECTION_DISTANCE)
			continue;

		if (p1.GetZ() > PROJECTION_DISTANCE)
		{
			float l = (PROJECTION_DISTANCE - p2.GetZ()) / (float)(p1.GetZ() - p2.GetZ());
			Point3D pd(
				p2.GetX() + l * (p1.GetX() - p2.GetX()),
				p2.GetY() + l * (p1.GetY() - p2.GetY()),
				PROJECTION_DISTANCE);

			Point3D point1 = projectionMatrix * pd;
			Point3D point2 = projectionMatrix * p2;
			graphics.DrawLine(point1.GetX(), point1.GetY(), point2.GetX(), point2.GetY());
		}
		else if (p2.GetZ() > PROJECTION_DISTANCE)
		{
			float l = (PROJECTION_DISTANCE - p1.GetZ()) / (float)(p2.GetZ() - p1.GetZ());
			Point3D pd(
				p1.GetX() + l * (p2.GetX() - p1.GetX()),
				p1.GetY() + l * (p2.GetY() - p1.GetY()),
				PROJECTION_DISTANCE);

			Point3D point1 = projectionMatrix * p1;
			Point3D point2 = projectionMatrix * pd;
			graphics.DrawLine(point1.GetX(), point1.GetY(), point2.GetX(), point2.GetY());
		}
		else
		{
			Point3D point1 = projectionMatrix * p1;
			Point3D point2 = projectionMatrix * p2;
			graphics.DrawLine(point1.GetX(), point1.GetY(), point2.GetX(), point2.GetY());
		}
	}
}
