#include <iostream>
#include <cassert>
#include <stdarg.h>
#include <typeinfo>

template <typename T>
class Grid final
{
public:
    using value_type = T;
    using size_type = unsigned;
    Grid(T *data, size_type y_size, size_type x_size) : data(data), y_size(y_size), x_size(x_size) {}

    Grid(T const &t) : data(new T[1]), x_size(1), y_size(1)
    {
        *data = t;
    }

    Grid(size_type y_size, size_type x_size) : data(new T[y_size * x_size]), y_size(y_size), x_size(x_size)
    {
    }

    Grid(size_type y_size, size_type x_size, T const &t) : data(new T[y_size * x_size]), y_size(y_size), x_size(x_size)
    {
        for (unsigned i = 0; i < y_size * x_size; ++i)
        {
            data[i] = t;
        }
    }

    T operator()(size_type y_idx, size_type x_idx) const
    {
        return data[y_idx * x_size + x_idx];
    }

    T &operator()(size_type y_idx, size_type x_idx)
    {
        return data[y_idx * x_size + x_idx];
    }

    Grid<T> &operator=(T const &t)
    {
        for (auto it = data; it != data + x_size * y_size; ++it)
            *it = t;
        return *this;
    }

    size_type get_y_size() const { return y_size; }

    size_type get_x_size() const { return x_size; }

    T *operator[](size_type y_idx)
    {
        return data + y_idx * x_size;
    }

    void print()
    {
        for (unsigned i = 0; i < x_size * y_size; ++i)
        {
            std::cout << *(data + i) << "    ";
        }
    }

    Grid(Grid<T> const &x) : data(new T[x.y_size * x.x_size])
    {
        y_size = x.y_size;
        x_size = x.x_size;
        for (unsigned i = 0; i < y_size * x_size; ++i)
        {
            *(data + i) = *(x.data + i);
        }
    }

    Grid(Grid<T> &&x) : data(x.data), x_size(x.x_size), y_size(x.y_size)
    {
        delete [] x.data;
        x.data = nullptr;
        x.y_size = 0;
        x.x_size = 0;
    }

    Grid<T> &operator=(Grid<T> &x)
    {
        if (&x == this)
            return *this;
        delete[] data;
        y_size = x.y_size;
        x_size = x.x_size;
        data = new T[y_size * x_size];
        for (unsigned i = 0; i < y_size * x_size; ++i)
        {
            *(data + i) = *(x.data + i);
        }

        return *this;
    }

    Grid<T> &operator=(Grid<T> &&x)
    {
        if (&x == this)
            return *this;
        delete[] data;
        data = x.data;
        x.data = nullptr;
        y_size = x.y_size;
        x_size = x.x_size;
        x.y_size = 0;
        x.x_size = 0;

        return *this;
    }

    ~Grid()
    {
        delete[] data;
        data = nullptr;
    }

private:
    T *data;
    size_type y_size, x_size;
};


int main()
{
    Grid<float> g(3, 2, 0.0f);
    assert(3 == g.get_y_size());
    assert(2 == g.get_x_size());

    using gsize_t = Grid<int>::size_type;

    for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
        for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
            assert(0.0f == g[y_idx][x_idx]);

    for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
        for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
            g[y_idx][x_idx] = 1.0f;

    for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
        for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
            assert(1.0f == g(y_idx, x_idx));

    g.print();
    return 0;
}
