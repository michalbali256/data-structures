#include <iostream>
#include <fstream>
#include <vector>

#include "range_tree.h"

int main(int argc, char * * argv)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	double alphas[3] = { 0.52, 0.7, 0.97 };

	std::vector<range::range_tree> trees;
	for(size_t i = 0; i < 3; ++i)
		trees.push_back(range::range_tree(alphas[i]));

	char c;
	bool was = false;
	while (!std::cin.eof())
	{
		
		std::cin >> c;
		if (std::cin.eof())
			break;
		assert(std::cin.good());
		if (c == 'I')
		{
			range::data_t x, y;
			std::cin >> x >> y;
			if (std::cin.eof())
				break;
			assert(std::cin.good());
			for (size_t i = 0; i < 3; ++i)
				trees[i].insert(x, y);
		}
		else if (c == 'C')
		{
			range::data_t x1, y1, x2, y2;
			std::cin >> x1 >> y1 >> x2 >> y2;
			if (std::cin.eof())
				break;
			for (size_t i = 0; i < 3; ++i)
				trees[i].range_count(x1, x2, y1, y2);
		}
		else if (c == '#')
		{
			size_t n;
			std::cin >> n;
			if (was)
			{
				for (size_t i = 0; i < 3; ++i)
					std::cout << trees[i].insert_avg() << " ";
				for (size_t i = 0; i < 3; ++i)
					std::cout << trees[i].insert_max() << " ";
				for (size_t i = 0; i < 3; ++i)
					std::cout << trees[i].count_avg() << " ";
				for (size_t i = 0; i < 3; ++i)
					std::cout << trees[i].count_max() << " ";
				
				std::cout << "\n";

				for (size_t i = 0; i < 3; ++i)
					trees[i].clear();
			}
			std::cout << n << " ";
			was = true;
		}
	}
	for (size_t i = 0; i < 3; ++i)
		std::cout << trees[i].insert_avg() << " ";
	for (size_t i = 0; i < 3; ++i)
		std::cout << trees[i].insert_max() << " ";
	for (size_t i = 0; i < 3; ++i)
		std::cout << trees[i].count_avg() << " ";
	for (size_t i = 0; i < 3; ++i)
		std::cout << trees[i].count_max() << " ";

	std::cout << "\n";

	return 0;
}
