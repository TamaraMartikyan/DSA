#include <iostream>
using namespace std;

void printTrustRelations(int trust[][2], int rows) {
    cout << "Trust connections:" << endl;
    for (int i = 0; i < rows; i++) {
        cout << "{" << trust[i][0] << ", " << trust[i][1] << "} ";
    }
    cout << endl;
}


int findJudge(int n, int trust[][2], int rows) {
    int out[100] = { 0 };
    int in[100] = { 0 };

    printTrustRelations(trust, rows);

    for (int i = 0; i < rows; i++) {
        int a = trust[i][0], b = trust[i][1];
        in[b]++;
        out[a]++;
    }

    for (int i = 1; i <= n; i++) {
        if (in[i] == n - 1 && out[i] == 0) {
            return i;
        }
    }

    return -1;
}

int main() {
    int n = 3;
    int trust1[3][2] = { {1, 3}, {2, 3} };
    int rows1 = 2;
    cout << "Judge: " << findJudge(n, trust1, rows1) << endl;
    cout << endl;


    int trust2[3][2] = { {1, 3}, {2, 3}, {3, 1} };
    int rows2 = 3;
    cout << "Judge: " << findJudge(n, trust2, rows2) << endl;

    return 0;
}




#include <iostream>
#include <vector>
using namespace std;

class Graph {
public:
    int judgeDecision;
    vector<pair<int, int>> edges;
    Graph(int decision) : judgeDecision(decision) {}

    void addEdge(int person, int agreement) {
        edges.push_back({ person, agreement });
    }

    bool getVerdict() {
        int agreementCount = 0;

        for (auto& edge : edges) {
            if (edge.second == 1) {
                agreementCount++;
            }
        }

        int n = edges.size();
        if (agreementCount > n / 2) {
            return judgeDecision == 1;
        }
        else {
            return judgeDecision == 0;
        }
    }
};

int main() {
    int judgeDecision;
    int n;

    cout << "Mutqagreq datavori voroshumy(1-mexadrakan, 2-ardaracman): ";
    cin >> judgeDecision;

    cout << "Mutqagreq mardkanc qanaky: ";
    cin >> n;

    Graph graph(judgeDecision);

    cout << "Mutqagreq yuraqanchyuri voroshumy(1-hamakarciq e datavori voroshmany, 0-tarakarciq e)" << endl;
    for (int i = 0; i < n; i++) {
        int opinion;
        cin >> opinion;
        graph.addEdge(i, opinion);
    }

    if (graph.getVerdict()) {
        cout << "Mexadryaly mexavor e chanachvel." << endl;
    }
    else {
        cout << "Mexadryaly ardaracvel e." << endl;
    }

    return 0;
}