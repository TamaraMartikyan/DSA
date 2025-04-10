#include <iostream>
#include <string>
using namespace std;

class Graph {
private:
    const int rows = 7;
    const int cols = 7;
    string matrix[7][7]; 

public:
   
    Graph() {
        matrix[0][0] = "0"; matrix[0][1] = "n1"; matrix[0][2] = "n2"; matrix[0][3] = "n3"; matrix[0][4] = "n4"; matrix[0][5] = "n5"; matrix[0][6] = "n6";
        matrix[1][0] = "n1"; matrix[1][1] = "0"; matrix[1][2] = "10"; matrix[1][3] = "0"; matrix[1][4] = "0"; matrix[1][5] = "8"; matrix[1][6] = "5";
        matrix[2][0] = "n2"; matrix[2][1] = "10"; matrix[2][2] = "0"; matrix[2][3] = "0"; matrix[2][4] = "20"; matrix[2][5] = "12"; matrix[2][6] = "0";
        matrix[3][0] = "n3"; matrix[3][1] = "0"; matrix[3][2] = "0"; matrix[3][3] = "0"; matrix[3][4] = "4"; matrix[3][5] = "0"; matrix[3][6] = "0";
        matrix[4][0] = "n4"; matrix[4][1] = "0"; matrix[4][2] = "20"; matrix[4][3] = "4"; matrix[4][4] = "0"; matrix[4][5] = "15"; matrix[4][6] = "0";
        matrix[5][0] = "n5"; matrix[5][1] = "8"; matrix[5][2] = "12"; matrix[5][3] = "0"; matrix[5][4] = "15"; matrix[5][5] = "0"; matrix[5][6] = "7";
        matrix[6][0] = "n6"; matrix[6][1] = "5"; matrix[6][2] = "0"; matrix[6][3] = "0"; matrix[6][4] = "0"; matrix[6][5] = "7"; matrix[6][6] = "0";
    }

  
    void printAdjMatrix() {
        cout << "\nAdjacency Matrix Representation:\n";
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << matrix[i][j] << "\t";
            }
            cout << "\n";
        }
    }

   
    void determineAndPrintNodes() {
        int E = -1, D = -1, B = -1, F = -1, A = -1, C = -1;

        // node E (with exactly 1 connection)
        for (int i = 1; i < rows; i++) {
            int connections = 0;
            for (int j = 1; j < cols; j++) {
                if (matrix[i][j] != "0") connections++;
            }
            if (connections == 1) { E = i; break; }
        }

        // node D (connected to E)
        for (int j = 1; j < cols; j++) {
            if (matrix[E][j] != "0") { D = j; break; }
        }

        // node B (with exactly 4 connections)
        for (int i = 1; i < rows; i++) {
            int connections = 0;
            for (int j = 1; j < cols; j++) {
                if (matrix[i][j] != "0") connections++;
            }
            if (connections == 4) { B = i; break; }
        }

        // node F (connected to D but not E or B)
        for (int j = 1; j < cols; j++) {
            if (matrix[D][j] != "0" && j != E && j != B) { F = j; break; }
        }

        // node A (with exactly 2 connections)
        for (int i = 1; i < rows; i++) {
            int connections = 0;
            for (int j = 1; j < cols; j++) {
                if (matrix[i][j] != "0") connections++;
            }
            if (connections == 2 && i != E) { A = i; break; }
        }

        // node C (the remaining node)
        for (int i = 1; i < rows; i++) {
            if (i != E && i != D && i != B && i != F && i != A) { C = i; break; }
        }

       
        cout << "\nNode A = " << matrix[A][0] << "\n";
        cout << "Node B = " << matrix[B][0] << "\n";
        cout << "Node C = " << matrix[C][0] << "\n";
        cout << "Node D = " << matrix[D][0] << "\n";
        cout << "Node E = " << matrix[E][0] << "\n";
        cout << "Node F = " << matrix[F][0] << "\n";

       
        string distance = matrix[B][C];
        cout << "\nDistance between B and C: " << distance << "\n";
    }
};

int main() {
   
    Graph graph;

   
    graph.printAdjMatrix();
    graph.determineAndPrintNodes();

    return 0;
}