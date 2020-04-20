#include "list-of-siblings.h"
using namespace list_of_siblings;

namespace list_of_siblings
{

template<class _Tp>
typename Tree<_Tp>::iterator Tree<_Tp>::Append(value_type root_value)
{
	return nullptr;
}

template<class _Tp>
typename Tree<_Tp>::iterator Tree<_Tp>::Append(iterator root_node, std::vector<value_type> &children)
{
	return nullptr;
}

template<class _Tp>
typename Tree<_Tp>::iterator Tree<_Tp>::Root()
{
	return iterator(this, root);
}

template<class _Tp>
typename Tree<_Tp>::const_iterator Tree<_Tp>::Root() const
{
	return const_iterator(this, root);
}

template<class _Tp>
typename Tree<_Tp>::iterator Tree<_Tp>::End()
{
	return iterator(nullptr);
}

template<class _Tp>
typename Tree<_Tp>::const_iterator Tree<_Tp>::End() const
{
	return const_iterator(nullptr);
}

} // namespace list_of_siblings
