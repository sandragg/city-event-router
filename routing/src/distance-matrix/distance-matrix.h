#ifndef CITY_EVENT_ROUTER_DISTANCE_MATRIX_H
#define CITY_EVENT_ROUTER_DISTANCE_MATRIX_H

#include <iostream>


/**
 * Stores distance between points.
 */
class DistanceMatrix
{
	public:
		/**
		 * Constructor with a defined matrix size.
		 * @param size Amount of points
		 */
		explicit DistanceMatrix(size_t size);
		~DistanceMatrix();
		/**
		 * Assign distance between two points.
		 * @param rov Row index (first point)
		 * @param col Column index (second point)
		 * @param value Distance
		 * @return Reference to the matrix.
		 */
		DistanceMatrix& Assign(size_t rov, size_t col, int value);
		/**
		 * Reset matrix.
		 * Sets all values to *0*.
		 *
		 * @return Reference to the matrix.
		 */
		DistanceMatrix& Clear();
		/**
		 * @overload
		 * @param index Row index (point)
		 * @return Pointer to the array of distances associated with a point.
		 */
		int* operator[](size_t index);
		/**
		 * @overload
		 * @param index Row index (point)
		 * @return Const pointer to the array of distances associated with a point.
		 */
		const int* operator[](size_t index) const;
		/**
		 * Get matrix size.
		 */
		size_t Size() const;

	private:
		int** matrix;
		size_t size;
};


#endif //CITY_EVENT_ROUTER_DISTANCE_MATRIX_H
