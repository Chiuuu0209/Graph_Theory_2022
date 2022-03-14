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
				for (int j = 0; j < adjacency_lists[graph_number][queue_front].size(); j++)
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

int Load_graph(vector<vector<vector<int>>> &adjacency_lists)
{
	ifstream test_file("test.txt", ios::in);
	if (!test_file.is_open())
		cerr << "Failed to open file.\n";
	else
	{
		int number_of_graphs, V;
		string s, tmp;
		vector<int> edge;
		vector<vector<int>> adjacency_list;
		test_file >> number_of_graphs;
		for (int n = 0; n < number_of_graphs; n++)
		{
			test_file >> V;
			getline(test_file, s);
			adjacency_list.clear();
			for (int i = 0; i < V; i++)
			{
				getline(test_file, s);
				istringstream istr(s);
				edge.clear();
				while (istr >> tmp)
				{
					int value = stoi(tmp);
					edge.push_back(value - 1);
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