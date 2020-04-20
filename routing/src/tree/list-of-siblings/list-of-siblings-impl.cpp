#include "list-of-siblings.cpp"
#include "base-iterator.cpp"
#include "base-const-iterator.cpp"

#include "../../tracer/tracer.h"


template class list_of_siblings::Tree<tracer::RoutePoint>;
template class list_of_siblings::TreeIterator<tracer::RoutePoint>;
template class list_of_siblings::ConstTreeIterator<tracer::RoutePoint>;
