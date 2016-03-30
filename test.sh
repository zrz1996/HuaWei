#!/bin/bash
if [ $(uname) == "Darwin" ]; then
	g++-4.9 -std=c++11 ./checker/check.cpp -o ./checker/check -O2
else
	g++ -std=c++11 ./checker/check.cpp -o ./checker/check -O2
fi
python ./checker/test.py
