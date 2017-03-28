#include "Point3D.h"

Point3D::Point3D(float x, float y, float z)
	: m_data{ x,y,z,1 }
{
}

void Point3D::Normalize()
{
	if (m_data[3] != 0)
	{
		m_data[0] /= m_data[3];
		m_data[1] /= m_data[3];
		m_data[2] /= m_data[3];
		m_data[3] = 1;
	}
}