#include <iostream>
#include <cassert>
#include <stdarg.h>
#include <typeinfo>

template <typename T, size_t N>
class MultipliGrid final
{
public:
    using value_type = T;
    using size_type = size_t;

private:
    T *data = nullptr;
    size_type spaces[N];
    long len;

public:
    MultipliGrid() : len(0)
    {
        for (size_t i = 0; i < N; ++i)
        {
            spaces[i] = 0;
        }
    }

    MultipliGrid(T *point, size_type arr[])
    {
        len = 1;
        for (size_t i = 0; i < N; ++i)
        {
            spaces[i] = arr[i];
            len = len * arr[i];
        }
        data = new T[len];
        for (long i = 0; i < len; ++i)
        {
            *(data + i) = *(point + i);
        }
    }

    void too(int i, value_type first)
    {
        data = new T[len];
        for (long i = 0; i < len; i++)
        {
            *(data + i) = first;
        }
    }

    template <typename First, typename... Args>
    void too(int i, First first, Args... args)
    {
        spaces[i] = first;
        len = len * first;
        too(++i, args...);
    }

    template <typename... Args>
    MultipliGrid(Args... args)
    {
        len = 1;
        too(0, args...);
    }

    T foo(int i, T *point) const
    {
        return *point;
    }

    template <typename First, typename... Args>
    T foo(int i, T *point, First first, Args... args) const
    {
        size_type mass = 1;
        for (size_type j = 1 + i; j < N; j++)
        {
            mass = mass * spaces[j];
        }
        return foo(++i, (point + mass * first), args...);
    }

    template <typename... Args>
    T operator()(Args... args) const
    {
        T *point = data;
        return foo(0, point, args...);
    }

    MultipliGrid<T, N - 1> operator[](size_type idx) const
    {
        T *newdata = data + idx * (len / spaces[0]);
        size_type newarr[N - 1];
        for (size_type i = 1; i < N; i++)
        {
            newarr[i - 1] = spaces[i];
        }
        T newvalue[len / spaces[0]];
        for (unsigned long i = 0; i < (len / spaces[0]); i++)
        {
            newvalue[i] = *(newdata + i);
        }
        return MultipliGrid<value_type, N - 1>(newvalue, newarr);
    }

    void print()
    {
        for (long i = 0; i < len; ++i)
        {
            std::cout << *(data + i) << "    ";
        }
        std::cout << '\n';
    }

    MultipliGrid<T, N> &operator=(MultipliGrid<T, N> const &x)
    {
        std::cout << "oper copy" << '\n';
        if (&x == this)
            return *this;
        delete[] data;
        for (size_type i = 0; i < N; i++)
        {
            spaces[i] = x.spaces[i];
        }
        len = x.len;
        data = new T[len];
        for (long i = 0; i < len; i++)
        {
            *(data + i) = *(x.data + i);
        }

        return *this;
    }

    MultipliGrid<T, N> &operator=(MultipliGrid<T, N> &&x)
    {
        if (&x == this)
            return *this;
        delete[] data;
        data = x.data;
        x.data = nullptr;
        for (size_type i = 0; i < N; i++)
        {
            spaces[i] = x.spaces[i];
        }
        len = x.len;

        return *this;
    }

    MultipliGrid(MultipliGrid<T, N> const &x)
    {
        len = x.len;
        data = new T[len];
        for (long i = 0; i < len; i++)
        {
            *(data + i) = *(x.data + i);
        }
        for (size_type i = 0; i < N; i++)
        {
            spaces[i] = x.spaces[i];
        }
    }

    MultipliGrid(MultipliGrid<T, N> &&x) : data(x.data), len(x.len)
    {
        x.data = nullptr;
        for (size_type i = 0; i < N; i++)
        {
            spaces[i] = x.spaces[i];
        }
    }

    ~MultipliGrid()
    {
        delete[] data;
        data = nullptr;
    }
};

int main()
{
    MultipliGrid<float, 3> f3(2, 3, 4, 2.0f);
    // assert(1.0f == f3(1, 1, 1));
    float arr1[9] = {1, 2, 3, 4, 5, 6, 7, 8};
    size_t arr2[3] = {2, 2, 2};
    MultipliGrid<float, 3> f2(arr1, arr2);
    MultipliGrid<float, 2> f1;
    f1 = f2[1];

    MultipliGrid<float, 3> const g3(2, 3, 4, 1.0f);
    assert(1.0f == g3(1, 1, 1));

    MultipliGrid<float, 2> g2(2, 5, 2.0f);
    assert(2.0f == g2(1, 1));

    g2 = g3[1];
    assert(1.0f == g2(1, 1));

    return 0;
}
