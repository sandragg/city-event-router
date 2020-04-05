#ifndef ROUTING_LIST_OF_SIBLINGS_H
#define ROUTING_LIST_OF_SIBLINGS_H

#include <vector>
#include <forward_list>
#include "tree.h"


namespace list_of_siblings
{

template<class _Tp>
class Tree : public tree::Tree<_Tp>
{
	private:
		using base				= tree::Tree<_Tp>;

	public:
		using value_type		= typename base::value_type;
		using reference			= typename base::reference;
		using const_reference	= typename base::const_reference;

		// TODO Create custom Tree iterator
		// Iterator may point to Node or array index.
		// Iterator dereference should return value_type.
		using iterator			= std::iterator_traits<value_type>;
		using const_iterator	= std::iterator_traits<const value_type>;

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

	private:
		struct Node
		{
			_Tp value;
			std::forward_list<size_t> *descendants;
		};

		std::vector<Node> *nodes;
};

} // namespace list_of_siblings


#endif //ROUTING_LIST_OF_SIBLINGS_H
