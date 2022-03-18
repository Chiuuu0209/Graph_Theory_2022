# Graph Theory project 1
---
## data_structure:
```
----Team_N_E24076831_E24076475
  |----README.md
  |----Project_report.docs  
  |----Makefile             
  |----Bipartite.cpp
  |----test_cases
     |----test_cases.txt
     |----test_cases.jpg
  |----open_banchmarks
     |----open_banchmarks.txt
     |----open_benchmarks_1.jpg
     |----open_benchmarks_2.jpg
```

# About this program
```
Input a text file with informations of a series of graphs to examinate whether each of them is bipartite.
It will print "Graph i :True" on the screen if it is bipartite or "Graph i :False" if not.
```

## How to compile and run
|instruction                |descripton                             |
|  -----------------------  | ------------------------------------  |
|make build                 |compiles bipartite.cpp to bipartite.exe|
|make run                   |run bipartite.exe with open benchmarks |
|make run InputFile=FILENAME|run bipartite.exe with FILENAME        |
|make                       |(build and run)                        |
|make clean                 |                                       |

## input_file
```
open benchmarks: /open_benchmarks/open_benchmarks.txt
other test cases: /test_cases/test_cases.txt
...
```

## format of test cases
```
number_of_graphs
number_of_vertex_in_graph(1)
number_of_adj_vertexes_of_vertex(1) adj_vertex_1_of_vertex(1) adj_vertex_2_of_vertex(1)...
number_of_adj_vertexes_of_vertex(2) adj_vertex_1_of_vertex(2)...
number_of_adj_vertexes_of_vertex(3) adj_vertex_1_of_vertex(3)...
...

number_of_vertex_in_graph(2)
number_of_adj_vertexes_of_vertex(1) adj_vertex_1_of_vertex(1) adj_vertex_2_of_vertex(1)...
number_of_adj_vertexes_of_vertex(2) adj_vertex_1_of_vertex(2)...
number_of_adj_vertexes_of_vertex(3) adj_vertex_1_of_vertex(3)...
...

example:

line
1.      2
2.      3
3.      2 2 3
4.      1 1
5.      1 1
6.      
7.      3
8.      1 2
9.      1 1
10.     0

表示此份檔案包含*2*個graph
第一個graph有*3*個vertex
vertex 1 有*2*個adjacent vertex, 分別為vertex *2* 及 vertex *3*
vertex 2 有*1*個adjacent vertex, 為vertex *1*
vertex 3 有*1*個adjacent vertex, 為vertex *1*

第二個graph有*3*個vertex
vertex 1 有*1*個adjacent vertex, 為vertex *2*
vertex 2 有*1*個adjacent vertex, 為vertex *1*
vertex 3 有*0*個adjacent vertex

```

## test cases
![image](test_cases/test_cases.jpg)

## open benchmarks
![image](open_benchmarks/open_benchmarks_1.jpg)
![image](open_benchmarks/open_benchmarks_2.jpg)
