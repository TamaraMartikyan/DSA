
#include <iostream>
#include <list>
#include <map>
using namespace std;

class Graph {
    map<int, list<int> >
        adjList; 

public:
  
    void add_edge(int u, int v)
    {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

  
    void print()
    {
        cout << "Adjacency list for the Graph: " << endl;
     
        for (auto i : adjList) {
        
            cout << i.first << " -> ";
            
            for (auto j : i.second) {
                // Print the connected vertex
                cout << j << " ";
            }
            cout << endl;
        }
    }
};

int main()
{
    Graph g;

    g.add_edge(1, 0);
    g.add_edge(2, 0);
    g.add_edge(1, 2);

    g.print();
    return 0;
}
