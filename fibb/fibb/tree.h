#ifndef DATA_STRUCTURES_SPLAY_TREE_H
#define DATA_STRUCTURES_SPLAY_TREE_H

#include "common.h"
#include "vector.h"

namespace splay
{
    


class tree : public measurable_struct_iface
{
protected:
    struct node
    {
        node(key_t key) : key(key) {}
        key_t key;
        node * left = nullptr;
        node * right = nullptr;
        
        ~node();
    };
	enum class dir
	{
		L,
		R
	};
	struct path_node
	{
		node * n;
		dir d;
	};
    

    node * root_ = nullptr;
    
public:
    
    virtual void insert(key_t value) override;
    virtual void find(key_t value) override;
    
    void clear();
    
    ~tree();
protected:
    virtual double get_average_and_clear() override;
    virtual void splay() = 0;
    size_t locate(key_t key);
    vector<path_node> locate_path;
    
    /*
    //         A              B
    //        / \            / \  
    //       T1  B    ->    A  T3
    //          / \        / \   
    //         T2 T3      T1  T2
    // rotates right child of node A up
    */
    static node * rotate_left(node * a, node * b);
    
    /*
    //         A              B
    //        / \            / \ 
    //       B  T3    ->    T1  A
    //      / \                / \ 
    //     T1 T2              T2  T3
    // rotates left child of node a up
    */
    static node * rotate_right(node * a, node * b);
};


}

#endif