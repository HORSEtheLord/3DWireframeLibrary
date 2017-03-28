#pragma once
#include <array>
#include "Point3D.h"

class Matrix3D
{
private:
	std::array<float, 16> m_data;

public:
	Matrix3D();
	float& operator() (unsigned row, unsigned col)
	{
		return m_data[4 * row + col];
	}

	float operator() (unsigned row, unsigned col) const
	{
		return m_data[4 * row + col];
	}

	static Matrix3D CreateIdentity();
	static Matrix3D CreateTranslationMatrix(float dx, float dy, float dz);
	static Matrix3D CreateRotationXMatrix(float angle);
	static Matrix3D CreateRotationYMatrix(float angle);
	static Matrix3D CreateRotationZMatrix(float angle);
	static Matrix3D CreateScaleMatrix(float sx, float sy, float sz);
	static Matrix3D CreateProjectionMatrix(float d);

	friend Matrix3D operator+(const Matrix3D &lhs, const Matrix3D &rhs);
	friend Matrix3D operator*(const Matrix3D &lhs, const Matrix3D &rhs);
	friend Matrix3D operator*(const Matrix3D &lhs, float rhs);
	friend Matrix3D operator*(float lhs, const Matrix3D &rhs);
};

Point3D operator*(const Matrix3D &lhs, const Point3D &rhs);