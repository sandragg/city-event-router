#include "breadth-first-search.cpp"
#include "depth-first-search.cpp"

#include "../list-of-siblings/list-of-siblings.h"


template class tree::BfsIterator<list_of_siblings::Tree<int>>;
template class tree::DfsIterator<list_of_siblings::Tree<int>>;
