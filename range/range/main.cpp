#include <iostream>
#include <fstream>
#include <string>
#include <set>

#include <string.h>

#include "range_tree.h"

int main(int argc, char * * argv)
{   
	bool naive = false;

	if (argc <= 1)
	{
		std::cout << "Enter prefix for files\n";
		return 1;
	}
	size_t prefix_arg = 1;
	if (argc > 1 && strcmp(argv[1], "-n") == 0)
	{
		naive = true;
		++prefix_arg;
	}

	std::string prefix = argv[prefix_arg];


	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	/*char c;
	bool was = false;
	while (!std::cin.eof())
	{
		
		std::cin >> c;
		if (std::cin.eof())
			break;
		assert(std::cin.good());
		if (c == 'I')
		{
			std::cin >> id >> k;
			if (std::cin.eof())
				break;
			assert(std::cin.good());
			heap.insert(k, id);
		}
		else if (c == 'M')
		{
			heap.delete_min();
		}
		else if (c == 'D')
		{
			std::cin >> id >> k;
			if (std::cin.eof())
				break;
			heap.decrease(id, k);
		}
		else if (c == '#')
		{
			size_t n;
			std::cin >> n;
			if (was)
			{
				decrease_max << heap.decrease_max() << "\n";
				decrease_avg << heap.decrease_average() << "\n";
				delete_max << heap.delete_max() << "\n";
				delete_avg << heap.delete_average() << "\n";
				heap.clear();
			}
			std::cout << n << "\n";
			decrease_max << n << " ";
			decrease_avg << n << " ";
			delete_max << n << " ";
			delete_avg << n << " ";
			was = true;
		}
	}*/
	std::cout << "PROPER END\n";
	return 0;
}
