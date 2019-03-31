#pragma once
#include "nodedata.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#define MAXNODES 101
using namespace std;

class GraphM {

/*

ADT- Graph&Table , show shortest path

GraphM Class:

-allows to read the info from file, and store the info to make a graph of adjacent node edge
-allows to insert/remove edge 
-allows to find each node's shortest path to the each other node, and show the distant
-allows to find the shortest path and distant of between 2 specific nodes

Assumption
-Assume all the nodes are directed

-Assume the max nodes in the graph is 100

-If  the edge which passes into insertEdge()  has already exsited, this action will fail.

-Assume the TableType T want to be update every time during insert/remove edge
findShortestPath() get call in the  insert/remove method

--According to enhance the time complexity, I create an array of vector<int> as a list to store each node's adjacent nodes,
  and then I don't need to traverse the whole matrix when I check adjacent nodes.
*/
public:
		
	GraphM();											//: among others that need to be initialized, the data member T is initialized	
	bool buildGraph(ifstream&);						    //: builds up graph node information and adjacency matrix of edges betwee
	bool insertEdge(int, int, int);						//: insert an edge into graph between two given nodes	
	bool removeEdge(int, int);							//: remove an edge between two given nodes	
	void findShortestPath();							//: find the shortest path between every node to every other node in the graph,	
	void displayAll();									//:uses couts to demonstrate that the algorithm works properly.
	void display(int, int);								//display path by nodes


private:
	struct TableType {
		bool visited;									 // whether node has been visited
		int dist;										 // shortest distance from source known so far
		int path;										 // previous node in path of min dist
	};

	NodeData data [MAXNODES];							 // data for graph nodes 
	int C[MAXNODES][MAXNODES];							 // Cost array, the adjacency matrix
	int size;										     // number of nodes in the graph
	TableType T[MAXNODES][MAXNODES];					 // stores visited, distance, path
	vector<int> adjacentList[MAXNODES];						     // the list of each node's adjacent nodes
	string getPath(int, int);							 //a recursion helper, help to retrieve path (the node's previous node)
};