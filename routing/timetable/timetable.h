#ifndef ROUTING_TIMETABLE_H
#define ROUTING_TIMETABLE_H


namespace timetable
{

struct Interval
{
	Interval(time_t s, time_t e): start(s), end(e) {}

	bool operator==(const Interval& rhs)
	{
		return this->start == rhs.start
			   && this->end == rhs.end;
	}

	time_t start;
	time_t end;
};

template<class _Tp>
class Timetable
{
	public:
		virtual void AddInterval(const Interval &interval) = 0;

		virtual void RemoveInterval(const Interval &interval) = 0;

		virtual _Tp GetInInterval(const Interval &interval, bool strict) const = 0;

		virtual _Tp GetAll() const = 0;
};

} // namespace timetable


#endif //ROUTING_TIMETABLE_H
