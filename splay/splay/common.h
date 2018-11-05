#ifndef DATA_STRUCTURES_SPLAY_COMMON_H
#define DATA_STRUCTURES_SPLAY_COMMON_H

#include <cstdint>
#include <assert.h>

#include "vector.h"

namespace splay {

using key_t = size_t;

class struct_iface
{
public:
    virtual void insert(key_t value) = 0;
    virtual void find(key_t value) = 0;
};

class measurable
{
public:
    void add_stat(size_t steps)
    {
        stats.push_back(steps);
    }
    virtual double get_average_and_clear() = 0;
    
protected:
    vector<size_t> stats;
};

class measurable_struct_iface : public struct_iface, public measurable
{

};

}

#endif
