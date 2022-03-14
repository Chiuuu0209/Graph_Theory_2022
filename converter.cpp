#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>
#include <time.h>
using namespace std;

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

void converter(vector<vector<vector<int>>> &adjacency_lists)
{
    ofstream output_file("output.txt", ios::out);
    if (!output_file.is_open())
        cerr << "Failed to open file.\n";
    else
    {
        output_file << adjacency_lists.size() << endl;
        for (int i = 0; i < adjacency_lists.size(); i++)
        {
            output_file << adjacency_lists[i].size() << endl;
            for (int j = 0; j < adjacency_lists[i].size(); j++)
            {
                int int1 = 0, int2 = 0;
                for (int k = 0; k < adjacency_lists[i][j].size(); k++)
                {
                    int2 = adjacency_lists[i][j][k] + 1;
                    for (int m = 0; m < int2 - int1 - 1; m++)
                    {
                        output_file << "0";
                    }
                    output_file << "1";
                    int1 = int2;
                }
                for (int n = 0; n < adjacency_lists[i].size() - int2; n++)
                {
                    output_file << "0";
                }
                output_file << endl;
            }
            output_file << endl;
        }
        output_file.close();
    }
}

int main()
{

    int number_of_graphs;
    vector<vector<vector<int>>> data;
    number_of_graphs = Load_graph(data);
    converter(data);

    return 0;
}