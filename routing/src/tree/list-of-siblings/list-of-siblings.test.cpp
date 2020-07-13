#include <catch2/catch.hpp>
#include <array>
#include <vector>
#include <numeric>
#include "list-of-siblings.h"
#include "../iterators/depth-first-search.h"
#include "../iterators/breadth-first-search.h"


void initialize_tree(list_of_siblings::Tree<int> &tree, const std::array<int, 16> &labels);

TEST_CASE("List of siblings implementation", "[tree]")
{
	std::array<int, 16> labels;
	std::iota(labels.begin(), labels.end(), 1);

	SECTION("Clear tree")
	{
		list_of_siblings::Tree<int> tree;
		REQUIRE(tree.Empty());

		tree.Append(10);
		tree.Append(tree.Root(), { 1, 2, 3 });
		REQUIRE_FALSE(tree.Empty());

		tree.Clear();
		REQUIRE(tree.Empty());
	}

	SECTION("Find nodes in a tree")
	{
		list_of_siblings::Tree<int> tree(16);
		initialize_tree(tree, labels);

		REQUIRE(tree.Find(0) == tree.End());
		REQUIRE(tree.Find(777) == tree.End());
		REQUIRE(tree.Find(tree.End()) == tree.End());

		auto it = tree.Find(1);
		REQUIRE((it != tree.End() && *it == 1));
		auto result = tree.Find(it);
		REQUIRE((it != tree.End() && *it == *result));

		it = tree.Find(8);
		REQUIRE((it != tree.End() && *it == 8));
		result = tree.Find(it);
		REQUIRE((it != tree.End() && *it == *result));

		it = tree.Find(16);
		REQUIRE((it != tree.End() && *it == 16));
		result = tree.Find(it);
		REQUIRE((it != tree.End() && *it == *result));

		it = tree.Find(3);
		REQUIRE((it != tree.End() && *it == 3));
		it = tree.Find(5);
		REQUIRE((it != tree.End() && *it == 5));
		it = tree.Find(9);
		REQUIRE((it != tree.End() && *it == 9));
		it = tree.Find(10);
		REQUIRE((it != tree.End() && *it == 10));
		it = tree.Find(13);
		REQUIRE((it != tree.End() && *it == 13));
	}

	SECTION("Get parent node")
	{
		list_of_siblings::Tree<int> tree(16);
		initialize_tree(tree, labels);

		auto parent = tree.Find(15);
		auto child = tree.Find(16);
		REQUIRE(parent == tree.GetParent(child));
		child = parent;
		parent = tree.Find(10);
		REQUIRE(parent == tree.GetParent(child));
		child = parent;
		parent = tree.Find(4);
		REQUIRE(parent == tree.GetParent(child));
		child = parent;
		REQUIRE(tree.Root() == tree.GetParent(child));

		parent = tree.Find(2);
		child = tree.Find(6);
		REQUIRE(parent == tree.GetParent(child));

		parent = tree.Find(8);
		child = tree.Find(13);
		REQUIRE(parent == tree.GetParent(child));

		child = tree.Find(2);
		REQUIRE(tree.Root() == tree.GetParent(child));
	}

	SECTION("Get children")
	{
		list_of_siblings::Tree<int> tree(16);
		initialize_tree(tree, labels);

		auto it = tree.Root();
		REQUIRE(tree.GetRightSibling(it) == tree.End());

		it = tree.GetLeftMostChild(tree.Root());
		REQUIRE((it != tree.End() && *it == 2));

		it = tree.GetRightSibling(it);
		REQUIRE((it != tree.End() && *it == 3));

		it = tree.GetLeftMostChild(it);
		REQUIRE((it != tree.End() && *it == 7));
		REQUIRE((tree.GetLeftMostChild(it) == tree.End()));

		it = tree.GetRightSibling(it);
		REQUIRE((it != tree.End() && *it == 8));

		it = tree.GetLeftMostChild(it);
		REQUIRE((it != tree.End() && *it == 13));

		it = tree.GetRightSibling(it);
		REQUIRE((it != tree.End() && *it == 14));
		REQUIRE(tree.GetLeftMostChild(it) == tree.End());
		REQUIRE(tree.GetRightSibling(it) == tree.End());
	}
}

TEST_CASE("Tree traversal", "[tree]")
{
	std::array<int, 16> labels;
	std::iota(labels.begin(), labels.end(), 1);

	list_of_siblings::Tree<int> tree(16);
	initialize_tree(tree, labels);

	SECTION("Depth first traversal")
	{
		std::vector<int> expected_result =
			{ 1, 2, 5, 6, 11, 12, 3, 7, 8, 13, 14, 9, 4, 10, 15, 16 };

		tree::DfsIterator<decltype(tree)> it(tree);
		std::vector<int> result;
		while (!it.IsEnd())
		{
			result.push_back(*it);
			++it;
		}
		REQUIRE(result == expected_result);
	}

	SECTION("Breadth first traversal")
	{
		std::vector<int> expected_result(16);
		std::iota(expected_result.begin(), expected_result.end(), 1);

		tree::BfsIterator<decltype(tree)> it(tree);
		std::vector<int> result;
		while (!it.IsEnd())
		{
			result.push_back(*it);
			++it;
		}
		REQUIRE(result == expected_result);
	}
}


void initialize_tree(list_of_siblings::Tree<int> &tree, const std::array<int, 16> &labels)
{
	auto it = labels.begin();

	tree.Append(*it); // 1
	it++;
	tree.Append(tree.Root(), { it, it += 3 }); // 2 3 4
	tree.Append(tree.Find(2), { it, it += 2 }); // 5 6
	tree.Append(tree.Find(3), { it, it += 3 }); // 7 8 9
	tree.Append(tree.Find(4), { it, it += 1 }); // 10
	tree.Append(tree.Find(6), { it, it += 2 }); // 11 12
	tree.Append(tree.Find(8), { it, it += 2 }); // 13 14
	tree.Append(tree.Find(10), { it, it += 1 }); // 15
	tree.Append(tree.Find(15), { it, it += 1 }); // 16
}
