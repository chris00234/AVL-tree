#include <iostream>
#include "MyAVLTree.hpp"
#include "runtimeexcept.hpp"
#include <string>
#include <cassert>

int main()
{
	MyAVLTree<int, std::string> tree;
	tree.insert(1, "foo");
	tree.insert(2, "foo");
	tree.insert(3, "foo");
	tree.insert(12, "foo");
	tree.insert(9, "foo");

	std::vector<int> trav = tree.preOrder();
	for (int i = 0; i < trav.size(); i++)
	{
		std::cout << trav[i] << std::endl;
	}
	/*std::vector<int> expected = { 1,2,3 };
	assert(trav == expected);*/

}