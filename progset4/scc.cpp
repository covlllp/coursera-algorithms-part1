#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
// #include <algorithm>
using namespace std;

struct Node {
	string name;
	int seen, f;
	vector<Node*> edges, reverseEdges;
	Node(string n){
		name = n;
		seen = 0;
	}
};

struct Graph {
	vector<Node*> nodes;	// size is always one more; 0 index not used
	vector<int> scc;		// contains all scc sizes
};

void printVector(vector<int> vec);
void addEdge(Node &node, Node* node_name);
void addReverseEdge(Node &node, Node* node_name);
void addNodeToGraph(Graph &graph, Node* pt, int ind);
void addEdgeToNodeOnGraph(Graph &graph, string node_name, string edge_name);
void unseeNodes(Graph &graph);
Graph* populate(string fileName);
Graph* dfs_loop(Graph* graph, string direction);
void dfs(Node* node, string direction, int &t, int &s, Graph* graph);
bool compare(int a, int b);



int main()
{
	cout << "Start populating" << endl;
	Graph* graph = populate("test.txt");
	cout << "Done populating, starting first dfs loop" << endl;

	cout << "Start DFS loop on reverse graph" << endl;
	graph = dfs_loop(graph, "reverse");
	cout << "DFS reverse loop complete" << endl;

	for (int i = 1; i < graph->nodes.size(); i++) {
		cout << "Node " << graph->nodes[i]->name << " found at " << i << endl;
	}

	// cout << "Unsee all nodes" << endl;
	// unseeNodes(*graph);
	// cout << "Unseeing nodes complete" << endl;

	// cout << "Start DFS loop on forward graph" << endl;
	// graph = dfs_loop(graph, "forward");
	// cout << "DFS forward loop complete" << endl;

	// cout << "Print out SCCs" << endl;
	// printVector(graph->scc);


	// cout << graph_pt->nodes.size() << endl;
	// cout << graph_pt->nodes[3]->seen << endl;



	return(0);
}


void printVector(vector<int> vec) {
	// print current graph.nodes
	cout << "size of vector is " << vec.size() << endl;
	for (int i = 0; i < vec.size(); i++) {
		cout << " " << vec[i];
	}
}

void addEdge(Node &node, Node* node_name) {
	node.edges.push_back(node_name);
}

void addReverseEdge(Node &node, Node* node_name) {
	node.reverseEdges.push_back(node_name);
}

void addNodeToGraph(Graph &graph, Node* pt, int ind) {
	graph.nodes[ind] = pt;
}

void addEdgeToNodeOnGraph(Graph &graph, string node_name, string edge_name) {
	int node_name_int = stoi(node_name);
	int edge_name_int = stoi(edge_name);
	int max_ind = max(node_name_int, edge_name_int);
	if (max_ind > graph.nodes.capacity()) {
		graph.nodes.resize(max_ind + 1);
	}

	// Ensure both nodes exist in graph
	if (graph.nodes[node_name_int] == 0) {
		Node* node = new Node(node_name);
		addNodeToGraph(graph, node, node_name_int);
	}
	if (graph.nodes[edge_name_int] == 0) {
		Node* edge = new Node(edge_name);
		addNodeToGraph(graph, edge, edge_name_int);
	}

	Node* node = graph.nodes[node_name_int];
	Node* edge = graph.nodes[edge_name_int];

	// add front and reverse edge
	addEdge(*node, edge);
	addReverseEdge(*edge, node);
}

void unseeNodes(Graph &graph) {
	for (int i = 1; i < graph.nodes.size(); i++) {
		Node node = *graph.nodes[i];
		node.seen = 0;
	}
}

Graph* populate(string fileName) {
	Graph* graph_pt = new Graph();
	int lineNum = 1;
	string str;
	ifstream infile;
	infile.open(fileName);
	while(getline(infile, str)) {
		int ind = str.find(" ");
		string node_str = str.substr(0, ind);
		string edge_str = str.substr(ind + 1);
		addEdgeToNodeOnGraph(*graph_pt, node_str, edge_str);
		// cout << "line " << lineNum << ": ";
		// cout << node_str << ":" << edge_str << endl;
		lineNum++;
	}
	infile.close();
	return graph_pt;
}

Graph* dfs_loop(Graph* graph, string direction) {
	Graph* new_graph = new Graph();
	int size = graph->nodes.size() - 1;
	new_graph->nodes.resize(size);
	int t = 0;
	int s;
	for (int i = graph->nodes.size() - 1; i; i--) {
		Node* node = graph->nodes[i];
		if (!node->seen) {
			s = 0;
			dfs(node, direction, t, s, new_graph);
			new_graph->scc.push_back(s);
		}
	}
	// sort(new_graph->nodes.begin(), new_graph->nodes.end(), compare);
	return new_graph;
}

void dfs(Node* start_node, string direction, int &t, int &s, Graph* graph) {
	vector<Node*> mystack;
	mystack.push_back(start_node);

	while (mystack.size()) {
		Node* node = mystack.back();
		mystack.pop_back();
		if (node->seen == 0) {
			s++;
			node->seen++;
			mystack.push_back(node);
			if (direction == "forward") {
				for (int i = 0; i < node->edges.size(); i++) {
					Node* edge = node->edges[i];
					if (edge->seen == 0) {
						mystack.push_back(edge);
					}
				}
			} else if (direction == "reverse") {
				for (int i = 0; i < node->reverseEdges.size(); i++) {
					Node* edge = node->reverseEdges[i];
					if (edge->seen == 0) {
						mystack.push_back(edge);
					}
				}
			}
		} else if (node->seen == 1) {
			node->seen++;
			t++;
			node->f = t;
			addNodeToGraph(*graph, node, t);
		}
		node = NULL;
	}
}

bool compare(int a, int b) {
	return (a > b);
}