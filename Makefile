all: QuickSort BubbleSort InsertionSort

%: %.cc
	g++ -g -Wall -std=c++11 $< -o $@

%: %.c
	gcc $< -o $@

