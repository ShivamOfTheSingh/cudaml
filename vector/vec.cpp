// vec.cpp
#include "vec.h"
#include <stdexcept>
#include <iostream>
#include <string>

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

// Constructor is float pointer array is given
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
vector vector::add_cpu(const vector *a, const vector *b) const
{
    if (a->size != b->size)
    {
        throw std::invalid_argument("Vectors must be the same size!");
    }
    vector c = vector(a->size);

    for (int i = 0; i < a->size; ++i)
    {
        c.data[i] = a->data[i] + b->data[i];
    }

    return c;
}

vector vector::sub_cpu(const vector *a, const vector *b) const
{
    if (a->size != b->size)
    {
        throw std::invalid_argument("Vectors must be the same size!");
    }
    vector c = vector(a->size);

    for (int i = 0; i < a->size; ++i)
    {
        c.data[i] = a->data[i] - b->data[i];
    }

    return c;
}

vector vector::dot_cpu(const vector *a, const vector *b) const
{
    if (a->size != b->size)
    {
        throw std::invalid_argument("Vectors must be the same size!");
    }
    int c = 0;

    for (int i = 0; i < a->size; ++i)
    {
        c += a->data[i] * b->data[i];
    }

    return c;
}

vector vector::div_cpu(const vector *a, const int b) const
{
    if (b == 0)
    {
        throw std::invalid_argument("Cannot divide by zero!");
    }
    int c = 0;

    for (int i = 0; i < a->size; ++i)
    {
        c += a->data[i] / b;
    }

    return c;
}

bool vector::equivalent_cpu(const vector *a, const vector *b) const
{
    if (a->size != b->size)
    {
        throw std::invalid_argument("Vectors must be the same size!");
    }

    for (int i = 0; i < a->size; ++i)
    {
        if (a->data[i] != b->data[i])
        {
            return false;
        }
    }

    return true;
}

// Utility functions
void vector::resize(int new_size)
{
    if(new_size <= capacity) return;

    int new_capacity = new_size;
    float *temp = new float[new_capacity];

    for (int i = 0; i < size; ++i)
    {
        temp[i] = data[i];
    }

    delete[] data;
    data = temp;
    capacity = new_capacity;
}

void vector::append(float t)
{
    if (size >= capacity)
    {
        resize(capacity * 2);
    }
    data[size] = t;
    ++size;
}

void vector::switch_mode()
{
    gpu_enabled = !gpu_enabled;
    std::string flair = gpu_enabled ? "GPU" : "CPU";
    std::cout << "Switched to " << flair << "mode\n";
}