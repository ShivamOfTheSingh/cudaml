// vec.cpp
#include "vec.h"

// Constructor if data is not given
vector::vector(int size, bool gpu_enabled)
    : size(size), gpu_enabled(gpu_enabled), capacity(size)
{
    data = new float[capacity];
    for (int i = 0; i < capacity; ++i)
    {
        data[i] = 0.0f;
    }
}


// Constructor is flout pointer array is given
vector::vector(int size, float *input_data, bool gpu_enabled)
    : size(size), gpu_enabled(gpu_enabled), capacity(size)
{
    data = new float[capacity];
    if (input_data)
    {
        for (int i = 0; i < capacity; ++i)
        {
            data[i] = input_data[i];
        }
    }
}

// Destructor
vector::~vector()
{
    delete[] data;
}

// Vector operator overloading
vector operator+(const vector &b)
{

}

vector operator-(const vector &b)
{

}

vector operator*(const vector &b)
{

}

// Getter Functions
int vector::get_size() const
{
    return size;
}
