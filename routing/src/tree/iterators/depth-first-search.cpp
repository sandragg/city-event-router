#include "depth-first-search.h"


template<class _Container>
DfsIterator<_Container>::DfsIterator(const container& tree)
{
	this->tree = &tree;
	position = tree.Root();
}

template<class _Container>
typename DfsIterator<_Container>::reference
DfsIterator<_Container>::operator*()
{
	return *position;
}

template<class _Container>
DfsIterator<_Container>& DfsIterator<_Container>::operator++()
{
	// logic for dfc. save stack in a private property

	return *this;
}
