// vec.h
#pragma once
#include <type_traits>

class vector
{
private:
    bool gpu_enabled;
    int capacity;

    // CPU operator overloaded functions
    vector add_cpu(const vector *a, const vector *b) const;
    vector sub_cpu(const vector *a, const vector *b) const;
    vector dot_cpu(const vector *a, const vector *b) const;
    bool equivalent_cpu(const vector *a, const vector *b) const;

    // GPU operator overloaded functions
    vector add_gpu(const vector *a, const vector *b) const;
    vector sub_gpu(const vector *a, const vector *b) const;
    vector dot_gpu(const vector *a, const vector *b) const;
    bool equivalent_gpu(const vector *a, const vector *b) const;

public:
    int size;
    float *data;

    // Constructors
    // Constructor if no data array is given
    vector(int size = 0, bool gpu_enabled = false);
    // Constructor if flout pointer array is given
    vector(int size, float *input_data, bool gpu_enabled = false);
    // Constructor if general pointer array is given
    template <typename T>
    vector(int size, T *input_data, bool gpu_enabled = false);

    // Destructor
    ~vector();

    // Vector operator overloading
    vector operator+(const vector &b);
    vector operator-(const vector &b);
    vector operator*(const vector &b);
    vector operator/(const vector &b);
    vector operator/(const int &b);
    vector operator==(const vector &b);

    // Utility functions
    void append(float t);
    template <typename T>
    void append(T t);
    void resize(int new_size);
    void switch_mode();
};

// Constructer given a generic array type
template <typename T>
vector::vector(int size, T *input_data, bool gpu_enabled)
    : size(size), gpu_enabled(gpu_enabled), capacity(size)
{
    static_assert(std::is_arithmetic<T>::value, "Data must be numerical!");

    data = new float[capacity];
    if (input_data)
    {
        for (int i = 0; i < capacity; ++i)
        {
            data[i] = static_cast<float>(input_data[i]);
        }
    }
}


// Opereator overloaded functions
vector vector::operator+(const vector &b)
{
    if(gpu_enabled)
    {
        add_gpu(this, &b);
    } else 
    {
        add_cpu(this, &b);
    }
}

vector vector::operator+(const vector &b)
{
    if (gpu_enabled)
    {
        sub_gpu(this, &b);
    }
    else
    {
        sub_cpu(this, &b);
    }
}

vector vector::operator+(const vector &b)
{
    if (gpu_enabled)
    {
        dot_gpu(this, &b);
    }
    else
    {
        dot_cpu(this, &b);
    }
}

vector vector::operator==(const vector &b)
{
    if (gpu_enabled)
    {
        equivalent_gpu(this, &b);
    }
    else
    {
        equivalent_cpu(this, &b);
    }
}

// Utility functions
template <typename T>
void vector::append(T t) {
    static_assert(std::is_arithmetic<T>::value, "Input parameter must be numerical!");

    if(size >= capacity)
    {
        resize(capacity * 2);
    }
    data[size] = static_cast<float>(t);
    ++size;
}