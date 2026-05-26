CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g

my-redis: src/main.cpp
	$(CXX) $(CXXFLAGS) -o my-redis src/main.cpp

clean:
	rm -f my-redis