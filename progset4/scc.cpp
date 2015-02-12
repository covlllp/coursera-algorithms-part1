#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

struct Node {
	string name;
	int seen, f;
	vector<Node*> edges, reverseEdges;
	Node(string n) : name(n) {}
};

struct Graph {
	vector<Node*> nodes;	// size is always one more; 0 index not used
};

void addEdge(Node &node, Node* node_name);
void addReverseEdge(Node &node, Node* node_name);
void addNodeToGraph(Graph &graph, Node* pt, int ind);
void addEdgeToNodeOnGraph(Graph &graph, string node_name, string edge_name);
void unseeNodes(Graph &graph);
Graph* populate(string fileName);
void dfs_loop(Graph* graph, string direction);
void dfs(Node* node, string direction, int &t, int &s);



int main()
{
	cout << "Start populating" << endl;
	Graph* graph_pt = populate("SCC.txt");
	cout << "Done populating, starting first dfs loop" << endl;

	cout << "Start DFS loop on reverse graph" << endl;
	dfs_loop(graph_pt, "reverse");
	cout << "DFS reverse loop complete" << endl;
	// cout << graph_pt->nodes.size() << endl;
	// cout << graph_pt->nodes[3]->seen << endl;



	return(0);
}




void addEdge(Node &node, Node* node_name) {
	node.edges.resize(node.edges.size() + 1);
	node.edges.push_back(node_name);
}

void addReverseEdge(Node &node, Node* node_name) {
	node.reverseEdges.resize(node.reverseEdges.size() + 1);
	node.reverseEdges.push_back(node_name);
}

void addNodeToGraph(Graph &graph, Node* pt, int ind) {
	graph.nodes[ind] = pt;
	// graph.nodes.insert(graph.nodes.begin() + ind, pt);
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

	// // print current graph.nodes
	// cout << "size of vector is " << graph.nodes.size();
	// cout << ", max_ind is " << max_ind;
	// cout << ", node_name is " << node_name;
	// cout << ", edge_name is " << edge_name << endl;
	// for (int i = 0; i < graph.nodes.size(); i++) {
	// 	cout << "index " << i << ": " << graph.nodes[i] << endl;
	// }


	Node* node_pt = graph.nodes[node_name_int];
	Node node = *node_pt;

	// Node node = *graph.nodes[node_name_int];
	Node edge = *graph.nodes[edge_name_int];

	// add front and reverse edge
	addEdge(node, &edge);
	addReverseEdge(edge, &node);
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

void dfs_loop(Graph* graph, string direction) {
	int t = 0;
	int s;
	vector<int> s_container;
	for (int i = graph->nodes.size() - 1; i; i--) {
		Node* node = graph->nodes[i];
		if (!node->seen) {
			s = 0;
			dfs(node, direction, t, s);
			s_container.push_back(s);
		}
	}
}

void dfs(Node* start_node, string direction, int &t, int &s) {
	stack<Node*> mystack;
	mystack.push(start_node);

	while (mystack.size()) {
		Node* node = mystack.top();
		mystack.pop();
		if (node->seen == 0) {
			s++;
			node->seen++;
			mystack.push(node);
			if (direction == "forward") {
				for (int i = 0; i < node->edges.size(); i++) {
					Node* edge = node->edges[i];
					if (edge->seen == 0)
						mystack.push(edge);
				}
			} else if (direction == "reverse") {
				for (int i = 0; i < node->reverseEdges.size(); i++) {
					Node* edge = node->reverseEdges[i];
					if (edge->seen == 0)
						mystack.push(edge);
				}
			}
		} else if (node->seen == 1) {
			node->seen++;
			t++;
			node->f = t;
		}
	}
}
