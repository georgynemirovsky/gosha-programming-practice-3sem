#include <iostream>

struct base_exception {
    virtual void what() = 0;
};

struct no_top_element final: base_exception {
    void what() override {
        std::cout << "There will be no top element, go home." << '\n';
    }
};

struct no_element final: base_exception {
    void what() override {
        std::cout << "I won't delete it, everything is empty here anyway" << '\n';
    }
};

struct no_element_with_this_index final: base_exception {
    void what() override {
        std::cout << "There is no element with this index" << '\n';
    }
};

template <typename T>
class Vector {
  public:
    Vector(): size(1), buffer(new T) {};

    Vector(Vector const& vec): size(vec.size) {
        buffer = new T[size];
        for (size_t i = 0; i < size; i++) {
            buffer[i] = vec.buffer[i];
        }
    }

    Vector(Vector&& vec) noexcept:size(vec.size), buffer(vec.buffer) {
        vec.size = 0;
        vec.buffer = nullptr;
    }

    void push_back(const T& value) {
        if (size < max_size) {
            buffer[size] = value;
            size++;
        } else {
            add_memory();
            buffer[size] = value;
            size++;
        }
    }

    T& top() {
        if (size == 0) {
            throw no_top_element();
        }
        return buffer[size - 1];
    }

    void pop() {
        if (size == 0) {
            throw no_element();
        }
        delete buffer[size - 1];
        size--;
    }

    bool is_empty() const {
        return (size == 0);
    }

    size_t capacity() const {
        return max_size;
    }

    T& at(size_t index){
        if (index < 0 || index >= size) {
            throw no_element_with_this_index();
        }
        return buffer[index];
    }

    T& operator[](size_t index) {
        return buffer[index];
    }

    const T& operator[](size_t index) const {
        return buffer[index];
    }

    ~Vector() {
        delete [] buffer;
        size = 0;
        max_size = 0;
        buffer = nullptr;
    }

  private:
    size_t size = 0;
    T* buffer = nullptr;
    size_t max_size = 0;

    void add_memory() {
        max_size = max_size * 2;
        T* tmp_buffer = buffer;
        buffer = new T[max_size];
        for (size_t i = 0; i < size; i++) {
            buffer = tmp_buffer;
        }
        delete [] tmp_buffer;
        tmp_buffer = nullptr;
    }

};

int main() {
    Vector<int> v;
    return 0;
}
