#ifndef AVL_TREE_TEST_HPP
#define AVL_TREE_TEST_HPP

#include <bits/stdc++.h>

#include "avl_tree.hpp"

/**
 * Asserts that a given AVL tree is valid.
 * Asserts that:
 *  * The tree is balanced.
 *  * The order of the nodes is correct.
 *  * The heights of the nodes are correct.
 *  * The balance of the nodes are between -1 and 1.
 *  * The size of the tree is equal to the number of nodes in the tree.
 */
template <typename T>
void
assert_tree_valid(const AVLTree<T> &tree)
{
	if (tree.root == nullptr)
	{
		if (tree.size != 0)
		{
			std::cerr << "Tree size is " << tree.size
				<< " but should be 0" << std::endl;
			assert(false);
		}

		return;
	}

	size_t size = 0;

	tree.root->dfs([&size](const AVLTreeNode<T> *node, size_t depth)
	{
		if (node->left != nullptr && node->left->val >= node->val)
		{
			std::cerr << "Invalid subtree order: " << std::endl
				<< *node << std::endl;
			assert(false);
		}

		if (node->right != nullptr && node->right->val <= node->val)
		{
			std::cerr << "Invalid subtree order: " << std::endl
				<< *node << std::endl;
			assert(false);
		}

		if (std::abs(avl_balance(node)) > 1)
		{
			std::cerr << "Invalid subtree balance: " << std::endl
				<< *node << std::endl;
			assert(false);
		}

		if (node->height != 1 + std::max(avl_height(node->left),
			avl_height(node->right)))
		{
			std::cerr << "Invalid subtree height: " << std::endl
				<< *node << std::endl;
			assert(false);
		}

		size++;
	});

	if (size != tree.size)
	{
		std::cerr << "Tree size is " << tree.size
			<< " but counted " << size << " nodes" << std::endl;
		assert(false);
	}
}

/**
 * Performs a random test of the AVL tree.
 * The test consists of inserting random values into the tree and
 * then removing them in random order.
 * In between the test, all values are checked to be in the tree.
 * @param size The number of random elements to insert and remove.
 * @param min The minimum value to insert.
 * @param max The maximum value to insert.
 */
void
randomised_test(size_t size, int min, int max)
{
	// Set up random number generator.

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distribution(min, max);

	// Create the AVL tree.

	AVLTree<int> tree;
	assert_tree_valid(tree);

	// Insert random values.

	std::vector<int> values(size);

	for (size_t i = 0; i < size; i++)
	{
		values[i] = distribution(gen);
	}

	// Insert all values to the AVL tree.

	for (size_t i = 0; i < size; i++)
	{
		#ifdef DEBUG
		std::cout << "Inserting " << values[i] << std::endl;
		#endif

		tree.insert(values[i]);

		#ifdef DEBUG
		std::cout << tree << std::endl;
		#endif

		assert_tree_valid(tree);
	}

	// Check that all values are in the AVL tree.

	for (size_t i = 0; i < size; i++)
	{
		#ifdef DEBUG
		std::cout << "Finding " << values[i] << std::endl;
		#endif

		if (!tree.has(values[i]))
		{
			std::cerr << "Value " << values[i]
				<< " not found, but it should be" << std::endl;
			assert(false);
		}
	}

	// Remove all values from the AVL tree in random order.

	std::random_shuffle(values.begin(), values.end());

	for (size_t i = 0; i < size; i++)
	{
		#ifdef DEBUG
		std::cout << "Removing " << values[i] << std::endl;
		#endif

		tree.remove(values[i]);

		#ifdef DEBUG
		std::cout << tree << std::endl;
		#endif

		assert_tree_valid(tree);
	}

	assert_tree_valid(tree);
}

#endif