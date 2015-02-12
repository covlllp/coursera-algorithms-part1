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
	int length;
	vector<Node*> nodes;
	Graph() {
		length = 0;
	}
};


void addEdge(Node node, string node_name) {
	node.edges.push_back(node_name);
}

void addReverseEdge(Node node, string node_name) {
	node.reverseEdges.push_back(node_name);
}

void addNodeToGraph(Graph graph, Node node, int ind) {
	graph.length++;
	if (graph.nodes.capacity() < graph.length) {
		graph.nodes.resize(graph.length * 100);
	}
	Node* pt = &node;
	graph.nodes.insert(graph.nodes.begin() + ind, pt);
}

void addEdgeToNodeOnGraph(Graph graph, string node_name, string edge_name) {
	int node_name_int = stoi(node_name);
	int edge_name_int = stoi(edge_name);
	if (graph.nodes[node_name_int] == 0) {
		Node node(node_name);
		addNodeToGraph(graph, node, edge_name_int);
	}
	Node* nodept = graph.nodes[node_name_int];
	Node node = *nodept;
	addEdge(node, edge_name);

	// add reverse edge
	if (graph.nodes[edge_name_int] == 0) {
		Node edge(edge_name);
		addNodeToGraph(graph, edge, node_name_int);
	}
	Node* edgept = graph.nodes[edge_name_int];
	Node edge = *edgept;
	addReverseEdge(edge, node_name);
}

void unseeNodes(Graph graph) {
	for (int i = 0; i < graph.nodes.size(); i++) {
		Node node = *graph.nodes[i];
		node.seen = 0;
	}
}


int main()
{
	Graph graph;
	int x = 5;
	Node node("hello");
	cout << graph.nodes.capacity() << '\n';
	Node* pt = &node;
	graph.nodes.resize(x);
	graph.nodes.insert(graph.nodes.begin() + x, pt);
	// nodes.insert(nodes.begin() + x, node);

	cout << "myvector contains:";
	for (int i=0;i<graph.nodes.size();i++)
		cout << ' ' << graph.nodes[i];
	cout << '\n';
	pt = graph.nodes[3];
	cout << pt;

	int i = 1;
	string str;
	ifstream infile;
	infile.open("test.txt");

	// while(getline(infile, str)) {
	// 	cout << "line " << i << ":" << str << '\n';
	// 	i++;
	// }

	infile.close();


	return(0);
}