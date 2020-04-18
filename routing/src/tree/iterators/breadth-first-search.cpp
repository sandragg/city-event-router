#include "breadth-first-search.h"


template<class _Container>
BfsIterator<_Container>::BfsIterator(const container& tree)
{
	this->tree = &tree;
	queue.push(tree.Root());
}

template<class _Container>
typename BfsIterator<_Container>::reference
BfsIterator<_Container>::operator*()
{
	return *queue.front();
}

template<class _Container>
BfsIterator<_Container>& BfsIterator<_Container>::operator++()
{
	traceIteration(*tree, queue);
	return *this;
}

template<class _Container>
bool BfsIterator<_Container>::IsEnd() const
{
	return queue.empty();
}

template<class _Container>
typename BfsIterator<_Container>::iterator
tree::BfsIterator<_Container>::Get() const
{
	return queue.front();
}

template<class _Container>
void BfsIterator<_Container>::traceIteration(const container &container, std::queue<iterator> &trace_queue)
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
