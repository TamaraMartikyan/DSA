#include <iostream>
#include <vector>
using namespace std;

class Graph {
private:
    vector<vector<int>> adjList; 

public:
    
    Graph(int numStudents) {
        adjList.resize(numStudents + 1); // 1-based indexing
    }

   
    void addConnection(int u, int v) {
        if (u > 0 && v > 0 && u < adjList.size() && v < adjList.size()) {
            adjList[u].push_back(v);
            adjList[v].push_back(u); 
        }
        else {
            cout << "Invalid student number" << endl;
        }
    }

    
    void printGraph() const {
        for (int i = 1; i < adjList.size(); ++i) {
            cout << "Student " << i << ": ";
            for (int friendId : adjList[i]) {
                cout << friendId << " ";
            }
            cout << endl;
        }
    }

    
    int calculateTotalDegrees() const {
        int totalDegrees = 0;
        for (const auto& list : adjList) {
            totalDegrees += list.size(); // Sum the size of all adjacency lists
        }
        return totalDegrees;
    }

   
    bool isConfigurationPossible() const {
        return calculateTotalDegrees() % 2 == 0;
    }
};

int main() {
    int numStudents, numConnections;

   
    cout << "Enter the number of students: ";
    cin >> numStudents;
    cout << "Enter the number of connections: ";
    cin >> numConnections;

    if (numStudents <= 0 || numConnections < 0) {
        cout << "Invalid input" << endl;
        return -1; 
    }

    
    Graph graph(numStudents);
    cout << "Enter the connections (pairs of friends):" << endl;
    for (int i = 0; i < numConnections; ++i) {
        int u, v;
        cin >> u >> v;
        if (u <= numStudents && v <= numStudents && u > 0 && v > 0) {
            graph.addConnection(u, v);
        }
        else {
            cout << "Invalid student number in connection " << u << " and " << v << ". Skipping this connection." << endl;
        }
    }

    
    cout << "Total sum of degrees: " << graph.calculateTotalDegrees() << endl;
    cout << (graph.isConfigurationPossible() ? "The configuration is possible." : "The configuration is not possible.") << endl;

 
    graph.printGraph();

    return 0;
}





#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Graph {
private:
    vector<vector<int>> adjList;  

public:
    
    Graph(int numStudents) {
        adjList.resize(numStudents + 1);  
    }

    
    void addFriendship(int u, int v) {
        adjList[u].push_back(v); 
        adjList[v].push_back(u);  
    }

    
    int getDegree(int student) {
        return adjList[student].size();  
    }

    
    bool hasFourStudentsWithSameDegree() {
        unordered_map<int, int> degreeCount;  // Map to count the number of students for each degree
        for (int i = 1; i < adjList.size(); ++i) {  
            int degree = getDegree(i); // Get the degree (number of friends) of student i
            degreeCount[degree]++;
            if (degreeCount[degree] >= 4) {
                return true;  
            }
        }
        return false;
    }
};

int main() {
    int numStudents, numConnections;

    
    cout << "Enter the number of students: ";
    cin >> numStudents;
    cout << "Enter the number of connections: ";
    cin >> numConnections;

    
    Graph graph(numStudents);

  
    if (graph.hasFourStudentsWithSameDegree()) {
        cout << "There are at least 4 students with the same number of friends." << endl;
    }
    else {
        cout << "No four students have the same number of friends." << endl;
    }

    return 0;
}
