#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Node {
	string name;
	int seen, f;
	vector<string> edges, reverseEdges;
	Node(string n) : name(n) {}
};

struct Graph {
	int len;
	vector<Node*> nodes;
	Graph() : len(0) {}
};

void addEdge(Node &node, string node_name);
void addReverseEdge(Node &node, string node_name);
void addNodeToGraph(Graph &graph, Node node, int ind);
void addEdgeToNodeOnGraph(Graph &graph, string node_name, string edge_name);
void unseeNodes(Graph &graph);
Graph populate(string fileName);



int main()
{
	cout << "Start populating" << endl;

	Graph graph = populate("test.txt");

	cout << "Done populating, starting first dfs loop" << endl;
	cout << graph.len << endl;



	return(0);
}




void addEdge(Node &node, string node_name) {
	node.edges.resize(node.edges.size() + 1);
	node.edges.push_back(node_name);
}

void addReverseEdge(Node &node, string node_name) {
	node.reverseEdges.resize(node.reverseEdges.size() + 1);
	node.reverseEdges.push_back(node_name);
}

void addNodeToGraph(Graph &graph, Node node, int ind) {
	graph.len++;
	if (graph.nodes.capacity() < graph.len) {
		graph.nodes.resize(graph.len);
	}
	Node* pt = &node;
	graph.nodes.insert(graph.nodes.begin() + ind, pt);
}

void addEdgeToNodeOnGraph(Graph &graph, string node_name, string edge_name) {
	int node_name_int = stoi(node_name);
	int edge_name_int = stoi(edge_name);
	int max_ind = max(node_name_int, edge_name_int);
	if (max_ind > graph.nodes.capacity()) {
		graph.nodes.resize(max_ind + 1);
	}

	if (graph.nodes[node_name_int] == 0) {
		Node node = Node(node_name);
		addNodeToGraph(graph, node, node_name_int);
	}
	Node node = *graph.nodes[node_name_int];
	addEdge(node, edge_name);

	// add reverse edge
	if (graph.nodes[edge_name_int] == 0) {
		Node edge = Node(edge_name);
		addNodeToGraph(graph, edge, edge_name_int);
	}
	Node edge = *graph.nodes[edge_name_int];
	addReverseEdge(edge, node_name);
}

void unseeNodes(Graph &graph) {
	for (int i = 0; i < graph.nodes.size(); i++) {
		Node node = *graph.nodes[i];
		node.seen = 0;
	}
}

Graph populate(string fileName) {
	Graph graph = Graph();
	int lineNum = 1;
	string str;
	ifstream infile;
	infile.open(fileName);
	while(getline(infile, str)) {
		int ind = str.find(" ");
		string node_str = str.substr(0, ind);
		string edge_str = str.substr(ind + 1);
		addEdgeToNodeOnGraph(graph, node_str, edge_str);
		cout << "line " << lineNum << ": ";
		cout << node_str << ":" << edge_str << endl;
		lineNum++;
	}
	infile.close();
	return graph;
}
