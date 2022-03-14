#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>
#include <time.h>
using namespace std;

enum colour
{
	NO_COLOR,
	BLUE,
	GREEN
};

bool is_Bipartite(int graph_number, int V, int ***adjacency_lists)
{
	vector<int> color(V, NO_COLOR);
	queue<int> BFS_queue;
	for (int i = 0; i < V; i++)
	{
		if (!color[i])
		{
			BFS_queue.push(i);
			color[i] = BLUE;
			while (!BFS_queue.empty())
			{
				int queue_front = BFS_queue.front();
				BFS_queue.pop();
				for (int j = 0; j < V; j++)
				{
					if (adjacency_lists[graph_number][queue_front][j]) // true:adjacent
					{
						if (color[j] == color[queue_front])
							return false;
						if (!color[j])
						{
							BFS_queue.push(j);
							if (color[queue_front] == BLUE)
								color[j] = GREEN;
							else
								color[j] = BLUE;
						}
					}
				}
			}
		}
	}
	return true;
}

int Load_graph(int ***&adjacency_lists, int *&number_of_vertexes)
{
	ifstream test_file("test.txt", ios::in);
	if (!test_file.is_open())
		cerr << "Failed to open file.\n";
	else
	{
		int number_of_graphs, V;
		int tmp;
		test_file >> number_of_graphs;
		adjacency_lists = new int **[number_of_graphs];
		number_of_vertexes = new int[number_of_graphs];
		for (int n = 0; n < number_of_graphs; n++)
		{
			test_file >> V;
			adjacency_lists[n] = new int *[V];
			number_of_vertexes[n] = V;
			for (int i = 0; i < V; i++)
			{
				adjacency_lists[n][i] = new int[V];
				for (int j = 0; j < V; j++)
				{
					test_file >> tmp;
					adjacency_lists[n][i][j] = tmp;
				}
			}
		}
		test_file.close();
		return number_of_graphs;
	}
	return 0;
}

struct timespec diff(struct timespec start, struct timespec end) {
  struct timespec temp;
  if ((end.tv_nsec-start.tv_nsec)<0) {
    temp.tv_sec = end.tv_sec-start.tv_sec-1;
    temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
  } else {
    temp.tv_sec = end.tv_sec-start.tv_sec;
    temp.tv_nsec = end.tv_nsec-start.tv_nsec;
  }
  return temp;
}

int main()
{
	// 儲存時間用的變數
	struct timespec start, end;
	double time_used;

	// 計算開始時間
	clock_gettime(CLOCK_MONOTONIC, &start);
	
	//clock_t t1, t2;

	int number_of_graphs;
	int ***data;
	int *number_of_vertexes;
	number_of_graphs = Load_graph(data, number_of_vertexes);

	for (int i = 0; i < number_of_graphs; i++)
	{
		//t1 = clock();
		if (is_Bipartite(i, number_of_vertexes[i], data))
			cout << "True\n";
		else
			cout << "False\n";
		//t2 = clock();
		//printf("%lfseconds\n", (t2 - t1) / (double)(CLOCKS_PER_SEC));
	}

	// 計算結束時間
	clock_gettime(CLOCK_MONOTONIC, &end);

	// 計算實際花費時間
	struct timespec temp = diff(start, end);
	time_used = temp.tv_sec + (double) temp.tv_nsec / 1000000000.0;
	printf("Time = %f\n", time_used);

	return 0;
}