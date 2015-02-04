
var fs = require('fs');

fs.readFile('kargerMinCut.txt', function(err, data) {
	// var data = fs.readFileSync('kargerMinCut.txt');
	if (err) throw(err);

	var min_cuts = Infinity;
	var times = 10;
	for (var i = 0; i < Math.floor(times * Math.log(times)); i++) {
		var nodeList = new NodeList(data.toString().split('\n').map(function(str) {
			var str_arr = str.split('\t').map(function(val) {
				return val * 1;
			}).filter(function(val) {
				return val > 0;
			});
			return new Node(str_arr.shift(), str_arr);
		}));

		var cuts = nodeList.findMinCut();
		if (cuts < min_cuts) min_cuts = cuts;
	};
	console.log('min_cuts is ', min_cuts);
});


var Node = function(node, edges) {
	this.name = node;
	this.edges = edges;
}

Node.prototype.getIndexOfEdge = function(node_name, start) {
	if (start === undefined) start = 0;
	return this.edges.indexOf(node_name, start);
};

Node.prototype.removeEdgesTo = function(target_node_name) {
	this.edges = this.edges.filter(function(node_name) {
		return node_name != target_node_name;
	});
};

Node.prototype.combineEdgesWith = function(node) {
	this.edges = this.edges.concat(node.edges);
	this.removeEdgesTo(this.name);
	this.removeEdgesTo(node.name)
};



var NodeList = function(arr) {
	this.nodes = arr;
}

NodeList.prototype.findMinCut = function() {
	while (this.nodes.length > 2) {
		var randNode_ind = Math.floor(Math.random() * this.nodes.length);
		var randNode = this.nodes[randNode_ind];
		var randEdge_ind = Math.floor(Math.random() * randNode.edges.length);
		var randEdge = randNode.edges[randEdge_ind];

		this.collapseEdge(randNode, randEdge);
	}
	return this.nodes[0].edges.length;
};

NodeList.prototype.collapseEdge = function(node1, node2_name) {
	var node2_ind = this.indexOf(node2_name);
	var node2 = this.nodes[node2_ind];

	// Combine node edges and remove all self loops
	node1.combineEdgesWith(node2);
	this.nodes.splice(node2_ind, 1);
	this.updateEdgesFromTo(node2_name, node1.name);
};

NodeList.prototype.indexOf = function(node_name) {
	for (var i = 0; i < this.nodes.length; i++) {
		if (this.nodes[i].name == node_name) {
			return i;
		}
	};
};

NodeList.prototype.updateEdgesFromTo = function(from_node_name, to_node_name) {
	this.nodes.forEach(function(node) {
		var ind = 0;
		while (ind != -1) {
			ind = node.getIndexOfEdge(from_node_name, ind);
			if (ind != -1) {
				node.edges[ind] = to_node_name;
			}
		}
	});
};