// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>
using namespace std;

bool isBipartite(int V, vector<vector<int>> &adj)
{
	// vector to store colour of vertex
	// assigning all to -1 i.e. uncoloured
	// colours are either 0 or 1
	// for understanding take 0 as red and 1 as blue
	vector<int> col(V, -1);

	// queue for BFS storing {vertex , colour}
	queue<pair<int, int> > q;

	//loop incase graph is not connected
	for (int i = 0; i < V; i++) {
	
	//if not coloured
		if (col[i] == -1) {
		
		//colouring with 0 i.e. red
			q.push({ i, 0 });
			col[i] = 0;
		
			while (!q.empty()) {
				pair<int, int> p = q.front();
				q.pop();
			
				//current vertex
				int v = p.first;
				//colour of current vertex
				int c = p.second;
				
				//traversing vertexes connected to current vertex
				// for (int j : adj[v]) {
				// 	//if already coloured with parent vertex color
				// 	//then bipartite graph is not possible
				// 	if (col[j] == c)
				// 		return 0;
				
				// 	//if uncoloured
				// 	if (col[j] == -1) {
				// 	//colouring with opposite color to that of parent
				// 		col[j] = (c) ? 0 : 1;
				// 		q.push({ j, col[j] });
				// 	}
					
				// }
				for (int j = 0;j<adj[v].size();j++) {
					int adj_v = adj[v][j];
					printf("traverse vertex : %d -> vertex : %d \n",v,adj_v);
					//if already coloured with parent vertex color
					//then bipartite graph is not possible
					if (col[adj_v] == c)
						return 0;
				
					//if uncoloured
					if (col[adj_v] == -1) {
					//colouring with opposite color to that of parent
						col[adj_v] = (c) ? 0 : 1;
						q.push({ adj_v, col[adj_v] });
					}
					
				}
			}
		}
	}
	//if all vertexes are coloured such that
	//no two connected vertex have same colours
	return 1;
}


void Load_graph(vector<vector<int>> &adj_list){
    ifstream f("2.txt",ios::in);
	if (!f.is_open()) {
        cout << "Failed to open file.\n";
    } else {
		string s;
		vector<int> edge;
		while(std::getline(f,s)){
			cout<<"This line is : "<<s<<"\n";
			istringstream istr(s);
			string tmp;
            edge.clear();
			while (istr>>tmp)
			{
				int value = stoi(tmp);
				printf("values : %d\n",value);
				edge.push_back(value);
			}
			adj_list.push_back(edge - 1);
		}
		f.close();
	}
	printf("Finish loading data: len of data is %d\n",adj_list.size());
}


int main()
{
	// number of vertex
	int V;
	V = 20;

	//adjacency list for storing graph
	// for testing
	// vector<int> adj[V];
	// adj[0] = {12};
	// adj[1] = {11};
	// adj[2] = {};
	// adj[3] = {10};
	// adj[4] = {13};
	// adj[5] = {15};
	// adj[6]={18};
	// adj[7]={16,17};
	// adj[8]={19};
	// adj[9]={18};
	// adj[10]={3};
	// adj[11]={1};
	// adj[12]={0};
	// adj[13]={4};
	// adj[14]={};
	// adj[15]={5};
	// adj[16]={7};
	// adj[17]={7};
	// adj[18]={6,9};
	// adj[19]={8};


	vector<vector<int>> data;
	Load_graph(data);

	bool ans = isBipartite(V, data);
	string s = (ans)?"Yes! It is Biopartite.\n":"No! It is not Biopartite.\n";
	cout<<"Anser is : "<<ans<<" and "<<s;

	return 0;
}