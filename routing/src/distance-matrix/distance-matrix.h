#ifndef CITY_EVENT_ROUTER_DISTANCE_MATRIX_H
#define CITY_EVENT_ROUTER_DISTANCE_MATRIX_H

#include <iostream>


class DistanceMatrix
{
	public:
		explicit DistanceMatrix(size_t size);
		~DistanceMatrix();
		DistanceMatrix& Assign(size_t rov, size_t col, int value);
		DistanceMatrix& Clear();
		int* operator[](size_t index);
		const int* operator[](size_t index) const;
		const size_t Size() const;

	private:
		int** matrix;
		size_t size;
};


#endif //CITY_EVENT_ROUTER_DISTANCE_MATRIX_H
