all: QuickSort

%: %.cc
	g++ -Wall -std=c++11 $< -o $@

%: %.c
	gcc $< -o $@

