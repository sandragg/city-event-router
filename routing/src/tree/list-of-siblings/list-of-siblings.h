#ifndef ROUTING_LIST_OF_SIBLINGS_H
#define ROUTING_LIST_OF_SIBLINGS_H

#include <vector>
#include <forward_list>
#include "../tree.h"
#include "base-iterator.h"
#include "base-const-iterator.h"


namespace list_of_siblings
{

template<class _Tp>
class Tree : public tree::Tree<TreeIterator<_Tp>, ConstTreeIterator<_Tp>>
{
		using position			= size_t;

	public:
		using value_type		= _Tp;
		using iterator			= TreeIterator<value_type>;
		using const_iterator	= ConstTreeIterator<value_type>;
		using reference			= typename iterator::reference;
		using const_reference	= typename const_iterator::reference;

		explicit Tree(size_t size);
		iterator Append(value_type root_value) override;
		iterator Append(iterator root, std::vector<value_type> &descendants) override;
		iterator Root() override;
		const_iterator Root() const override;
		reference Find(iterator position) override;
		const_reference Find(const_iterator position) const override;
		iterator GetParent(iterator position) override;
		const_iterator GetParent(const_iterator position) const override;
		iterator GetLeftMostChild(iterator position) override;
		const_iterator GetLeftMostChild(const_iterator position) const override;
		iterator GetRightSibling(iterator position) override;
		const_iterator GetRightSibling(const_iterator position) const override;
		void Clear() override;
		bool Empty() const override;
		size_t Depth() const override;
		iterator End() override;
		const_iterator End() const override;

	private:
		struct Node
		{
			position next_free;
			value_type value;
			std::forward_list<size_t> descendants;
		};

		std::vector<Node> nodes;
		position root;
		position space_cursor;

		template<class> friend class TreeIterator;
		template<class> friend class ConstTreeIterator;

		void init_space_cursor(position begin);
		void clear(position root_node);
		void clear_descendants(position root_node);
		position allocate_node();
		void erase_node(position node_position);
		position find_node_position(iterator node) const;
};

} // namespace list_of_siblings


#endif //ROUTING_LIST_OF_SIBLINGS_H
