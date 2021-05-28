#include <pybind11/pybind11.h>
#include <iostream>

namespace py = pybind11;

unsigned long int sum(unsigned long int n) {
    unsigned long int s = 0;
    for (unsigned long int i = 0; i < n; i++) {
        s += i;
    }
    return s;
}

PYBIND11_MODULE(bigsum, m) {
    m.doc() = "pybind11 bigsum example";  // optional module docstring

    m.def("sum", &sum, "Sum all elements from 0 to n", py::arg("n"));
}


int main(){

    int n = 100;
    int s = sum(100);
    std::cout << "Sum of all number up to " << n << " is: " << s << std::endl;

}