all: QuickSort BubbleSort InsertionSort LinkedList BinaryTree

%: %.cc
	g++ -g -Wall -std=c++11 $< -o $@

%: %.c
	gcc $< -o $@

