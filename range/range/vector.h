#ifndef DATA_STRUCTURES_SPLAY_VECTOR_H
#define DATA_STRUCTURES_SPLAY_VECTOR_H

#include <stdint.h>
#include "assert.h"
#include "memory.h"

namespace range
{

template<typename T>
class vector
{
    static constexpr size_t init_capacity = 8;
    T * data_;
    size_t size_;
    size_t capacity_;
public:
    
    vector() : data_(new T[init_capacity]), size_(0), capacity_(init_capacity) {}
    vector(const vector<T> & other) : data_(new T[other.size_]), capacity_(other.capacity_), size_(other.size_)
    {
        memcpy(data_, other.data_, size_ * sizeof(T));
    }
    vector(vector<T> && other)  : data_(new T[other.size_]), capacity_(other.capacity_), size_(other.size_)
    {
        other.data_ = nullptr;
    }
    
    void push_back(const T & item);
    void push_back(T && item);
    
    size_t size();
	size_t capacity();

    void reserve(size_t new_capacity);
    void resize(size_t new_size);
    void resize(size_t new_size, const T & init_val);
    
	void stretch_to_fit(size_t new_size, const T & init_val);

    void clear();
    
    T & back();
    
    T & operator[](size_t i);
    
    ~vector();
private:
    void check_full_and_reserve();
};

template<typename T>
void vector<T>::push_back(const T & item)
{
    check_full_and_reserve();
    data_[size_] = item;
    ++size_;
}

template<typename T>
void vector<T>::push_back(T && item)
{
    check_full_and_reserve();
    data_[size_] = std::move(item);
    ++size_;
}

template<typename T>
void vector<T>::check_full_and_reserve()
{
    if(size_ != capacity_)
        return;
    reserve(capacity_ * 2);
}

template<typename T>
void vector<T>::reserve(size_t new_capacity)
{
    if(new_capacity <= capacity_)
        return;
    capacity_ = new_capacity;
    T * tmp = new T[capacity_];
    memcpy(tmp, data_, size_*sizeof(T));
    delete[] data_;
    data_ = tmp;
}


template<typename T>
void vector<T>::resize(size_t new_size)
{
    reserve(new_size);
    
    size_ = new_size;
}


template<typename T>
void vector<T>::resize(size_t new_size, const T & init_val)
{
    reserve(new_size);
    
    for(size_t i = size_; i < new_size; ++i)
        data_[i] = init_val;
    
    size_ = new_size;
}

template<typename T>
void vector<T>::stretch_to_fit(size_t new_size, const T & init_val)
{
	while (new_size >= capacity_)
		reserve(capacity_ * 2);
	if (new_size >= size_)
		resize(new_size + 1, init_val);
}

template<typename T>
void vector<T>::clear()
{
    size_ = 0;
}

template<typename T>
size_t vector<T>::size()
{
    return size_;
}
template<typename T>
size_t vector<T>::capacity()
{
	return capacity_;
}

template<typename T>
T & vector<T>::back()
{
    assert(size_ > 0);
    return data_[size_ - 1];
}

template<typename T>
T & vector<T>::operator[](size_t i)
{
    assert(i >= 0);
    assert(i < size_);
    
    return data_[i];
}

template<typename T>
vector<T>::~vector()
{
    delete[] data_;
}


}

#endif