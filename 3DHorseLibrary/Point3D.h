#pragma once
#include <array>

class Point3D
{
private:
	std::array<float, 4> m_data;

public:
	Point3D(float x, float y, float z);

	float operator[] (unsigned index) const
	{
		return m_data[index];
	}

	float& operator[] (unsigned index)
	{
		return m_data[index];
	}

	float GetX() const { return m_data[0]; }
	float GetY() const { return m_data[1]; }
	float GetZ() const { return m_data[2]; }
	float GetW() const { return m_data[3]; }

	void Normalize();
};
