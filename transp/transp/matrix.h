#ifndef DATA_STRUCTURES_TRANSP_MATRIX_H
#define DATA_STRUCTURES_TRANSP_MATRIX_H

#include "utility"

#include "vector.h"



namespace transp
{

class writer
{
public:
	static void log_swap(size_t x1, size_t y1, size_t x2, size_t y2)
	{
		std::cout << "X " << y1 << " " << x1 << " " << y2 << " " << x2 << "\n";
	}
};

class noop_writer
{
public:
	static void log_swap(size_t, size_t, size_t, size_t){}
};

template<class w>
class matrix
{
public:
	matrix(vector<uint32_t> * data, size_t n) : data_(data), n_(n){}
	
	void swap(size_t x1, size_t y1, size_t x2, size_t y2)
	{
		w::log_swap(x1, y1, x2, y2);
		std::swap((*data_)[y1*n_ + x1], (*data_)[y2*n_ + x2]);
	}
	
	void transpose()
	{
		transpose(0,0, n_);
	}
	
	void transpose(size_t x1, size_t y1, size_t n)
	{
		size_t mx = n / 2;
		
		if(n == 1) 
		{
			//transpose_one(x1, y1);
			return;
		}
		
		//A|B
		//-+-
		//C|D
		transpose(x1, y1, mx);							//A
		transpose_and_swap(x1 + mx, y1, n - mx, mx);    //B
		transpose(x1 + mx, y1 + mx, n - mx);            //D
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
	
	void transpose_and_swap(size_t x1, size_t y1, size_t n, size_t m)
	{
		size_t mx = n / 2;
		size_t my = m / 2;
		
		if(n == 1 || m == 1)
		{
			transpose_one(x1, y1);
			if (n == 2 || m == 2)
				transpose_one(x1 + n - 1, y1 + m - 1);
			return;
		}

		//A|B
		//-+-
		//C|D
		transpose_and_swap(x1, y1, mx, my);                   //A
		transpose_and_swap(x1 + mx, y1, n - mx, my);          //B
		transpose_and_swap(x1, y1 + my, mx, m - my);          //C
		transpose_and_swap(x1 + mx, y1 + my, n - mx, m - my); //D
	}
	
	vector<uint32_t> * data_;
	size_t n_;
};

}

#endif