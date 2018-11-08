#include <iostream>
#include <fstream>

#include "vector.h"
#include "matrix.h"

using namespace transp;



int main(int argc, char * * argv)
{   
    vector<uint32_t> data;
	vector<uint32_t> check;
	for (size_t n = 5; n < 1000; ++n)
	{
		std::cout << n << "\n";
		data.resize(n*n);
		check.resize(n*n);
		for (int i = 0; i < data.size(); ++i)
		{
			data[i] = i;
			check[i] = i;
		}

		matrix mt(&data, n);
		mt.transpose();

		matrix mtn(&check, n);
		mtn.naive_transpose();

		for (size_t i = 0; i < n*n; ++i)
		{
			if (check[i] != data[i])
				std::cout << "error" << "\n";
		}

		/*for(int i = 0; i < n; ++i)
		{

			for(size_t j = 0; j < n; j++)
			{
				std::cout << m.at(j, i) << " ";
			}
			std::cout << "\n";
		}*/

		
	}

}
