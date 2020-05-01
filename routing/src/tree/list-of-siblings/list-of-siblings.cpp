#include "list-of-siblings.h"
#include<algorithm>


namespace list_of_siblings
{

template<class _Tp>
Tree<_Tp>::Tree(size_t size)
{
	nodes.resize(size);
	init_space_cursor(0);
	root = space_cursor;
}

template<class _Tp>
typename Tree<_Tp>::iterator Tree<_Tp>::Append(value_type root_value)
{
	Clear();

	root = allocate_node();
	nodes[root].value = root_value;

	return iterator(*this, root);
}

template<class _Tp>
typename Tree<_Tp>::iterator
Tree<_Tp>::Append(iterator root_node, std::vector<value_type> &descendants)
{
	auto root_position = find_node_position(root_node);
	clear_descendants(root_position);

	auto &descendants_list = nodes[root_position].descendants;
	position new_position = 0;
	for (const auto &value : descendants)
	{
		new_position = allocate_node();
		nodes[new_position].value = value;
		descendants_list.push_front(new_position);
	}

	return root_node;
}

template<class _Tp>
typename Tree<_Tp>::iterator Tree<_Tp>::Root()
{
	return iterator(*this, root);
}

template<class _Tp>
typename Tree<_Tp>::const_iterator Tree<_Tp>::Root() const
{
	return const_iterator(*this, root);
}

template<class _Tp>
typename Tree<_Tp>::iterator
Tree<_Tp>::Find(const_iterator node) const
{
	try
	{
		auto node_position = find_node_position(node);
		return iterator(const_cast<Tree<_Tp>&>(*this), node_position);
	}
	catch (std::domain_error err)
	{
		std::cerr << err.what() << std::endl;
		return End();
	}
}

template<class _Tp>
typename Tree<_Tp>::iterator
Tree<_Tp>::GetParent(const_iterator node) const
{
	if (node == Root()) return End();

	try
	{
		auto parent_position = find_node_parent(node);
		return iterator(const_cast<Tree<_Tp>&>(*this), parent_position);
	}
	catch (std::domain_error err)
	{
		std::cerr << err.what() << std::endl;
		return End();
	}
}

template<class _Tp>
typename Tree<_Tp>::iterator
Tree<_Tp>::GetLeftMostChild(const_iterator node) const
{
	try
	{
		auto node_position = find_node_position(node);
		auto descendants = nodes[node_position].descendants;

		if (!descendants.empty())
			return iterator(const_cast<Tree<_Tp>&>(*this), descendants.front());
	}
	catch (std::domain_error err)
	{
		std::cerr << err.what() << std::endl;
	}

	return End();
}

template<class _Tp>
typename Tree<_Tp>::iterator
Tree<_Tp>::GetRightSibling(const_iterator node) const
{
	try
	{
		auto parent_position = find_node_parent(node);
		auto descendants_list = nodes[parent_position].descendants;

		auto value = *node;

		auto descendant = std::find_if(
			descendants_list.begin(),
			descendants_list.end(),
			[&](position p)
			{
				return &nodes[p].value == &value;
			});

		auto next_sibling = ++descendant;
		if (next_sibling != descendants_list.end())
			return iterator(const_cast<Tree<_Tp>&>(*this), *next_sibling);
	}
	catch (std::domain_error err)
	{
		std::cerr << err.what() << std::endl;
	}

	return End();
}

template<class _Tp>
void Tree<_Tp>::Clear()
{
	if (!Empty())
	{
		clear(root);
		init_space_cursor(0);
		root = space_cursor;
	}
}

template<class _Tp>
bool Tree<_Tp>::Empty() const
{
	return root == space_cursor;
}

template<class _Tp>
typename Tree<_Tp>::iterator Tree<_Tp>::End() const
{
	return iterator(nullptr);
}

template<class _Tp>
void Tree<_Tp>::init_space_cursor(position begin)
{
	space_cursor = begin;

	for (size_t i = begin; i < nodes.size(); i++)
		nodes[i].next_free = i + 1;
}

template<class _Tp>
void Tree<_Tp>::clear(position root_node)
{
	std::queue<position> trace_queue;
	trace_queue.push(root_node);

	while (!trace_queue.empty())
	{
		auto current_node = trace_queue.front();
		trace_queue.pop();

		auto descendants = nodes[current_node].descendants;
		auto next_node = descendants.begin();
		while (next_node != descendants.end())
		{
			trace_queue.push(*next_node);
			next_node++;
		}
		erase_node(current_node);
	}
}

template<class _Tp>
void Tree<_Tp>::clear_descendants(position root_node)
{
	auto &descendants_list = nodes[root_node].descendants;
	auto descendant = descendants_list.begin();
	while (descendant != descendants_list.end())
	{
		clear(*descendant);
		descendant++;
		descendants_list.pop_front();
	}
}

template<class _Tp>
typename Tree<_Tp>::position Tree<_Tp>::allocate_node()
{
	if (space_cursor == nodes.size())
	{
		nodes.resize(nodes.size() * 2);
		init_space_cursor(space_cursor);
	}
	auto position = space_cursor;
	space_cursor = nodes[space_cursor].next_free;

	return position;
}

template<class _Tp>
void Tree<_Tp>::erase_node(position p)
{
	nodes[p].descendants.clear();
	nodes[p].next_free = space_cursor;
	space_cursor = p;
}

template<class _Tp>
typename Tree<_Tp>::position
Tree<_Tp>::find_node_position(const_iterator node) const
{
	auto value = *node;

	if (&value == &nodes[root].value) return root;

	std::queue<position> trace_queue;
	trace_queue.push(root);

	while (!trace_queue.empty())
	{
		auto current_node = trace_queue.front();
		trace_queue.pop();

		auto descendants = nodes[current_node].descendants;
		auto next_node = descendants.begin();
		while (next_node != descendants.end())
		{
			if (&value == &nodes[*next_node].value) return *next_node;
			trace_queue.push(*next_node);
			next_node++;
		}
	}

	throw std::domain_error("Node was not found.");
}

template<class _Tp>
typename Tree<_Tp>::position
Tree<_Tp>::find_node_parent(const_iterator node) const
{
	auto value = *node;

	std::queue<position> trace_queue;
	trace_queue.push(root);

	while (!trace_queue.empty())
	{
		auto current_node = trace_queue.front();
		trace_queue.pop();

		auto descendants = nodes[current_node].descendants;
		auto next_node = descendants.begin();
		while (next_node != descendants.end())
		{
			if (&value == &nodes[*next_node].value) return current_node;
			trace_queue.push(*next_node);
			next_node++;
		}
	}

	throw std::domain_error("Parent was not found.");
}

} // namespace list_of_siblings
