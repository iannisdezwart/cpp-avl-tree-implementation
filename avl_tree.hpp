#ifndef AVL_TREE_IMPL_HPP
#define AVL_TREE_IMPL_HPP

#include <bits/stdc++.h>

/**
 * Structure for a node in an AVL tree.
 * Holds the value, height and the left and right children.
 */
template <typename T>
struct AVLTreeNode
{
	// Value of the node.
	T val;

	// Height of the node.
	// This is equal to max(left_height, right_height) + 1.
	// A leaf node has height 1 by definition.
	size_t height;

	// Pointer to the left child.
	AVLTreeNode *left;

	// Pointer to the right child.
	AVLTreeNode *right;

	/**
	 * Constructs a leaf node for an AVL tree.
	 * @param val Value of the node.
	 */
	AVLTreeNode(const T &val)
		: val(val), height(1), left(nullptr), right(nullptr) {}

	/**
	 * Performs an in-order depth first traversal of the subtree rooted at
	 * this node. Calls the given callback function on each node.
	 * @param callback Callback function to call on each node.
	 * @param depth Current depth of the node.
	 */
	void
	dfs(std::function<void (const AVLTreeNode *, size_t)> cb,
		size_t depth = 0)
	const
	{
		if (left != nullptr)
		{
			left->dfs(cb, depth + 1);
		}

		cb(this, depth);

		if (right != nullptr)
		{
			right->dfs(cb, depth + 1);
		}
	}

	/**
	 * Prints the subtree rooted at this node. The output is in the form
	 * of a lying tree:
	 * 	100 (1)               # left node (height 1)
	 * 200 (2)                    # root node (height 2)
	 * 	300 (1)               # right node (height 1)
	 * This has the property that all nodes are printed in increasing order
	 * if you read it from top to bottom.
	 * @param os Output stream to print to.
	 * @param node Root of the subtree to print.
	 */
	friend std::ostream &
	operator<<(std::ostream &os, const AVLTreeNode &node)
	{
		node.dfs([&os](const AVLTreeNode<T> *node, size_t depth)
		{
			os << std::string(depth, '\t') << node->val
				<< " (" << node->height << ")" << std::endl;
		});

		return os;
	}
};

/**
 * Returns the height of a given AVL tree node.
 * If the node is null, returns 0.
 */
template <typename T>
size_t
avl_height(const AVLTreeNode<T> *node)
{
	if (node == nullptr)
	{
		return 0;
	}

	return node->height;
}

/**
 * Rebalances the subtree rooted at a given node `z` for the left-left case.
 */
template <typename T>
AVLTreeNode<T> *
avl_rebalance_left_left(AVLTreeNode<T> *z)
{
	/*
		      z                    y
		     / \                /    \
		    y   T4    -->      x      z
		   / \                / \    / \
		  x  T3              T1 T2  T3 T4
		 / \
		T1 T2
	*/

	AVLTreeNode<T> *y = z->left;
	AVLTreeNode<T> *x = y->left;
	AVLTreeNode<T> *T1 = x->left;
	AVLTreeNode<T> *T2 = x->right;
	AVLTreeNode<T> *T3 = y->right;
	AVLTreeNode<T> *T4 = z->right;

	// Reorganise the nodes.

	z->left = T3;
	y->right = z;

	// Update the heights.

	x->height = std::max(avl_height(T1), avl_height(T2)) + 1;
	z->height = std::max(avl_height(T3), avl_height(T4)) + 1;
	y->height = std::max(x->height, z->height) + 1;

	return y;
}

/**
 * Rebalances the subtree rooted at a given node `z` for the left-right case.
 */
template <typename T>
AVLTreeNode<T> *
avl_rebalance_left_right(AVLTreeNode<T> *z)
{
	/*
	        z                    x
	       / \                /    \
	      y   T4    -->      y      z
	     / \                / \    / \
	    T1  x              T1 T2  T3 T4
	       / \
	      T2 T3
	*/

	AVLTreeNode<T> *y = z->left;
	AVLTreeNode<T> *x = y->right;
	AVLTreeNode<T> *T1 = y->left;
	AVLTreeNode<T> *T2 = x->left;
	AVLTreeNode<T> *T3 = x->right;
	AVLTreeNode<T> *T4 = z->right;

	// Reorganise the nodes.

	y->right = T2;
	z->left = T3;
	x->left = y;
	x->right = z;

	// Update the heights.

	y->height = std::max(avl_height(T1), avl_height(T2)) + 1;
	z->height = std::max(avl_height(T3), avl_height(T4)) + 1;
	x->height = std::max(y->height, z->height) + 1;

	return x;
}

/**
 * Rebalances the subtree rooted at a given node `z` for the right-right case.
 */
template <typename T>
AVLTreeNode<T> *
avl_rebalance_right_right(AVLTreeNode<T> *z)
{
	/*
	        z                    y
	       / \                /    \
	      T1  y     -->      z      x
	         / \            / \    / \
	        T2  x          T1 T2  T3 T4
	           / \
	          T3 T4
	*/

	AVLTreeNode<T> *y = z->right;
	AVLTreeNode<T> *x = y->right;
	AVLTreeNode<T> *T1 = z->left;
	AVLTreeNode<T> *T2 = y->left;
	AVLTreeNode<T> *T3 = x->left;
	AVLTreeNode<T> *T4 = x->right;

	// Reorganise the nodes.

	z->right = T2;
	y->left = z;

	// Update the heights.

	z->height = std::max(avl_height(T1), avl_height(T2)) + 1;
	x->height = std::max(avl_height(T3), avl_height(T4)) + 1;
	y->height = std::max(z->height, x->height) + 1;

	return y;
}

/**
 * Rebalances the subtree rooted at a given node `z` for the right-left case.
 */
template <typename T>
AVLTreeNode<T> *
avl_rebalance_right_left(AVLTreeNode<T> *z)
{
	/*
	        z                    x
	       / \                /    \
	      T1  y     -->      z      y
	         / \            / \    / \
	        x  T4          T1 T2  T3 T4
	       / \
	      T2 T3
	*/

	AVLTreeNode<T> *y = z->right;
	AVLTreeNode<T> *x = y->left;
	AVLTreeNode<T> *T1 = z->left;
	AVLTreeNode<T> *T2 = x->left;
	AVLTreeNode<T> *T3 = x->right;
	AVLTreeNode<T> *T4 = y->right;

	// Reorganise the nodes.

	z->right = T2;
	y->left = T3;
	x->left = z;
	x->right = y;

	// Update the heights.

	z->height = std::max(avl_height(T1), avl_height(T2)) + 1;
	y->height = std::max(avl_height(T3), avl_height(T4)) + 1;
	x->height = std::max(z->height, y->height) + 1;

	return x;
}

/**
 * Inserts `val` into the subtree rooted at a given `node`.
 * Handles the `&size` of the subtree and rebalances the tree if necessary.
 * Returns the new root of the subtree.
 */
template <typename T>
AVLTreeNode<T> *
avl_insert(AVLTreeNode<T> *node, const T &val, size_t &size)
{
	// When we reach the end of the tree,
	// insert the new value at this position.

	if (node == nullptr)
	{
		size++;
		return new AVLTreeNode<T>(val);
	}

	// Traverse the tree according to how the new value compares
	// to the left and right children of the current node.

	if (val < node->val)
	{
		node->left = avl_insert(node->left, val, size);
	}
	else if (val > node->val)
	{
		node->right = avl_insert(node->right, val, size);
	}
	else
	{
		// The value already exists in the tree.
		// We will do nothing.

		return node;
	}

	// Get the height of the left and right children.

	size_t left_height = avl_height(node->left);
	size_t right_height = avl_height(node->right);

	// After the recursive downwards step, we will traverse the
	// tree upwards again and update the height of the current node.

	node->height = 1 + std::max(left_height, right_height);

	// We will check if the current node is unbalanced.
	// If it is, we will have to find a rotation to fix it.

	ssize_t balance = left_height - right_height;

	if (balance > 1)
	{
		// The left subtree is too tall.

		if (val < node->left->val)
		{
			// Left-left case.

			return avl_rebalance_left_left(node);
		}
		else
		{
			// Left-right case.

			return avl_rebalance_left_right(node);
		}
	}

	if (balance < -1)
	{
		// The right subtree is too tall.

		if (val > node->right->val)
		{
			// Right-right case.

			return avl_rebalance_right_right(node);
		}
		else
		{
			// Right-left case.

			return avl_rebalance_right_left(node);
		}
	}

	// This node is already balanced, so we just return it
	// as it currently is.

	return node;
}

/**
 * Utility function that returns the balance of a given node.
 * The balance is defined as the difference between the height
 * of the left subtree and the height of the right subtree.
 */
template <typename T>
ssize_t
avl_balance(const AVLTreeNode<T> *node)
{
	if (node == nullptr)
	{
		return 0;
	}

	return avl_height(node->left) - avl_height(node->right);
}

/**
 * Removs `val` from the subtree rooted at a given `node`.
 * Handles the `&size` of the subtree and rebalances the tree if necessary.
 * Returns the new root of the subtree.
 */
template <typename T>
AVLTreeNode<T> *
avl_remove(AVLTreeNode<T> *node, const T& val, size_t &size);

/**
 * Deletes `node` and reconnects the tree if it became disconnected.
 */
template <typename T>
AVLTreeNode<T> *
avl_remove_node(AVLTreeNode<T> *node)
{
	// Check how many children this node has.

	if (node->left == nullptr && node->right == nullptr)
	{
		// The node has no children.
		// We can just delete it from the tree.

		delete node;
		return nullptr;
	}

	if (node->left == nullptr)
	{
		// The node has only a right child.
		// We can just replace the node with its right child.

		AVLTreeNode<T> *right = node->right;
		delete node;
		return right;
	}

	if (node->right == nullptr)
	{
		// The node has only a left child.
		// We can just replace the node with its left child.

		AVLTreeNode<T> *left = node->left;
		delete node;
		return left;
	}

	// The node has two children.
	// We will replace the node with its in-order successor.
	// This is the left-most child of the right subtree.

	AVLTreeNode<T> *successor = node->right;

	while (successor->left != nullptr)
	{
		successor = successor->left;
	}

	// Copy the value from the successor node.

	node->val = successor->val;

	// Remove the successor node.

	size_t dummy_size;
	node->right = avl_remove(node->right, successor->val, dummy_size);

	// Return the "new" root of the subtree.
	// It's not actually new, because we just replace the value
	// with the value of the successor node.

	return node;
}

/**
 * Removs `val` from the subtree rooted at a given `node`.
 * Handles the `&size` of the subtree and rebalances the tree if necessary.
 * Returns the new root of the subtree.
 */
template <typename T>
AVLTreeNode<T> *
avl_remove(AVLTreeNode<T> *node, const T& val, size_t &size)
{
	// When we reach the end of the tree, we haven't found
	// the value to remove.

	if (node == nullptr)
	{
		return nullptr;
	}

	// Traverse the tree according to how the value to be removed
	// compares to the left and right children of the current node.

	if (val < node->val)
	{
		node->left = avl_remove(node->left, val, size);
	}
	else if (val > node->val)
	{
		node->right = avl_remove(node->right, val, size);
	}
	else
	{
		// We found the node to be removed.

		size--;
		node = avl_remove_node(node);
	}

	// Make sure the node exists.

	if (node == nullptr)
	{
		return nullptr;
	}

	// Get the height of the left and right children.

	size_t left_height = avl_height(node->left);
	size_t right_height = avl_height(node->right);

	// After the recursive downwards step, we will traverse the
	// tree upwards again and update the height of the current node.

	node->height = 1 + std::max(left_height, right_height);

	// We will check if the current node is unbalanced.
	// If it is, we will have to find a rotation to fix it.

	ssize_t balance = left_height - right_height;

	if (balance > 1)
	{
		// The left subtree is too tall.

		if (avl_balance(node->left) >= 0)
		{
			// Left-left case.

			return avl_rebalance_left_left(node);
		}
		else
		{
			// Left-right case.

			return avl_rebalance_left_right(node);
		}
	}

	if (balance < -1)
	{
		// The right subtree is too tall.

		if (avl_balance(node->right) <= 0)
		{
			// Right-right case.

			return avl_rebalance_right_right(node);
		}
		else
		{
			// Right-left case.

			return avl_rebalance_right_left(node);
		}
	}

	// This node is already balanced, so we just return it
	// as it currently is.

	return node;
}

/**
 * Searches the tree for a given value.
 * Returns true if the value is found, false otherwise.
 */
template <typename T>
bool
avl_has(const AVLTreeNode<T> *node, const T& val)
{
	// If we reach the end of the tree, the value is not in the tree.

	if (node == nullptr)
	{
		return false;
	}

	// Traverse the tree according to how the value to be found
	// compares to the left and right children of the current node.

	if (val < node->val)
	{
		return avl_has(node->left, val);
	}

	if (val > node->val)
	{
		return avl_has(node->right, val);
	}

	// We found the value.

	return true;
}

/**
 * Structure representing an AVL tree.
 * Holds the root node of the tree as well as its size.
 */
template <typename T>
struct AVLTree
{
	// The root of the tree.
	AVLTreeNode<T> *root;

	// The current number of elements in the tree.
	size_t size;

	/**
	 * @brief Constructs an empty AVL tree.
	 */
	AVLTree() : root(nullptr), size(0) {}

	/**
	 * Inserts `val` into the tree.
	 * If it already exists, nothing happens.
	 */
	void
	insert(const T &val)
	{
		root = avl_insert(root, val, size);
	}

	/**
	 * Removes `val` from the tree.
	 * If it doesn't exist, nothing happens.
	 */
	void
	remove(const T &val)
	{
		root = avl_remove(root, val, size);
	}

	/**
	 * Returns true if the tree contains `val`, false otherwise.
	 */
	bool
	has(const T &val)
	const
	{
		return avl_has(root, val);
	}

	/**
	 * Prints the entire AVL tree and its size.
	 * The output is in the form of a lying tree:
	 * AVLTree (3)
	 * 	100 (1)               # left node (height 1)
	 * 200 (2)                    # root node (height 2)
	 * 	300 (1)               # right node (height 1)
	 * This has the property that all nodes are printed in increasing order
	 * if you read it from top to bottom.
	 * @param os Output stream to print to.
	 * @param tree The tree to print.
	 */
	friend std::ostream &
	operator<<(std::ostream &os, const AVLTree &tree)
	{
		os << "AVLTree (" << tree.size << ")" << std::endl;

		if (tree.root == nullptr)
		{
			return os;
		}

		return os << *tree.root;
	}
};

#endif