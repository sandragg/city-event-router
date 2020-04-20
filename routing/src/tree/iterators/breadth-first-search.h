#ifndef ROUTING_BREADTH_FIRST_SEARCH_H
#define ROUTING_BREADTH_FIRST_SEARCH_H

#include <queue>
#include "../tree.h"


namespace tree
{

/**
 * Breadth First Search iterator.
 */
template<class _Container>
class BfsIterator
{
		using container	= Tree<
		    typename _Container::iterator,
		    typename _Container::const_iterator>;
		using iterator	= typename container::iterator;
		using reference	= typename iterator::reference;

	public:
		explicit BfsIterator(const container &tree);
		BfsIterator& operator++();
		reference operator*();
		bool IsEnd() const;
		iterator Get() const;

	private:
		container *tree;
		std::queue<iterator> queue;

		void traceIteration(const container &container, std::queue<iterator> &trace_queue);
};

} // namespace tree


#endif //ROUTING_BREADTH_FIRST_SEARCH_H
