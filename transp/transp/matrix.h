#ifndef DATA_STRUCTURES_TRANSP_MATRIX_H
#define DATA_STRUCTURES_TRANSP_MATRIX_H

#include "utility"

#include "vector.h"

namespace transp
{

class matrix
{
public:
	matrix(vector<uint32_t> * data, size_t n) : data_(data), n_(n){}
	
	void swap(size_t x1, size_t y1, size_t x2, size_t y2)
	{
		std::swap((*data_)[y1*n_ + x1], (*data_)[y2*n_ + x2]);
	}
	
	void transpose()
	{
		transpose(0,0, n_-1, n_-1);
	}
	
	void transpose(size_t x1, size_t y1, size_t x2, size_t y2)
	{
		size_t mx = x1 + (x2 - x1 + 1) / 2;
		size_t my = y1 + (y2 - y1 + 1) / 2;
		
		if(mx == x1 && my == y1) 
		{
			transpose_one(x1, y1);
			return;
		}
		
		transpose(x1, y1, mx, my);
		transpose(mx + 1, my + 1, x2, y2);
		transpose_and_swap(mx + 1, y1, x2, my);
	}
	
	void naive_transpose()
	{
		for(size_t i = 0; i < n_; ++i)
			for(size_t j = i+1; j < n_; ++j)
				transpose_one(i, j);
	}
	
	uint32_t & at(size_t x, size_t y)
	{
		return (*data_)[y*n_ + x];
	}
private:
	
	void transpose_one(size_t x, size_t y)
	{
		swap(x, y, y, x);
	}
	
	void transpose_and_swap(size_t x1, size_t y1, size_t x2, size_t y2)
	{
		size_t mx = x1 + (x2 - x1) / 2;
		size_t my = y1 + (y2 - y1) / 2;
		
		if(mx <= x1+1 || my <= y1+1)
		{
			transpose_one(x1, y1);
			if (mx == x1 && my == y1 + 1)
			{
				transpose_one(x1, y1 + 1);
			}
			else if (mx == x1 + 1 && my == y1)
			{
				transpose_one(x1 + 1, y1);
			}
			return;
		}
		
		transpose_and_swap(x1, y1, mx, my);
		transpose_and_swap(mx + 1, y1, x2, my);
		transpose_and_swap(x1, my +1, mx, y2);
		transpose_and_swap(mx + 1, my + 1, x2, y2);
	}
	
	
	
	vector<uint32_t> * data_;
	size_t n_;
};

}

#endif