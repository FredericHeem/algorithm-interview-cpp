all: QuickSort BubbleSort InsertionSort LinkedList BinaryTree Dijkstra Array

%: %.cc
	g++ -g -Wall -std=c++11 $< -o $@

%: %.c
	gcc $< -o $@

