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

bool is_Bipartite(int graph_number, int V, vector<vector<vector<int>>> &adjacency_lists)
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

int Load_graph(vector<vector<vector<int>>> &adjacency_lists)
{
	ifstream test_file("test.txt", ios::in);
	if (!test_file.is_open())
		cerr << "Failed to open file.\n";
	else
	{
		int number_of_graphs, V;
		int tmp;
		vector<int> edge;
		vector<vector<int>> adjacency_list;
		test_file >> number_of_graphs;
		for (int n = 0; n < number_of_graphs; n++)
		{
			test_file >> V;
			adjacency_list.clear();
			for (int i = 0; i < V; i++)
			{
				edge.clear();
				for (int j = 0; j < V; j++)
				{
					test_file >> tmp;
					edge.push_back(tmp);
				}
				adjacency_list.push_back(edge);
			}
			adjacency_lists.push_back(adjacency_list);
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
	vector<vector<vector<int>>> data;
	number_of_graphs = Load_graph(data);
	for (int i = 0; i < number_of_graphs; i++)
	{
		t1 = clock();
		if (is_Bipartite(i, data[i].size(), data))
			cout << "True\n";
		else
			cout << "False\n";
		t2 = clock();
		printf("%lfseconds\n", (t2 - t1) / (double)(CLOCKS_PER_SEC));
	}

	return 0;
}