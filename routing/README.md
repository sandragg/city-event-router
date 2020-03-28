\mainpage

## Introduction
Routing is a program for computing all possible routes based a on set of way points
and custom preferences.
 
Route priorities:
 1. More visited way points;
 2. Less time spent;
 3. Less time for moving/driving.


## Custom Preferences

Routing provides the ability to customise search result.
Parameters marked with an asterisk are required.
                         
 Parameter  | Type      | Default   | Description
------------|-----------|-----------|-------------
 points*    | Waypoint[]|           | Points to be visited.
 distance_matrix* | number[][]|     | Distance matrix stores the time required for moving between each pair of points in the *points*.
 settings   | CustomSettings | null | Custom preferences.
 settings.min_stay_time | number | 1| Minimal time to spend at a point.
 settings.late_fee | number | 1     | Penalty coefficient for being late to a point.
 settings.time_before_open_fee | number | 1 | Penalty coefficient for being at a point before it's opened.
 settings.extra_time_fee | number |1| Fee coefficient for spending more than *min_stay_time* at a point.
 settings.points_priorities | PriorityPoint[] | null | Priority for each point in the *points*.
 settings.time_range | timetable::Interval | null | Time range limitation for route.

 
