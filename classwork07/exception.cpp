#include <iostream>
#include <cmath>
#include <cstring>

struct base_exception {
    virtual void what() = 0;
};

struct math_exception final: base_exception {
    void what() override {
        std::cout << "math exception" << '\n';
    }
};

struct invalid_argument final: base_exception {
    void what() override {
        std::cout << "invalid argument" << '\n';
    }
};

double inverse(double x) {
  if (x == 0)
    throw math_exception();
  return 1. / x;
}

double root(double x) {
  if (x < 0)
    throw invalid_argument();
  return std::sqrt(x);
}

int main() {
    try {
        inverse(0);
    } catch (math_exception &exception) {
        exception.what();
    }
    try {
        root(-1);
    } catch (invalid_argument &exception) {
        exception.what();
    }
    return 0;
}
