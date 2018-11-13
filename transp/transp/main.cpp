#include <iostream>
#include <fstream>
#include <chrono>
#include <utility>
#include <cmath>

#include "matrix.h"
#include "matrix_sizes.h"

using namespace transp;

int main(int argc, char * * argv)
{   
    bool naive = false;
    bool simulator = false;
    int max_size = 100 - 54;
    for(size_t i = 1; i <(size_t) argc; ++i)
    {
        if(!strcmp(argv[i], "-n"))
            naive = true;
        else if(!strcmp(argv[i], "-s"))
            simulator = true;
        else if(!strcmp(argv[i], "-m"))
        {
            ++i;
            max_size = atoi(argv[i]) - 54;
        }
    }
    
	//start once to put system under load and avoid distortion of first values
	for (size_t k = 0; k < (size_t)max_size; ++k)
	{
		size_t n = matrix_sizes[k];
		vector<uint32_t> data;
		data.resize(n*n);
		
		matrix<noop_writer> m(&data, n);
		m.transpose();
	}
	
	if (simulator)
	{
		for (size_t k = 0; k < (size_t)max_size; ++k)
		{
			size_t n = matrix_sizes[k];
			vector<uint32_t> data;
			data.resize(n*n);
			std::cout << "N " << n << "\n";
			if (naive)
			{
				matrix<writer> m(&data, n);
				m.naive_transpose();
			}
			else
			{
				matrix<writer> m(&data, n);
				m.transpose();
			}
			std::cout << "E\n";
		}
	}
	else
	{
		size_t constexpr repeat_whole = 5;
		size_t constexpr repeat_one = 5;
		double measured[sizeof(matrix_sizes)][repeat_whole][repeat_one];
		

		for (size_t i = 0; i < repeat_whole; ++i)
		{
			for (size_t k = 0; k < (size_t)max_size; ++k)
			{
				for (size_t j = 0; j < repeat_one; ++j)
				{
					size_t n = matrix_sizes[k];
					vector<uint32_t> data;
					data.resize(n*n);
				
					using namespace std::chrono;
					high_resolution_clock::time_point start, end;

					if (naive)
					{
						matrix<noop_writer> m(&data, n);
						start = high_resolution_clock::now();
						m.naive_transpose();
						end = high_resolution_clock::now();
					}
					else
					{
						matrix<noop_writer> m(&data, n);
						start = high_resolution_clock::now();
						m.transpose();
						end = high_resolution_clock::now();
					}

					duration<double> time_span = duration_cast<duration<double>>(end - start);

					measured[k][i][j] = time_span.count() * 1000000000 / ((n*n - n) / 2);
					std::cerr << n << " " << time_span.count() * 1000000000 / ((n*n - n) / 2) << " ns" << "\n";
				}
			}
		}

		//std::cout << n << " " << time_span.count() * 1000000000 / (n*n) << "\n";
		//std::cerr << n << " " << time_span.count() * 1000000000 / (n*n) << " ns" << "\n";

		for (size_t k = 0; k < (size_t)max_size; ++k)
		{
			double sum = 0;
			double min = std::numeric_limits<double>::max();
			double max = 0;
			for (size_t i = 0; i < repeat_whole; ++i)
			{
				for (size_t j = 0; j < repeat_one; ++j)
				{
					sum += measured[k][i][j];
					if (measured[k][i][j] > max)
						max = measured[k][i][j];
					if (measured[k][i][j] < min)
						min = measured[k][i][j];
				}
			}
			double mean = sum / (repeat_one * repeat_whole);
			double sqsum = 0;
			for (size_t i = 0; i < repeat_whole; ++i)
			{
				for (size_t j = 0; j < repeat_one; ++j)
				{
					sqsum += (measured[k][i][j] - mean) * (measured[k][i][j] - mean);
				}
			}
			double var = sqsum / (repeat_one * repeat_whole);
			double s = sqrt(var);

			size_t n = matrix_sizes[k];

			std::cerr << "size: " << n << "\n";
			std::cerr << "    mean: " << mean << "\n";
			std::cerr << "    max:  " << max << "\n";
			std::cerr << "    min:  " << min << "\n";
			std::cerr << "    var:  " << var << "\n";
			std::cerr << "    s:    " << s << "\n";

			std::cout << n << " " << mean << "\n";

		}


	}
    
}
