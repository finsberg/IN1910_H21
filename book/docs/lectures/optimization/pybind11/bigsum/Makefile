

all:
	# c++ -O3 -Wall -shared -std=c++11 -fPIC `python3 -m pybind11 --includes` bigsum.cpp -o bigsum`python3-config --extension-suffix` # linux
	 c++ -O3 -Wall -shared -std=c++11 -undefined dynamic_lookup `python3 -m pybind11 --includes` bigsum.cpp -o bigsum`python3-config --extension-suffix` # mac osx


clean:
	rm bigsum`python3-config --extension-suffix`