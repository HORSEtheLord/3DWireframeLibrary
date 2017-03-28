#define _USE_MATH_DEFINES
#include<cmath>

#include "Torus.h"

void Torus::GenerateTorus()
{
	float stepAlpha = M_PI * 2 / m_outerDensity;
	float stepBeta = M_PI * 2 / m_innerDensity;

	for (float a = 0; a < M_PI * 2 - stepAlpha / 2; a += stepAlpha)
		for (float b = 0; b < M_PI * 2 - stepBeta / 2; b += stepBeta)
		{
			m_points.emplace_back(
				(m_outerRadius + m_innerRadius * cos(b)) * cos(a),
				(m_outerRadius + m_innerRadius * cos(b)) * sin(a),
				m_innerRadius * sin(b));
		}

	for (int i = 0; i < m_outerDensity; ++i)
		for (int j = 0; j < m_innerDensity; ++j)
		{
			m_edges.emplace_back(i * m_innerDensity + j, i * m_innerDensity + (j + 1) % m_innerDensity);
			m_edges.emplace_back(i*m_innerDensity + j, ((i + 1) % m_outerDensity)*m_innerDensity + j);
		}
}

Torus::Torus(float positionX,
	float positionY,
	float positionZ,
	unsigned innerRadius,
	unsigned outerRadius,
	unsigned innerDensity,
	unsigned outerDensity)
	: Object3D(positionX, positionY, positionZ),
	m_innerRadius(innerRadius),
	m_outerRadius(outerRadius),
	m_innerDensity(innerDensity),
	m_outerDensity(outerDensity)
{
	GenerateTorus();
}
