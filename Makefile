OBJ = bipartite.cpp
InputFile = ./open_benchmarks/open_benchmarks.txt
all:build run
build:$(OBJ)
	g++ -o bipartite $(OBJ)
run:$(InputFile)
	./bipartite $(InputFile)
.PHONY:clean
clean:
	rm -rf *.o test