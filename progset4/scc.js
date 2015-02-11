var fs = require('fs');

fs.readFile('SCC.txt', function(err, data) {
	var start = new Date();
	if (err) throw(err);
	var graph = new Graph();
	
	data.toString().split('\n').forEach(function(edge_pair) {
		var edge = edge_pair.trim().split(' ');
		graph.addEdgeToNode(edge[0], edge[1]);
	});
});

var Node = function(name) {
	this.name = name;	// node number
	this.edges = [];	// array of node numbers corresponding to edges
	this.reverseEdges = [];
};

Node.prototype.addEdge = function(node_name) {
	this.edges.push(node_name);
};


var Graph = function() {
	this.nodes = {};
}

Graph.prototype.addNode = function(node) {
	this.nodes[node.name] = node;
};

Graph.prototype.addEdgeToNode = function(node_name, edge_name) {
	if (!edge_name) return;
	if (!this.nodes.hasOwnProperty(node_name)) {
		this.addNode(new Node(node_name));
	}
	this.nodes[node_name].addEdge(edge_name);
};