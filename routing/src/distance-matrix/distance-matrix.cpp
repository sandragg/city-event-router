#include "distance-matrix.h"


DistanceMatrix::DistanceMatrix(size_t size)
{
	this->size = size;
	matrix = new int*[size];

	for (size_t i = 0; i < size; i++)
	{
		matrix[i] = new int[size];
	}
	Clear();
}

DistanceMatrix::~DistanceMatrix()
{
	for (size_t i = 0; i < size; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}

int* DistanceMatrix::operator[](size_t index)
{
	return matrix[index];
}

const int* DistanceMatrix::operator[](size_t index) const
{
	return matrix[index];
}

DistanceMatrix& DistanceMatrix::Assign(size_t row, size_t col, int value)
{
	matrix[row][col] = value;

	if (row != col)
		matrix[col][row] = value;

	return *this;
}

DistanceMatrix& DistanceMatrix::Clear()
{
	for (size_t i = 0; i < size; i++)
		for (size_t j = 0; j < size; j++)
			matrix[i][j] = 0;

	return *this;
}

const size_t DistanceMatrix::Size() const
{
	return size;
}
