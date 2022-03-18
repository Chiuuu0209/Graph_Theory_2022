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
	ifstream test_file("test_adj_list.txt", ios::in);
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

int main()
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
	vector<vector<vector<int>>> data;
	number_of_graphs = Load_graph(data);
	for (int i = 0; i < number_of_graphs; i++)
	{
		///////////////////////////////////////////////////////////////////////////////
		// to calculate the execution time
		clock_gettime(CLOCK_MONOTONIC, &time_sub_1);
		///////////////////////////////////////////////////////////////////////////////

		if (is_Bipartite(i, data[i].size(), data))
			cout << "True\n";
		else
			cout << "False\n";
		
		///////////////////////////////////////////////////////////////////////////////
		// to calculate the execution time of graph
		clock_gettime(CLOCK_MONOTONIC, &time_sub_2);
		struct timespec temp = diff(time_sub_1, time_sub_2);
		time_used_sub = temp.tv_sec + (double)temp.tv_nsec / 1000000.0;
		cout << "The program execution time of this case is: " << time_used_sub << "ms" << endl;
		cout << "-----------------------------------------------------" << endl;
		///////////////////////////////////////////////////////////////////////////////
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