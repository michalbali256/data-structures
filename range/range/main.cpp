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

	std::vector<range::point> check_arr;

	char c;
	bool was = false;
	while (!std::cin.eof())
	{
		size_t n = 0;
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

			check_arr.push_back({ x,y });
		}
		else if (c == 'C')
		{
			range::data_t x1, y1, x2, y2;
			std::cin >> x1 >> y1 >> x2 >> y2;
			if (std::cin.eof())
				break;

			size_t count = 0;
			for (range::point p : check_arr)
			{
				if (p.x >= x1 && p.x <= x2 && p.y >= y1 && p.y <= y2)
					++count;
			}

			for (size_t i = 0; i < 3; ++i)
			{
				if (trees[i].range_count(x1, x2, y1, y2) != count)
				{
					std::cout << "WRONG " << n << "\n";
				}
				/*
				size_t ret = trees[i].range_count(x1, x2, y1, y2);
				assert(ret == count);*/
			}

			

		}
		else if (c == '#')
		{
			
			std::cin >> n;

			check_arr.reserve(n);

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

				check_arr.resize(0);
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
