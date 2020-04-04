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
	public:
		using base				= tree::Tree<_Tp>;
		using value_type 		= typename base::value_type;
		using reference 		= typename base::reference;
		using const_reference	= typename base::const_reference;
		using iterator 			= std::iterator_traits<value_type>; // ?
		using const_iterator	= std::iterator_traits<const value_type>; // ?

		reference Root();
		const_reference Root() const;
		reference Find(const_iterator position);
		const_reference Find(const_iterator position) const;
		iterator GetParent(const_iterator position);
		const_iterator GetParent(const_iterator position) const;
		iterator GetLeftMostChild(const_iterator position);
		const_iterator GetLeftMostChild(const_iterator position) const;
		iterator GetRightSibling(const_iterator position);
		const_iterator GetRightSibling(const_iterator position) const;
		void Clear();
		size_t Depth() const;
		size_t Size() const;

	private:
		std::vector<std::forward_list<_Tp>> container; // ?
};

} // namespace list_of_siblings


#endif //ROUTING_LIST_OF_SIBLINGS_H
