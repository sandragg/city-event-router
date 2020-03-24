#ifndef ROUTING_WAYPOINT_H
#define ROUTING_WAYPOINT_H

#include "point.h"
#include "../timetable/event.h"


struct Waypoint
{
	int id;
	Point coords;
	timetable::Event schedule;
};


#endif //ROUTING_WAYPOINT_H
