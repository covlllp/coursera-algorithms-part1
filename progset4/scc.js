var fs = require('fs');

fs.readFile('SCC.txt', function(err, data) {
	var start = new Date();
	if (err) throw(err);
	var graph = new Graph();
	console.log('start');

	data.toString().split('\n').forEach(function(edge_pair) {
		var edge = edge_pair.trim().split(' ');
		graph.addEdgeToNode(edge[0], edge[1]);
	});

	console.log('population done, start dfs loop');

	var obj = graph.dfs_loop('backward');

	console.log('dfs loop done, clear seen flags')

	var new_graph = obj[0];

	new_graph.unseeNodes();

	console.log('done, start final loop')

	obj = new_graph.dfs_loop('forward');

	console.log('done, obj length is ', obj[1].length)
	console.log(obj[1].slice(0, 5));
});

var Node = function(name) {
	this.name = name;	// node number
	this.edges = [];	// array of node numbers corresponding to edges
	this.reverseEdges = [];
	this.seen = 0;
	this.leader;
	this.f;
};

Node.prototype.addEdge = function(node_name) {
	this.edges.push(node_name);
};

Node.prototype.addReverseEdge = function(node_name) {
	this.reverseEdges.push(node_name);
};


var Graph = function() {
	this.nodes = {};
	this.length = 0;
}

Graph.prototype.dfs_loop = function(direction) {
	console.log('length is ', this.length);
	var new_graph = new Graph();
	var self = this;
	var t = 0;
	var s;
	var s_container = [];
	for (var i = this.length; i; i--) {
		if (i%5000 == 0) process.stdout.write('x');
		var node = this.nodes[i];
		if (!node.seen) {
			s = 0;
			dfs(node, direction);
			s_container.push(s);
		}
	}

	function dfs (node, direction) {
		var stack = [node];

		while (stack.length) {
			var n = stack.pop();
			if (n.seen == 0) {
				// if (s%100 == 0) process.stdout.write('0');
				s++;
				n.seen++;
				stack.push(n);
				if (direction == 'forward') {
					for (var i = 0; i < n.edges.length; i++) {
						var ind = self.findEdgeInd(n.edges[i])
						var next_n = self.nodes[ind];
						if (next_n.seen == 0) stack.push(next_n);
					};
				} else if (direction == 'backward') {
					for (var i = 0; i < n.reverseEdges.length; i++) {
						var ind = self.findEdgeInd(n.reverseEdges[i])
						var next_n = self.nodes[ind];
						if (next_n.seen == 0) stack.push(next_n);
					};
				}
			} else if (n.seen == 1) {
				n.seen++;
				t++;
				n.f = t;
				new_graph.addNode(n, n.f);
			}
		}
	}
	return [new_graph, s_container.sort(function(a, b) {
		return b - a;
	})];
};

Graph.prototype.findEdgeInd = function(node_name) {
	var keys = Object.keys(this.nodes);
	for (var i = 0; i < keys.length; i++) {
		var node = this.nodes[keys[i]]
		if (node.name == node_name) return keys[i];
	};
};

Graph.prototype.addNode = function(node, node_ind) {
	this.nodes[node_ind] = node;
	this.length++;
};

Graph.prototype.addEdgeToNode = function(node_name, edge_name) {
	if (!edge_name) return;
	if (!this.nodes.hasOwnProperty(node_name)) {
		this.addNode(new Node(node_name), node_name);
	}
	this.nodes[node_name].addEdge(edge_name);

	// also add reverse node
	if (!this.nodes.hasOwnProperty(edge_name)) {
		this.addNode(new Node(edge_name), edge_name);
	}
	this.nodes[edge_name].addReverseEdge(node_name);
};

Graph.prototype.unseeNodes = function() {
	for (var node in this.nodes) {
		this.nodes[node].seen = 0;
	}
};