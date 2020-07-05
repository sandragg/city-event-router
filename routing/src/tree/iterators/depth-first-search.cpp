#include "depth-first-search.h"


namespace tree
{

template<class Container>
DfsIterator<Container>::DfsIterator(container& tree)
{
	this->tree = &tree;
	stack.push(tree.Root());
}

template<class Container>
typename DfsIterator<Container>::reference
DfsIterator<Container>::operator*()
{
	return *stack.top();
}

template<class Container>
typename DfsIterator<Container>::pointer DfsIterator<Container>::operator->()
{
	return &*(*this);
}

template<class Container>
DfsIterator<Container>& DfsIterator<Container>::operator++()
{
	traceIteration(*tree, stack);
	return *this;
}

template<class Container>
bool DfsIterator<Container>::IsEnd() const
{
	return stack.empty();
}

template<class Container>
typename DfsIterator<Container>::iterator
DfsIterator<Container>::Get() const
{
	return stack.top();
}

template<class Container>
void DfsIterator<Container>::traceIteration(container &container, std::stack<iterator> &trace_stack)
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

} // namespace tree
