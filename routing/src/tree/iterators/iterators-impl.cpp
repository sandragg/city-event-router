#include "breadth-first-search.cpp"
#include "depth-first-search.cpp"

#include "../../tracer/tracer.h"
#include "../list-of-siblings/list-of-siblings.h"


template class tree::BfsIterator<list_of_siblings::Tree<tracer::RoutePoint>>;
template class tree::DfsIterator<list_of_siblings::Tree<tracer::RoutePoint>>;
