#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>
#include <time.h>
#include <string>
using namespace std;

enum colour
{
	NO_COLOR,
	BLUE,
	GREEN
};

// use BFS to test if Chromatic Number <= 2
bool is_Bipartite(int graph_number, int V, int ***adjacency_lists)
{
	vector<int> color(V, NO_COLOR);
	queue<int> BFS_queue;

	for (int i = 0; i < V; i++)
	{
		// new component
		if (!color[i])
		{
			BFS_queue.push(i);
			color[i] = BLUE;
			while (!BFS_queue.empty())
			{
				int queue_front = BFS_queue.front();
				BFS_queue.pop();

				// adjacency vertexes
				for (int j = 1; j <= adjacency_lists[graph_number][queue_front][0]; j++)
				{
					int adjacent_vertex = adjacency_lists[graph_number][queue_front][j];

					// odd cycle
					if (color[adjacent_vertex] == color[queue_front])
						return false;

					// new vertex
					if (!color[adjacent_vertex])
					{
						BFS_queue.push(adjacent_vertex);
						if (color[queue_front] == BLUE)
							color[adjacent_vertex] = GREEN;
						else
							color[adjacent_vertex] = BLUE;
					}
				}
			}
		}
	}
	return true;
}

int Load_graph(string input_file, int ***&adjacency_lists, int *&number_of_vertexes)
{
	ifstream test_file(input_file, ios::in);

	if (!test_file.is_open())
		cerr << "Failed to open file.\n";

	else
	{
		int number_of_graphs, V; // V : number of vertexes in one graph
		int number_of_adj_vertexes, tmp;

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
				test_file >> number_of_adj_vertexes; // of one vertex
				adjacency_lists[n][i] = new int[number_of_adj_vertexes + 1];

				adjacency_lists[n][i][0] = number_of_adj_vertexes;
				for (int j = 1; j < number_of_adj_vertexes + 1; j++)
				{
					test_file >> tmp;
					adjacency_lists[n][i][j] = tmp - 1;
				}
			}
		}

		test_file.close();
		return number_of_graphs;
	}
	return 0;
}

// for calculating the execution time of this program
struct timespec diff(struct timespec start, struct timespec end)
{
	struct timespec temp;
	if ((end.tv_nsec - start.tv_nsec) < 0)
	{
		temp.tv_sec = end.tv_sec - start.tv_sec - 1;
		temp.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
	}
	else
	{
		temp.tv_sec = end.tv_sec - start.tv_sec;
		temp.tv_nsec = end.tv_nsec - start.tv_nsec;
	}
	return temp;
}

int main(int argc, char **argv)
{
	///////////////////////////////////////////////////////////////////////////////
	// to calculate the total execution time of one case
	struct timespec time_start, time_end;
	double time_used_total;
	clock_gettime(CLOCK_MONOTONIC, &time_start);

	struct timespec time_sub_1, time_sub_2;
	double time_used_sub;
	///////////////////////////////////////////////////////////////////////////////

	int number_of_graphs;
	int ***data;				 // data structure : adj. list
	int *number_of_vertexes;	 // of each graphs
	string input_file = argv[1]; // input file name

	number_of_graphs = Load_graph(input_file, data, number_of_vertexes);
	for (int i = 0; i < number_of_graphs; i++)
	{
		cout << "Graph " << i + 1 << " :";

		if (is_Bipartite(i, number_of_vertexes[i], data))
			cout << "True\n";
		else
			cout << "False\n";
	}

	///////////////////////////////////////////////////////////////////////////////
	// to calculate the total execution time
	cout << endl;
	clock_gettime(CLOCK_MONOTONIC, &time_end);
	struct timespec temp = diff(time_start, time_end);
	time_used_total = temp.tv_sec + (double)temp.tv_nsec / 1000000.0;
	cout << "The program execution time of this program is: " << time_used_total << "ms" << endl;
	///////////////////////////////////////////////////////////////////////////////

	return 0;
}