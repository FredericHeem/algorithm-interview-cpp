all: QuickSort BubbleSort

%: %.cc
	g++ -Wall -std=c++11 $< -o $@

%: %.c
	gcc $< -o $@

