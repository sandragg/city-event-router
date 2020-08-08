#include "list-of-siblings.cpp"
#include "base-iterator.cpp"
#include "base-const-iterator.cpp"

#include "../../tracer/tracer.h"


template class list_of_siblings::Tree<int>;
template class list_of_siblings::TreeIterator<int>;
template class list_of_siblings::ConstTreeIterator<int>;

template class list_of_siblings::Tree<std::string>;
template class list_of_siblings::TreeIterator<std::string>;
template class list_of_siblings::ConstTreeIterator<std::string>;

template class list_of_siblings::Tree<tracer::RoutePoint<int>>;
template class list_of_siblings::TreeIterator<tracer::RoutePoint<int>>;
template class list_of_siblings::ConstTreeIterator<tracer::RoutePoint<int>>;
