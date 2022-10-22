#include <iostream>

template <typename T>
class unique_ptr {
  public:
    explicit unique_ptr(T* ptr): ptr(ptr) { }

    unique_ptr(unique_ptr&& other): ptr(other.ptr)
    {
        other.ptr = nullptr;
    }

    unique_ptr(unique_ptr& other) = delete;

    unique_ptr& operator=(unique_ptr&& other)
    {
        if (&other == this)
        {
            return *this;
        }
        delete [] ptr;
        ptr = other.ptr;
        other.ptr = nullptr;
        return *this;
    }

    unique_ptr& operator=(unique_ptr& other) = delete;

    T& operator*() const
    {
        return *ptr;
    }

    T* operator->() const
    {
        return ptr;
    }

    ~unique_ptr()
    {
        delete [] ptr;
        ptr = nullptr;
    }

  private:
    T* ptr = nullptr;
};

template <typename T>
class shared_ptr
{
public:
    explicit shared_ptr(T* ptr): cptr(ptr) { }
    shared_ptr(shared_ptr& other): cptr(other.ptr)
    {
        cptr->counter++;
    }
    shared_ptr(shared_ptr&& other)
    {

    }
    shared_ptr& operator=(shared_ptr& other)
    {

    }
    shared_ptr& operator=(shared_ptr&& other)
    {

    }
    ~shared_ptr()
    {

    }
private:
    template <typename U>
    struct ControlBlcok
    {
        ControlBlock(U* object): object(object), counter(1) { }

        ~ControlBlcok()
        {
            delete counter;
            delete object;
        }

        size_t counter = 0;
        U object;
    };

    ControlBlcok<T*> cptr = nullptr;

    template <typename U, typename... Args>
    friend shared_ptr<U> make_shared(Args&&... args);
};


template <typename U, typename... Args>
shared_ptr<U> make_shared(Args&&... args)
{
    auto ptr = new U(std::forward<Args>(args)...);
    return shared_ptr<U>(ptr);
}

int main ()
{
    int n = 10;
    unique_ptr<int> ptr_1(&n);

    unique_ptr<int> ptr_2(std::move(ptr_1));

    unique_ptr<int> ptr_3(&n);

    ptr_2 = std::move(ptr_3);
    return 0;
}
