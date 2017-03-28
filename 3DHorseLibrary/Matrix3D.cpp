#include<cmath>

#include "Matrix3D.h"

Matrix3D operator+(const Matrix3D &lhs, const Matrix3D &rhs)
{
	Matrix3D result;

	for (unsigned i = 0; i < 16; ++i)
		result.m_data[i] = lhs.m_data[i] + rhs.m_data[i];

	return result;
}

Matrix3D operator*(const Matrix3D &lhs, const Matrix3D &rhs)
{
	Matrix3D result;

	for (unsigned i = 0; i < 4; ++i)
		for (unsigned j = 0; j < 4; ++j)
			for (unsigned k = 0; k < 4; ++k)
				result(i, j) += lhs(i, k) * rhs(k, j);

	return result;
}

Matrix3D operator*(const Matrix3D &lhs, float rhs)
{
	Matrix3D result;

	for (unsigned i = 0; i < 16; ++i)
		result.m_data[i] = lhs.m_data[i] * rhs;

	return result;
}

Matrix3D operator*(float lhs, const Matrix3D &rhs)
{
	return rhs * lhs;
}

Matrix3D::Matrix3D()
{
	m_data.fill(0);
}

Matrix3D Matrix3D::CreateIdentity()
{
	Matrix3D matrix;

	matrix(0, 0) = 1;
	matrix(1, 1) = 1;
	matrix(2, 2) = 1;
	matrix(3, 3) = 1;

	return matrix;
}

Matrix3D Matrix3D::CreateTranslationMatrix(float dx, float dy, float dz)
{
	Matrix3D matrix = CreateIdentity();

	matrix(0, 3) = dx;
	matrix(1, 3) = dy;
	matrix(2, 3) = dz;

	return matrix;
}

Matrix3D Matrix3D::CreateRotationXMatrix(float angle)
{
	Matrix3D matrix = CreateIdentity();

	matrix(1, 1) = cos(angle);
	matrix(1, 2) = -sin(angle);
	matrix(2, 1) = sin(angle);
	matrix(2, 2) = cos(angle);

	return matrix;
}

Matrix3D Matrix3D::CreateRotationYMatrix(float angle)
{
	Matrix3D matrix = CreateIdentity();

	matrix(0, 0) = cos(angle);
	matrix(0, 2) = sin(angle);
	matrix(2, 0) = -sin(angle);
	matrix(2, 2) = cos(angle);

	return matrix;
}

Matrix3D Matrix3D::CreateRotationZMatrix(float angle)
{
	Matrix3D matrix = CreateIdentity();

	matrix(0, 0) = cos(angle);
	matrix(0, 1) = -sin(angle);
	matrix(1, 0) = sin(angle);
	matrix(1, 1) = cos(angle);

	return matrix;
}

Matrix3D Matrix3D::CreateScaleMatrix(float sx, float sy, float sz)
{
	Matrix3D matrix = CreateIdentity();

	matrix(0, 0) = sx;
	matrix(1, 1) = sy;
	matrix(2, 2) = sz;

	return matrix;
}

Matrix3D Matrix3D::CreateProjectionMatrix(float d)
{
	Matrix3D matrix = CreateIdentity();

	matrix(3, 2) = 1 / d;

	return matrix;
}

Point3D operator*(const Matrix3D &lhs, const Point3D &rhs)
{
	Point3D result(0, 0, 0);

	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			result[i] += lhs(i, j) * rhs[j];

	result.Normalize();

	return result;
}
