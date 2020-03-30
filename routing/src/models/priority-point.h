#ifndef ROUTING_PRIORITY_POINT_H
#define ROUTING_PRIORITY_POINT_H


/**
 * Point with priority.
 * Useful when it's required to store points sorted by priority
 * and get id of the first.
 *
 * @tparam _Tp Priority type
 */
template<class _Tp>
struct PriorityPoint
{
	int id;
	_Tp priority;

	bool operator>(const PriorityPoint<_Tp>& rhs)
	{
		return this->priority > rhs.priority;
	}
};


#endif //ROUTING_PRIORITY_POINT_H
