#include <bits/stdc++.h>

#include "avl_tree.hpp"
#include "test.hpp"

// #define DEBUG

/**
 * Convienience function that gets input from cin and handles errors.
 */
template <typename T>
void
cin_or_exit(T &val)
{
	std::cin >> val;

	if (std::cin.fail())
	{
		std::cerr << "Invalid input" << std::endl;
		exit(1);
	}

	if (std::cin.eof())
	{
		std::cerr << "Unexpected EOF" << std::endl;
		exit(1);
	}
}

/**
 * Starts an interactive demo of the AVL tree.
 * The user can insert, remove, and search for values.
 */
void
interactive_demo()
{
	AVLTree<int> avl_tree;

	while (true)
	{
		std::cout << "insert <value> | remove <value> "
			"| has <value> | quit" << std::endl;
		std::cout << "> ";

		std::string operation;
		cin_or_exit(operation);

		if (operation == "quit")
		{
			break;
		}

		int val;
		cin_or_exit(val);

		if (operation == "insert")
		{
			avl_tree.insert(val);
		}
		else if (operation == "remove")
		{
			avl_tree.remove(val);
		}
		else if (operation == "has")
		{
			std::cout << (avl_tree.has(val) ? "true" : "false")
				<< std::endl;
		}
		else
		{
			std::cerr << "Unknown operation: " << operation
				<< std::endl;
		}

		std::cout << avl_tree << std::endl;
	}
}

/**
 * Shows the main menu of the program.
 * The user can choose to do a randomised test, an interactive demo,
 * or quit the program.
 */
void
show_menu()
{
	std::cout << "Make a choice:" << std::endl;
	std::cout << "1. Randomised test" << std::endl;
	std::cout << "2. Interactive demo" << std::endl;
	std::cout << "3. Quit" << std::endl;
	std::cout << "> ";

	int choice;
	cin_or_exit(choice);

	switch (choice)
	{
		case 1:
		{
			std::cout << "Enter size of the tree: ";
			size_t size;
			cin_or_exit(size);

			std::cout << "Enter minimum value to insert: ";
			int min;
			cin_or_exit(min);

			std::cout << "Enter maximum value to insert: ";
			int max;
			cin_or_exit(max);

			randomised_test(size, min, max);
			std::cout << "Test passed" << std::endl;

			break;
		}

		case 2:
		{
			interactive_demo();
			break;
		}

		case 3:
		{
			exit(0);
		}

		default:
		{
			std::cerr << "Unknown choice: " << choice << std::endl;
			break;
		}
	}
}

int
main()
{
	while (true)
	{
		show_menu();
	}
}