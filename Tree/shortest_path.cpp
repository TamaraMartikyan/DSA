#include <iostream>
#include <limits>
using namespace std;

const int V = 7; 

int minDistance(int dist[], bool visited[]) {
    int min = numeric_limits<int>::max();
    int min_index = -1;
    for (int v = 0; v < V; v++) {
        if (!visited[v] && dist[v] < min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}


void printDistances(int dist[]) {
    cout << "Vertex \t Distance from A" << endl;
    for (int i = 0; i < V; i++) {
        cout << char('A' + i) << " \t " << dist[i] << endl;
    }
}

void dijkstra(int graph[V][V]) {
    int dist[V]; // dist[i] will hold the shortest distance from A to i
    bool visited[V];

    // Initialize all distances as INFINITE and visited[] as false
    for (int i = 0; i < V; i++) {
        dist[i] = numeric_limits<int>::max();
        visited[i] = false;
    }

  
    dist[0] = 0;

   
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed
        int u = minDistance(dist, visited);

        
        if (u == -1) break;

      
        visited[u] = true;

        // Update dist value of the adjacent vertices of the picked vertex
        for (int v = 0; v < V; v++) {

            if (!visited[v] &&
                graph[u][v] &&
                dist[u] != numeric_limits<int>::max() &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printDistances(dist);
    cout << "\nShortest distance from A to G: " << dist[6] << endl;
}

int main() {
  
    int graph[V][V] = { 0 };

    // Add edges (A=0, B=1, C=2, D=3, E=4, F=5, G=6)
    graph[0][1] = 5;    // A -> B (5)
    graph[0][3] = 12;   // A -> D (12)
    graph[0][6] = 25;   // A -> G (25)
    graph[1][3] = 8;    // B -> D (8)
    graph[3][2] = 2;    // D -> C (2)
    graph[2][4] = 4;    // C -> E (4)
    graph[4][6] = 5;    // E -> G (5)
    graph[2][6] = 10;   // C -> G (10)
    graph[2][5] = 5;    // C -> F (5)
    graph[5][6] = 10;   // F -> G (10)

    dijkstra(graph);
    return 0;
}