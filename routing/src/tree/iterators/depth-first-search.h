#ifndef ROUTING_DEPTH_FIRST_SEARCH_H
#define ROUTING_DEPTH_FIRST_SEARCH_H

#include <stack>
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
		explicit DfsIterator(container &tree);
		DfsIterator& operator++();
		reference operator*();
		bool IsEnd() const;
		iterator Get() const;

	private:
		container *tree;
		std::stack<iterator> stack;

		void traceIteration(container &container, std::stack<iterator> &trace_stack);
};

} // namespace tree


#endif //ROUTING_DEPTH_FIRST_SEARCH_H
