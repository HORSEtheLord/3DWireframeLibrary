#pragma once
#include "Object3D.h"

class Torus : public Object3D
{
private:
	unsigned m_innerRadius;
	unsigned m_outerRadius;
	unsigned m_innerDensity;
	unsigned m_outerDensity;

	void GenerateTorus();
public:
	Torus(float positionX,
		float positionY,
		float positionZ,
		unsigned innerRadius, 
		unsigned outerRadius, 
		unsigned innerDensity, 
		unsigned outerDensity);
};
