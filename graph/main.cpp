#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

struct Graph {
    unordered_map<int, vector<int>> adjacency_list;
    unordered_map<int, int> vertex_to_mat_index;
    int no_of_vertices;
    int no_of_edges;
};

void printGraph(const Graph &graph) {
    cout << "Graph:\n";
    for (const auto &[vertex, neighbours] : graph.adjacency_list) {
        cout << vertex << ": ";
        for (int neighbour : neighbours) {
            cout << neighbour << " ";
        }
        cout << "\n";
    }
    cout << endl;
}

Graph readGraphFromFile(const string &filename) {
    Graph graph;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        int vertex;
        char colon;
        ss >> vertex >> colon;
        int neighbour;
        vector<int> neighbours;
        while (ss >> neighbour) {
            neighbours.push_back(neighbour);
            if (ss.peek() == ',')
                ss.ignore();
        }
        graph.adjacency_list[vertex] = neighbours;
        graph.no_of_vertices++;
    }
    return graph;
}

vector<vector<int>> createAdjacencyMatrix(const Graph &graph) {
    int n = graph.no_of_vertices;
    vector<vector<int>> matrix(n, vector<int>(n, 0));
    for (const auto &[vertex, neighbours] : graph.adjacency_list) {
        auto it_i = graph.vertex_to_mat_index.find(vertex);
        if (it_i != graph.vertex_to_mat_index.end()) {
            int i = it_i->second;

            for (int neighbour : neighbours) {
                auto it_j = graph.vertex_to_mat_index.find(neighbour);
                if (it_j != graph.vertex_to_mat_index.end()) {
                    int j = it_j->second;
                    matrix[i][j] = 1;
                    matrix[j][i] = 1;
                }
            }
        }
    }
    return matrix;
}

unordered_map<int, vector<int>> createAdjacencyList(const Graph &graph) {
    return graph.adjacency_list;
}

void constructIndexingMap(Graph &graph) {
    int index = 0;
    unordered_map<int, int> res;
    for (const auto &[vertex, _] : graph.adjacency_list) {
        res[vertex] = index++;
    }
    graph.vertex_to_mat_index = res;
}

void printGraphIndexingMap(const Graph &graph) {
    cout << "Graph vertex to index map:\n";
    for (const auto &[vertex, index] : graph.vertex_to_mat_index) {
        cout << vertex << ": " << index << ", ";
    }
    cout << endl;
}

void printMatrix(const vector<vector<int>> &matrix) {
    for (const auto &line : matrix) {
        for (int val : line) {
            cout << val << " ";
        }
        cout << "\n";
    }
}

int main() {
    Graph graph = readGraphFromFile("graph.txt");

    constructIndexingMap(graph);
    printGraphIndexingMap(graph);

    cout << endl;

    printGraph(graph);

    cout << endl;

    unordered_map<int, vector<int>> adjacency_list = createAdjacencyList(graph);


    return 0;
}