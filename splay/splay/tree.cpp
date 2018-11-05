
#include <iostream>
#include "stdlib.h"

#include "tree.h"
namespace splay
{

void tree::insert(key_t value)
{
    size_t closest = locate(value);
    
    if (locate_path.size())
    {
        locate_path.resize(closest + 1);
		splay();
		assert(value != root_->key);
        if(value < root_->key)
        {
            /*
			//        R            R
			//       / \    ->    / \ 
			//      T1 T2        X  T2
			//                  /
			//                 T1
            */
			node * t1 = root_->left;
			root_->left = new node(value);
			root_->left->left = t1;
        }
        else
        {
            /*
			//        R            R
			//       / \    ->    / \ 
			//      T1 T2        T1  X
			//                        \ 
			//                        T2
            */
			node * t2 = root_->right;
			root_->right = new node(value);
			root_->right->right = t2;
        }
    }
    else
    {
        root_ = new node(value);
    }
}
void tree::find(key_t value)
{
    locate(value);
    assert(locate_path.size() > 0);
    assert(locate_path.back().n->key == value);
    if(locate_path.size() == 0 || locate_path.back().n->key != value)
    {
        std::cout << "finding a value that is not in the tree!\n";
        throw new std::exception;
    }
    add_stat(locate_path.size());
    
    splay();
}
    
double tree::get_average_and_clear()
{
	uint64_t sum = 0;
    for(size_t i = 0; i < stats.size(); ++i)
        sum += stats[i];
    
    double average = (double) sum / stats.size();
    //meybe also other averages or histogram?
    
    clear();
    stats.clear();
    
    return average;
}

void tree::clear()
{
	vector<node *> stack;
	stack.push_back(root_);
	while (stack.size() != 0)
	{
		node * n = stack.back();
		if (n->left)
		{
			stack.push_back(n->left);
			n->left = nullptr;
		}
		else if (n->right)
		{
			stack.push_back(n->right);
			n->right = nullptr;
		}
		else
		{
			delete n;
			stack.resize(stack.size() - 1);
		}
	}

    root_ = nullptr;
}

tree::node::~node()
{
	assert(!left);
	assert(!right);
	delete left;
	delete right;
}

tree::~tree()
{
    clear();
}

template<typename T>
T dist(T a, T b)
{
    if (a > b)
        return a - b;
    else
        return b - a;
}

size_t tree::locate(key_t key)
{
    locate_path.clear();
    
    if(!root_)
        return 0;
    
    node * n = root_;
    key_t min = dist(n->key, key);
    size_t imin = 0;
    
    while(n != nullptr && n->key != key)
    {
        auto d = dist(n->key, key);
        if(d < min)
        {
            imin = locate_path.size();
            min = d;
        }
        
		if (key < n->key)
		{
			locate_path.push_back({ n, dir::L });
			n = n->left;
		}
		else
		{
			locate_path.push_back({ n, dir::R });
			n = n->right;
		}
        
            
    }
    
    if(n != nullptr && n->key == key)
    {
        locate_path.push_back({ n, dir::L });
        if(dist(n->key, key) < min)
        {
            imin = locate_path.size() - 1;
            min = n->key - key;
        }
    }
        
    
    return imin;
}

/*
//         A              B
//        / \            / \ 
//       T1  B    ->    A  T3
//          / \        / \ 
//         T2 T3      T1  T2
// rotates right child of node A up
*/
tree::node * tree::rotate_left(node * a, node * b)
{
    assert(a);
    node * t2;
    //b = a->right;
    assert(b);
    t2 = b->left;
    
    b->left = a;
    a->right = t2;
    
    return b;
}
/*
//         A              B
//        / \            / \ 
//       B  T3    ->    T1  A
//      / \                / \ 
//     T1 T2              T2  T3
// rotates left child of node a up
*/
tree::node * tree::rotate_right(node * a, node * b)
{
    assert(a);
    node * t2;
    //b = a->left;
    assert(b);
    t2 = b->right;
    
    b->right = a;
    a->left = t2;
    
    return b;
}


}