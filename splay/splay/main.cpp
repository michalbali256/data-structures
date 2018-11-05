#include <iostream>
#include <fstream>
#include "common.h"
#include "opt.h"
#include "naive_tree.h"
#include "splay_tree.h"
using namespace splay;

void load_input(std::istream & in, measurable_struct_iface & str)
{
    char c;
    splay::key_t k;
    bool was = false;
    while(!in.eof())
    {
		//fscanf_s(in.f "%c %d\n", c, sizeof(c), k);
        in >> c >> k;
    
        if(c == 'I')
        {
            str.insert(k);
        }
        else if(c == 'F')
        {
            str.find(k);
        }
        else if(c == '#')
        {
            
            if(was)
                std::cout << str.get_average_and_clear() << "\n";
            std::cout << k << " ";
            was = true;
        }
    }
    std::cout << str.get_average_and_clear() << "\n";
}

int main(int argc, char * * argv)
{   
    std::istream * in = &std::cin;
    
    measurable_struct_iface * str = nullptr;
    
    for(size_t i = 1; i < (size_t)argc; ++i)
    {
        if(!strcmp(argv[i], "-o"))
            str = new opt;
        else if (!strcmp(argv[i], "-n"))
            str = new naive_tree;
        else if (!strcmp(argv[i], "-s"))
            str = new splay_tree;
        else
        {
            std::fstream * fin = new std::fstream;
            fin->open(argv[i]);
            in = fin;
        }
        
    }
    
    load_input(*in, *str);
}
