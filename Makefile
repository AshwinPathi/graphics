CXX=clang++
CXXFLAGS=-std=c++2a -O2


MAIN = main.cpp
DRIVER = src/raytracer/driver.cpp

run:
	$(CXX) $(CXXFLAGS) $(MAIN) $(DRIVER)

.PHONY: clean

clean:
	rm -f a.out