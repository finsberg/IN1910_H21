cmake_minimum_required(VERSION 3.4...3.18)
project(mandelbrot LANGUAGES CXX)

find_package(pybind11 REQUIRED)
pybind11_add_module(mandelbrot_py mandelbrot_pybind.cpp)