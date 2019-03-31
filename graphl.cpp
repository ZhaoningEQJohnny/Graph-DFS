#include "pch.h"
#include "graphl.h"

//constructor ,  init gNodes arr
GraphL::GraphL()
{
	for (int i = 0; i < MAXNODES; i++)
	{
		gNodes[i].data = NULL;
		gNodes[i].edgeHead = NULL;
		gNodes[i].visited = false;
	}
}

//deconstructor
GraphL::~GraphL()
{
	int i = 1;
	while (gNodes[i].data != NULL)
	{
		delete gNodes[i].data;
		gNodes[i].data = NULL;
		EdgeNode* curEdge = gNodes[i].edgeHead;
		while (curEdge != NULL)
		{
			gNodes[i].edgeHead = gNodes[i].edgeHead->nextEdge;
			delete curEdge;
			curEdge = gNodes[i].edgeHead;
		}
		i++;
	}
}


//split string by specific char ' '
static void SplitStr(string s, vector<string>& v, char c)
{
	int count = 0;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == c)
		{
			v.push_back(s.substr(count, i - count));
			count = i + 1;
		}
	}
	v.push_back(s.substr(count, s.size()));
}


// : builds up graph node information and adjacency list of edges between each node reading from a data file.
bool GraphL::buildGraph(ifstream& infile)
{
	//if file is empty , return false
	if (infile.eof())
	{
		return false;
	}
	string line = "";
	//first line -- size
	getline(infile, line);
	int size = atoi(line.c_str());
	//store node's name from file into  data array
	for (int i = 1; i <= size; i++)
	{
		if (infile.eof())
		{
			return false;
		}
		getline(infile, line);
		//set data value from file
		NodeData* newData = new NodeData(line);
		gNodes[i].data = newData;
	}
	//build edges
	while (!infile.eof())
	{
		getline(infile, line);
		vector<string> v;
		SplitStr(line, v, ' ');
		int n1 = atoi(v[0].c_str());
		int n2 = atoi(v[1].c_str());
		if (n1 == 0)
		{
			break;
		}
		EdgeNode* newEdge = new EdgeNode();
		newEdge->adjGraphNode = n2;
		newEdge->nextEdge = NULL;
		if (gNodes[n1].edgeHead == NULL)
		{
			gNodes[n1].edgeHead = newEdge;
		}
		else
		{
			newEdge->nextEdge = gNodes[n1].edgeHead;
			gNodes[n1].edgeHead= newEdge;
		}
				
	}

	return true;
}
//: Displays each node information and edge in the graph
void GraphL::displayGraph()
{
	cout << "Graph:" << endl;
	int i = 1;
	while (gNodes[i].data != NULL)
	{
		cout << "Node" << i << "         " <<  *gNodes[i].data << endl;
		EdgeNode* curEdge = gNodes[i].edgeHead;
		while (curEdge != NULL)
		{
			cout << "  edge  "<<i<<"  "<<curEdge->adjGraphNode<<endl;
			curEdge = curEdge->nextEdge;
		}
		i++;

	}
	cout << endl;
}
//: Makes a depth - first search and displays each node in depth - first order
void GraphL::depthFirstSearch()
{
	cout << "Depth-fisrt ordering:  ";
	int i = 1;
	while (gNodes[i].data != NULL)
	{
		if (!gNodes[i].visited)
		{
			dfsHelper(i);
		}
		i++;
	}
	cout << endl << endl;
}

void GraphL::dfsHelper(int index)
{
	EdgeNode* curEdge = gNodes[index].edgeHead;
	gNodes[index].visited = true;
	cout << index << " ";
	while (curEdge != NULL)
	{
		if (!gNodes[curEdge->adjGraphNode].visited)
		{
			dfsHelper(curEdge->adjGraphNode);
		}
		curEdge = curEdge->nextEdge;
	}
}