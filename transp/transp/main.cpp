#include <iostream>
#include <fstream>
#include <chrono>

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
    
    vector<char> prealloc;
    prealloc.resize(1024*1024*256);
    for(size_t i = 0; i < prealloc.size(); ++i)
        prealloc[i] = 47;
    prealloc.~vector();
    
    for(size_t i = 0; i < (size_t) max_size; ++i)
    {
        size_t n = matrix_sizes[i];
        vector<uint32_t> data;
        data.resize(n*n);
        
        if(simulator)
        {
            std::cout << "N " << n << "\n";
            if(naive)
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
        else
        {
            using namespace std::chrono;
            high_resolution_clock::time_point start, end;
            
            if(naive)
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
            
            std::cout << n << " " << time_span.count() * 1000000000 / (n*n) << "\n";
        }
    }
    
}
