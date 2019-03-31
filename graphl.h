#pragma once
#include "nodedata.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#define MAXNODES 101

using namespace std;

class GraphL {

/*
ADT- Depth-first search

GraphL Class:
-allows to read the info from file, and store the info to make a graph of adjacent node edge
-allows to display each node info and edge in the graph
-allows to display the nodes in the depth-first order


Assumption 
-graphNode.edgeHead default
The edge will only store the toNode,  fromNode is stored as gNodes' index.
	
-infile edge data
Assume the infile edge from Node data is always in acsending order, i.e.(1 4, 2 1, 3 2, 4 3) 

-source node
Assume the source node is always 1
*/
public:
	GraphL();
	~GraphL();
	bool buildGraph(ifstream&);			// : builds up graph node information and adjacency list of edges between each node reading from a data file.
	void displayGraph();			//: Displays each node information and edge in the graph(e.g., the top portion of Figure 1 (c))
	void depthFirstSearch();		//: Makes a depth - first search and displays each node in depth - first order


private:

	struct EdgeNode;      // forward reference for the compiler
	struct GraphNode {    // structs used for simplicity, use classes if desired
		EdgeNode* edgeHead; // head of the list of edges
		NodeData* data;     // data information about each node
		bool visited;
	};
	
	struct EdgeNode {
		int adjGraphNode;  // subscript of the adjacent graph node
		EdgeNode* nextEdge;
	};

	GraphNode gNodes [MAXNODES];			// array of GraphNodes
	void dfsHelper(int i);							//depthFirstSearch helper Method
};
