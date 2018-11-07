#include <iostream>
#include <fstream>

#include "vector.h"
#include "matrix.h"

using namespace transp;



int main(int argc, char * * argv)
{   
    vector<uint32_t> data;
    
    size_t n = 5;
    
    data.resize(n*n);
    for(int i = 0; i < data.size(); ++i)
    {
        data[i] = i;
    }
    
    matrix m(&data, n);
    
    for(int i = 0; i < n; ++i)
    {
        
        for(size_t j = 0; j < n; j++)
        {
            std::cout << m.at(j, i) << " ";
        }
        std::cout << "\n";
    }
    
    m.transpose();
    
    for(int i = 0; i < n; ++i)
    {
        for(size_t j = 0; j < n; j++)
        {
            std::cout << m.at(j, i) << " ";
        }
        std::cout << "\n";
    }
    
}
