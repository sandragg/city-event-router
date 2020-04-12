#include "depth-first-search.h"


template<class _Container>
DfsIterator<_Container>::DfsIterator(const container& tree)
{
	this->tree = &tree;
	stack.push(tree.Root());
}

template<class _Container>
typename DfsIterator<_Container>::reference
DfsIterator<_Container>::operator*()
{
	return *stack.top();
}

template<class _Container>
DfsIterator<_Container>& DfsIterator<_Container>::operator++()
{
	traceIteration(*tree, stack);
	return *this;
}

template<class _Container>
bool DfsIterator<_Container>::IsEnd() const
{
	return stack.empty();
}

template<class _Container>
void DfsIterator<_Container>::traceIteration(const container &container, std::stack<iterator> &trace_stack)
{
	while (!trace_stack.empty())
	{
		auto next_node = container.GetLeftMostChild(trace_stack.top());
		while (next_node == container.End())
		{
			auto current_node = trace_stack.top();
			trace_stack.pop();
			if (trace_stack.empty()) return;
			next_node = container.GetRightSibling(current_node);
		}
		trace_stack.push(next_node);
		return;
	}
}
