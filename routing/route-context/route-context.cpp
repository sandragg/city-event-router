#include "route-context.h"
using namespace route_context;


void RouteContext::UpdateOnNewTick(time_t now)
{
	upcoming = lower_bound(upcoming, time_priorities.end(), now);
}
