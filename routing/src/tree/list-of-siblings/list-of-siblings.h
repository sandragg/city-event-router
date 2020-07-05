#ifndef ROUTING_LIST_OF_SIBLINGS_H
#define ROUTING_LIST_OF_SIBLINGS_H

#include <vector>
#include <forward_list>
#include "../tree.h"
#include "base-iterator.h"
#include "base-const-iterator.h"


namespace list_of_siblings
{

template<class Tp>
class Tree : public tree::Tree<TreeIterator<Tp>, ConstTreeIterator<Tp>>
{
		using position			= size_t;

	public:
		using value_type		= Tp;
		using iterator			= TreeIterator<value_type>;
		using const_iterator	= ConstTreeIterator<value_type>;
		using reference			= typename iterator::reference;
		using const_reference	= typename const_iterator::reference;

		explicit Tree(size_t size = DEFAULT_SIZE);
		iterator Append(value_type root_value) override;
		iterator Append(iterator root, std::vector<value_type> &descendants) override;
		iterator Root() override;
		const_iterator Root() const override;
		iterator Find(const_iterator node) const override;
		iterator GetParent(const_iterator node) const override;
		iterator GetLeftMostChild(const_iterator node) const override;
		iterator GetRightSibling(const_iterator node) const override;
		void Clear() override;
		bool Empty() const override;
		iterator End() const override;

	private:
		static const size_t DEFAULT_SIZE = 32;
		struct Node
		{
			/**
			 * Position of the next free node.
			 * It's used to link elements of the free nodes list.
			 * @see #space_cursor
			 */
			position next_free;
			value_type value;
			std::forward_list<position> descendants;
		};
		/**
		 * Nodes container.
		 * Includes both used and free nodes.
		 */
		std::vector<Node> nodes;
		/**
		 * Position of the tree root.
		 */
		position root;
		/**
		 * Position of the first free node (free nodes list head).
		 */
		position space_cursor;

		template<class> friend class TreeIterator;
		template<class> friend class ConstTreeIterator;

		/**
		 * Initialize free nodes.
		 * Set #space_cursor to *begin* position.
		 * Append nodes from *begin* position to #nodes.size
		 * to the free nodes list.
		 *
		 * @param begin Start position of the free nodes
		 */
		void init_space_cursor(position begin);
		/**
		 * Clear subtree including root node.
		 *
		 * @param root_node Subtree root position
		 */
		void clear(position root_node);
		/**
		 * Clear subtree NOT including the root node.
		 *
		 * @param root_node Subtree root position
		 */
		void clear_descendants(position root_node);
		/**
		 * Get new node position.
		 */
		position allocate_node();
		/**
		 * Remove node.
		 * Return position to the free nodes list.
		 *
		 * @param root_node Node position to erase
		 */
		void erase_node(position node_position);
		/**
		 * Find node position.
		 *
		 * @param node Iterator to the node
		 * @return Node position
		 * @throw domain_error If node wasn't found.
		 */
		position find_node_position(const_iterator node) const;
		/**
		 * Find the parent node position.
		 *
		 * @param node Iterator to the node
		 * @return Parent position
		 * @throw domain_error If parent wasn't found.
		 */
		position find_node_parent(const_iterator node) const;
};

} // namespace list_of_siblings


#endif //ROUTING_LIST_OF_SIBLINGS_H
