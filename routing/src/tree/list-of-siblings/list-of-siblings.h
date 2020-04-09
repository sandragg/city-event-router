#ifndef ROUTING_LIST_OF_SIBLINGS_H
#define ROUTING_LIST_OF_SIBLINGS_H

#include <vector>
#include <forward_list>
#include "../tree.h"


namespace list_of_siblings
{

template<class _Tp>
class TreeIterator;

template<class _Tp>
class ConstTreeIterator;

template<class _Tp>
class Tree : public tree::Tree<TreeIterator<_Tp>, ConstTreeIterator<_Tp>>
{
	private:
		struct Node;
		using position			= size_t;

	public:
		using value_type		= _Tp;
		using iterator			= TreeIterator<value_type>;
		using const_iterator	= ConstTreeIterator<value_type>;
		using reference			= typename iterator::reference;
		using const_reference	= typename const_iterator::reference;

		iterator Root() override;
		const_iterator Root() const override;
		reference Find(const_iterator position) override;
		const_reference Find(const_iterator position) const override;
		iterator GetParent(const_iterator position) override;
		const_iterator GetParent(const_iterator position) const override;
		iterator GetLeftMostChild(const_iterator position) override;
		const_iterator GetLeftMostChild(const_iterator position) const override;
		iterator GetRightSibling(const_iterator position) override;
		const_iterator GetRightSibling(const_iterator position) const override;
		void Clear() override;
		size_t Depth() const override;
		size_t Size() const override;

		friend class TreeIterator<value_type>;

	private:
		struct Node
		{
			_Tp value;
			std::forward_list<size_t> *descendants;
		};

		std::vector<Node> *nodes;
		position root;
		position space_cursor;
};

#include "list-of-siblings.cpp"

} // namespace list_of_siblings


#endif //ROUTING_LIST_OF_SIBLINGS_H
