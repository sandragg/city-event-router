#ifndef ROUTING_PRIORITY_POINT_H
#define ROUTING_PRIORITY_POINT_H


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
