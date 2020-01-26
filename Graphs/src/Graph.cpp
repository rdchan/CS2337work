//Rishi Chandna rdc180001
#include "Graph.h"
#include <iostream>
#include <queue>
/*
default constructor
create empty adjacency list/matrix
max size = 10
*/
Graph::Graph() {
    //initialize with default size
    current_size = 0;
    max_size = 10;
    matrix = new bool*[max_size];

    //empty out the matrix
    for(int i = 0; i < max_size; ++i) {
        matrix[i] = new bool[max_size];
        for(int j = 0; j < max_size; j++) {
            matrix[i][j] = false;
        }
    }
}

/*
overloaded constructor
create empty adjacency list/matrix
max size = int parameter
*/
Graph::Graph(int size) {
    //initialize with given size
    current_size = 0;
    max_size = size;
    matrix = new bool*[max_size];
    color = new int[max_size];
    //empty out the matrix
    for(int i = 0; i < max_size; ++i) {
        color[i] = -1;
        matrix[i] = new bool[max_size];
        for(int j = 0; j < max_size; j++) {
            matrix[i][j] = false;
        }
    }
}

Graph::~Graph() {
    delete [] matrix;
}
/*
isEmpty
check if current size is zero
*/
bool Graph::isEmpty() {
    return current_size == 0;
}

/*
createGraph
read a formatted file and fill adjacency list/matrix
The first line in the file contains a number that indicates the number of vertices (n).
The vertices are labeled as 1, 2, 3, . . . , n.
Each subsequent line describes the edges from each vertex (see sample file)
*/
void Graph::createGraph(std::string filename) {

    //try to open the file
    std::ifstream input(filename);
    if(!input.is_open()) {
        std::cerr << "couldn't find " << filename;
        return;
    }

    //grab the number of nodes in the graph
    std::string line;
    getline(input, line);
    int size = stoi(line);
    current_size = size;
    int node;
    int connection;

    //**CAREFUL** breaks if there are extra spaces after the last number

    //for each line in the file
    while(getline(input, line)) {
        //grab the home node that the line starts with
        node = stoi(line.substr(0, line.find(" "))) - 1;
        line.erase(0, line.find(" ")+1);
        //for each number after the home node that has a space before it
        while( line.find(" ") != std::string::npos) {
            connection = stoi(line.substr(0, line.find(" "))) - 1;
            line.erase(0, line.find(" ")+1);
            //add it to the adjacency matrix
            matrix[node][connection] = true;
        }
        //finish it off with the last number that doesn't have a space before it or something
        connection = stoi(line) - 1;
        matrix[node][connection] = true;
    }
}

/*
isConnected
To determine if a graph is connected, execute a depth first search and mark which nodes were visited.
If all nodes are not visited with a dfs, the graph is not connected.
*/
bool Graph::isConnected() {
    bool* visited = new bool[current_size]; //gets updated to see if each node was visited
    for(int i = 0; i < current_size; i++) {
        visited[i] = false;
    }
    //visit node 0, and its neighbors, and their neighbors that haven't already been visited,
    //and their neighbors that haven't already been visited
    //and their neighbors that haven't already been visited etc.
    VisitNode(visited, 0);

    //check that we visited every node
    for(int i = 0; i < current_size; i++) {
        if(visited[i] == false) {
            return false;
        }
    }
    return true;
}

/*
VisitNode
when visiting a node, mark it as visited, then visit any adjacent nodes fully (depth first) and come back to other adjacent nodes
*/
void Graph::VisitNode(bool* visited, int node) {
    visited[node] = true;
    for(int i = 0; i < current_size; i++) {
        if(matrix[node][i] == true) {
            if(visited[i] == false) {
                VisitNode(visited, i);
            }
        }
    }
}

/*
printMatrix
print the adjacency matrix so that it can be verified that the graph was created properly
*/
void Graph::printMatrix() {
    for(int i = 0; i < current_size; i++) {
        for(int j = 0; j < current_size; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool Graph::isBipartite() {
    int* color = new int[current_size];
    for(int i = 0; i < current_size; i++) {
        color[i] = -1;
    }

    std::queue<int> queue;
    color[0] = 1;
    queue.push(0);
    while(!queue.empty()) {
        int vertex = queue.front();
        queue.pop();
        for(int neighbor = 0; neighbor < current_size; neighbor++) {
            if(matrix[vertex][neighbor] == 1) {
                if(color[neighbor] == -1) {
                    color[neighbor] = (color[vertex] == 1 ? 2 : 1);
                    queue.push(neighbor);
                } else {
                    if(color[neighbor] == color[vertex]) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}
