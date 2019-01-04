#include "bba_tree.h"
#include "node.h"
#include "vector.h"
#include "assert.h"

namespace range
{

void rebuild_nodes(const vector<node *> & nodes, node *& parent_child_ref, size_t begin, size_t end)
{
	if (begin == end)
	{
		parent_child_ref = nullptr;
		return;
	}
	
	if (end - begin == 1)
	{
		parent_child_ref = nodes[begin];
		nodes[begin]->left = nullptr;
		nodes[begin]->right = nullptr;
		nodes[begin]->size = 1;
		nodes[begin]->rebuild(nodes, begin, end);
		return;
	}
	size_t mid = (begin + end) / 2;

	parent_child_ref = nodes[mid];
	nodes[mid]->size = end - begin;
	nodes[mid]->rebuild(nodes, begin, end);
	rebuild_nodes(nodes, nodes[mid]->left, begin, mid);
	rebuild_nodes(nodes, nodes[mid]->right, mid + 1, end);
}

void bba_tree::rebuild(node *& to_rebuild)
{
	assert(to_rebuild);
	//now take all child points, put them into array
	vector<node *> sorted;
	sorted.reserve(to_rebuild->size);
	vector<node *> r_stack;
	node * n = to_rebuild;

	while (n != nullptr || r_stack.size() > 0)
	{
		/* Reach the left most Node of the
		   curr Node */
		while (n != nullptr)
		{
			/* place pointer to a tree node on
			   the stack before traversing
			  the node's left subtree */
			r_stack.push_back(n);
			n = n->left;
		}

		/* Current must be NULL at this point */
		n = r_stack.pop_back();

		sorted.push_back(n);

		/* we have visited the node and its
		   left subtree.  Now, it's right
		   subtree's turn */
		n = n->right;

	} /* end of while */

	assert(sorted.size() == to_rebuild->size);
	rebuild_nodes(sorted, to_rebuild, 0, sorted.size());
}

bool bba_tree::check_bba_invariant(node * n)
{
	assert(n);
	size_t l_size, r_size;

	if (n->left)
		l_size = n->left->size;
	else
		l_size = 0;
	if (n->right)
		r_size = n->right->size;
	else
		r_size = 0;
	if (l_size - r_size == 1 || r_size - l_size == 1)
		return true;

	if (n->size * alpha_ < l_size || n->size * alpha_ < r_size)
		return false;
	
	return true;
}

node *& next_child(node * n, node * p)
{
	if (p->key > n->key)
	{
		return n->right;
	}
	else
	{
		return n->left;
	}
}

void set_inserted_node(node * n)
{
	n->left = nullptr;
	n->right = nullptr;
	n->size = 1;
	n->insert(n->data);
}


void bba_tree::insert(node * p)
{
    if(root_ == nullptr)
    {
        root_ = p;
		set_inserted_node(p);
        return;
    }
    
	node ** parent = &root_;
	node ** child = &next_child(*parent, p);
	
	(*parent)->insert(p->data);
	++(*parent)->size;

	node ** rebuild_root = &root_;
	
	bool do_rebuild = false;


    while(*child)
    {
		
		(*child)->insert(p->data);
		++(*child)->size;
		
		if (!do_rebuild && !check_bba_invariant(*parent))
		{
			do_rebuild = true;
			rebuild_root = parent;
		}


        parent = child;
		child = &next_child(*parent, p);
    }

	*child = p;
	set_inserted_node(*child);
	//no need to check invariant, changed size from 0 to 1

	if (do_rebuild)
		rebuild(*rebuild_root);
}

void bba_tree::clear()
{
	delete root_;
	root_ = nullptr;
	//rework to non recursive deallocation
}

void bba_tree::build_from_sorted(vector<node *> & nodes)
{
	rebuild_nodes(nodes, root_, 0, nodes.size());
}

bba_tree::~bba_tree()
{
	clear();
}

    

}