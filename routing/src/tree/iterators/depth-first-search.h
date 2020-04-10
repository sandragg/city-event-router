#ifndef ROUTING_DEPTH_FIRST_SEARCH_H
#define ROUTING_DEPTH_FIRST_SEARCH_H

#include "../tree.h"


namespace tree
{

using namespace tree;

/**
 * Depth First Search iterator.
 */
template<class _Container>
class DfsIterator
{
	private:
		using container	= Tree<
		    typename _Container::iterator,
		    typename _Container::const_iterator>;
		using iterator	= typename container::iterator;
		using reference	= typename iterator::reference;

	public:
		explicit DfsIterator(const container &tree);
		DfsIterator& operator++();
		reference operator*();

	private:
		container *tree;
		iterator position;
};

#include "depth-first-search.cpp"

} // namespace tree


#endif //ROUTING_DEPTH_FIRST_SEARCH_H
