//Rishi Chandna rdc180001
#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <fstream>

class Graph
{
    public:
        Graph();
        Graph(int);
        virtual ~Graph();
        bool isEmpty();
        void createGraph(std::string);
        bool isConnected();
        void VisitNode(bool*, int);
        void printMatrix();
        bool isBipartite();
    protected:

    private:
        int max_size = 10;
        int current_size;
        int* color;
        bool** matrix;

};

#endif // GRAPH_H
