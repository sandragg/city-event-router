#ifndef ROUTING_BREADTH_FIRST_SEARCH_H
#define ROUTING_BREADTH_FIRST_SEARCH_H

#include <queue>
#include "../tree.h"


namespace tree
{

/**
 * Breadth First Search iterator.
 */
template<class Container>
class BfsIterator
{
		using container	= Tree<
		    typename Container::iterator,
		    typename Container::const_iterator>;
		using iterator	= typename container::iterator;
		using reference	= typename iterator::reference;
		using pointer	= typename iterator::pointer;

	public:
		explicit BfsIterator(container &tree);
		BfsIterator& operator++();
		reference operator*();
		pointer operator->();
		bool IsEnd() const;
		iterator Get() const;

	private:
		container *tree;
		std::queue<iterator> queue;

		void traceIteration(container &container, std::queue<iterator> &trace_queue);
};

} // namespace tree


#endif //ROUTING_BREADTH_FIRST_SEARCH_H
