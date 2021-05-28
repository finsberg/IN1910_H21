#include <pybind11/pybind11.h>

int add(int i, int j) {
    return i + j;
}

/* 
First argument here is the name of the module
which we set to example. The second argument is a
variable which we use to create the bindings.

m.doc() - can be used to create a docstring for the module

m.def() - generated the binding code.
+ first argument is the name of the function as it
will appear in the python module
+ second argument is a reference to the function
+ third argument is the docstring
+ Remaining arguments can be used to define names of the argument,
so that we can use keyword arguments in python
*/
PYBIND11_MODULE(example, m) {
    m.doc() = "pybind11 example plugin";  // optional module docstring

    m.def("add", &add, "A function which adds two numbers");

    // With keyword arguments
    // m.def("adding", &add, "A function which adds two numbers", py::arg("i"), py::arg("j"));

    // With default arguments
    // m.def("add", &add, "A function which adds two numbers",
    //   py::arg("i") = 1, py::arg("j") = 2);
}