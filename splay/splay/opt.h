#ifndef DATA_STRUCTURES_SPLAY_OPT_OPT_H
#define DATA_STRUCTURES_SPLAY_OPT_OPT_H

#include "common.h"
namespace splay
{

class opt : public measurable_struct_iface
{
    
    vector<size_t> counts;
public:
    
    opt():counts(){}
    
    virtual void insert(key_t value) override
    {
        (void)value;
    };
    virtual void find(key_t value) override
    {
        if(value >= counts.size())
            counts.resize(value+1, 0);
        ++counts[value];
    };
    
    
    using cost_t = uint_fast64_t;
    static constexpr cost_t COST_MAX = INT_FAST64_MAX;
    struct cost_root
    {
        cost_t cost = 0;
        key_t root = 0;
    };
    
    
    virtual double get_average_and_clear() override
    {
        compute_sums();
        
        vector<vector<cost_root>> roots;
        
        size_t n = counts.size();
        roots.resize(counts.size());
        for(size_t i = 0; i < roots.size(); ++i)
            roots[i].resize(counts.size());
        
        
        for(key_t i = 1; i < n; ++i)
        {
            roots[i][i].cost = counts[i];
            roots[i][i].root = i;
        }
        
        for(key_t k = 2; k < n; ++k)
        {
            for(key_t i = 1; i <= n-k; ++i)
            {
                key_t j = i+k-1;
                roots[i][j].cost = COST_MAX;
                
                
                for(key_t r = roots[i][j-1].root; r <= roots[i+1][j].root; ++r)
                {
                    cost_t c = ( r > i ? roots[i][r-1].cost : 0) +  
                        ( r < j ? roots[r+1][j].cost : 0) +  
                        sum(i, j);
                    
                    if (roots[i][j].cost > c)
                    {
                        roots[i][j].cost = c;
                        roots[i][j].root = r;
                    }
                }
            }
        }
        counts.clear();
        
        return roots[1][n-1].cost /((double) sum(0, n-1));
    }
    
private:
    
    vector<cost_t> sums;
    
    void compute_sums()
    {
        sums.resize(counts.size()+1);
        
        cost_t sum = 0;
        for(size_t i = 0; i < counts.size(); ++i)
        {
            sums[i] = sum;
            sum += counts[i];
        }
        sums[counts.size()] = sum;
        
    }
    
    cost_t sum(key_t i, key_t j)
    {
        assert(i < sums.size());
        assert(j+1 < sums.size());
        return sums[j+1] - sums[i];
    }
};

}
#endif
