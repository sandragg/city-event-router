#ifndef ROUTING_TIMETABLE_H
#define ROUTING_TIMETABLE_H


namespace timetable
{

struct Interval
{
	time_t start;
	time_t end;

	bool operator==(const Interval& rhs)
	{
		return this->start == rhs.start
			   && this->end == rhs.end;
	}
};

template<class _Tp>
class Timetable
{
	public:
		virtual void AddInterval(const Interval &interval) = 0;

		virtual void RemoveInterval(const Interval &interval) = 0;

		virtual _Tp GetInInterval(const Interval &interval) const = 0;

		const _Tp& GetAll() const { return schedule; }

	protected:
		_Tp schedule;
};

} // namespace timetable


#endif //ROUTING_TIMETABLE_H
