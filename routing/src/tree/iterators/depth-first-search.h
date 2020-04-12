#ifndef ROUTING_DEPTH_FIRST_SEARCH_H
#define ROUTING_DEPTH_FIRST_SEARCH_H

#include<stack>
#include "../tree.h"


namespace tree
{

/**
 * Depth First Search iterator.
 */
template<class _Container>
class DfsIterator
{
		using container	= Tree<
		    typename _Container::iterator,
		    typename _Container::const_iterator>;
		using iterator	= typename container::iterator;
		using reference	= typename iterator::reference;

	public:
		explicit DfsIterator(const container &tree);
		DfsIterator& operator++();
		reference operator*();
		bool IsEnd() const;

	private:
		container *tree;
		std::stack<iterator> stack;

		void traceIteration(const container &container, std::stack<iterator> &trace_stack);
};

#include "depth-first-search.cpp"

} // namespace tree


#endif //ROUTING_DEPTH_FIRST_SEARCH_H
