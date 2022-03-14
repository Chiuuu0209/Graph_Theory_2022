all:hello.cpp
	g++ test.cpp -o test
clean:
	re -f test
open:
	