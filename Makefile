all: QuickSort BubbleSort InsertionSort LinkedList

%: %.cc
	g++ -g -Wall -std=c++11 $< -o $@

%: %.c
	gcc $< -o $@

