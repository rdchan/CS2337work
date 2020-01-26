//Rishi Chandna rdc180001
#include <iostream>
#include "Graph.h"

using namespace std;

int main()
{
    Graph graph;
    graph.createGraph("graph4.txt");
    graph.printMatrix();
    cout << "graph is " << (graph.isConnected() ? "" : "not ") << "connected" << endl;
    cout << "graph is " << (graph.isBipartite() ? "" : "not ") << "bipartite" << endl;
    cout << "task failed successfully" << endl;
    return 0;
}
