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
				for (int j = 1; j <= adjacency_lists[graph_number][queue_front][0]; j++)
				{
					int adjacent_vertex = adjacency_lists[graph_number][queue_front][j];
					if (color[adjacent_vertex] == color[queue_front])
						return false;
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

int Load_graph(int ***&adjacency_lists, int *&number_of_vertexes)
{
	ifstream test_file("test_adj_list_for_pointer.txt", ios::in);
	if (!test_file.is_open())
		cerr << "Failed to open file.\n";
	else
	{
		int number_of_graphs, V;
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
				test_file >> number_of_adj_vertexes;
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

int main()
{
	clock_t t1, t2;

	int number_of_graphs;
	int ***data;
	int *number_of_vertexes;
	number_of_graphs = Load_graph(data, number_of_vertexes);
	for (int i = 0; i < number_of_graphs; i++)
	{
		t1 = clock();
		if (is_Bipartite(i, number_of_vertexes[i], data))
			cout << "True\n";
		else
			cout << "False\n";
		t2 = clock();
		printf("%lfseconds\n", (t2 - t1) / (double)(CLOCKS_PER_SEC));
	}

	return 0;
}