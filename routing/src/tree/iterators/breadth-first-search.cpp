#include "breadth-first-search.h"


namespace tree
{

template<class Container>
BfsIterator<Container>::BfsIterator(container& tree)
{
	this->tree = &tree;
	queue.push(tree.Root());
}

template<class Container>
typename BfsIterator<Container>::reference
BfsIterator<Container>::operator*()
{
	return *queue.front();
}

template<class Container>
typename BfsIterator<Container>::pointer BfsIterator<Container>::operator->()
{
	return &*(*this);
}

template<class Container>
BfsIterator<Container>& BfsIterator<Container>::operator++()
{
	traceIteration(*tree, queue);
	return *this;
}

template<class Container>
bool BfsIterator<Container>::IsEnd() const
{
	return queue.empty();
}

template<class Container>
typename BfsIterator<Container>::iterator
tree::BfsIterator<Container>::Get() const
{
	return queue.front();
}

template<class Container>
void BfsIterator<Container>::traceIteration(container &container, std::queue<iterator> &trace_queue)
{
	while (!trace_queue.empty())
	{
		auto current_node = trace_queue.front();
		trace_queue.pop();
		auto next_node = container.GetLeftMostChild(current_node);
		while (next_node != container.End())
		{
			trace_queue.push(next_node);
			next_node = container.GetRightSibling(next_node);
		}
		return;
	}
}

} // namespace tree
