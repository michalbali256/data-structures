#include "range_tree.h"

namespace range
{

void range_tree::insert(data_t x, data_t y)
{
	size_t steps = 0;
	x_tree.insert(new x_node({x, y}, alpha_), steps);

	if (steps > insert_max_)
		insert_max_ = steps;
	++insert_count_;
	insert_steps_ += steps;
}

size_t range_tree::range_count(data_t x_begin, data_t x_end, data_t y_begin, data_t y_end)
{
	size_t steps = 0;
	size_t count = x_tree.range_count(x_begin, x_end, y_begin, y_end, steps);

	if (steps > count_max_)
		count_max_ = steps;
	++count_count_;
	count_steps_ += steps;

	return count;
}

double range_tree::insert_avg()
{
	return (double)insert_steps_ / insert_count_;
}

uint64_t range_tree::insert_max()
{
	return insert_max_;
}

double range_tree::count_avg()
{
	return (double)count_steps_ / count_count_;
}

uint64_t range_tree::count_max()
{
	return count_max_;
}

void range_tree::clear()
{
	x_tree.clear();

	insert_steps_ = 0;
	insert_count_ = 0;
	insert_max_ = 0;

	count_steps_ = 0;
	count_count_ = 0;
	count_max_ = 0;
}

}