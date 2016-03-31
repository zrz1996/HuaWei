.PHONY: all
all: check future_net

check: ./checker/check.cpp
	g++-4.9 -std=c++11  ./checker/check.cpp -o ./checker/check -O2

future_net: future_net.cpp
	g++-4.9 -std=c++11  future_net.cpp -o future_net -O2

.PHONY: clean
clean:
	rm ./checker/check future_net
	
